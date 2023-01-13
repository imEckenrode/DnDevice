//#pragma once
#ifndef DNDV_DATA_H    //Cannot start with an E or an underscore, so may rename to H_...
#define DNDV_DATA_H

#include <stdbool.h>
#include <string.h> //for base comparison
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_err.h"
#include "esp_log.h"

/*               - - - THIS FILE DESCRIPTION - - -
 
 All event loop, NVS, and ID structure stuff for the DnDevice can be found in here.
    This is the only file lower than dndv_internals; dndv_internals imports this file.

 This file resulted from a refactoring of dndv_internals into dndv_internals and dndv_data
    Just import "dndv_data.h"

This will allow the usage of the event loop library and ID structures anywhere that includes "dndv_data.h"

order:      (global variables on top, then)
    Title
    Struct
    Comment about what the function will do
    Function
*/

/*      -  NVS  - 

Initialize the non-volatile storage library to persist data 
    Required for: ESP-NOW   */
void nvs_init(void);


/*         -- GLOBAL DEFINITIONS --          */
#define INITIAL_MAX_PLAYER_COUNT 16     //The DnDevice allocates room for this many players' contact info (MAC, key, names, etc)

#define MAC_ADDR_SIZE 6     //uints and chars are 1 byte each, so the size should always be 6*1
/*     -- LOWEST LEVEL DATA TYPES --      */

//Byte-sized number
typedef uint8_t Num;
//Byte-sized signed number
typedef int8_t sNum;

// Key(Identifier) (for players and PCs) - a unique number, used to key in and track each character
typedef short Key;    //Can change this implementation as needed
//  - ARRAY DATA TYPES -
typedef uint8_t DynData[]; //Dynamic Data type, must be last in the struct and must allocate room for it. \\TODO: Implement this in place of all the other uint8_t datas
//may need typedef uint8_t* data_p; for raw data...

//MacAddr is defined to make any MAC address assignments more readable
typedef unsigned char macAddr[MAC_ADDR_SIZE];

typedef char NickName[8];
typedef char Name[24];
typedef char FullName[96];
typedef char Msg[192];

/*   Device-level data is managed in dndv_internals   */


/* _- Auxillary Functions -_

    Nice assistant functions    */

//Pretty prints the MAC address
bool printMAC(macAddr MAC);



/*  ---  Sending Structures and Functions ---

    These are the generic sending structures
    See the sending structures per ID under "Bases and IDs"      */

/*  ID as Data (no other data = no Malloc required) - Data Structure */
struct __attribute__((__packed__)) EVENT{
    uint8_t BASE;
    uint8_t ID;
};

/*
typedef struct __attribute__((__packed__)) eventPlusData{
    uint8_t data[];   //This "flexible array member" means dynamic allocation will be neccesary
} d_pure;   */      //Cannot have only a blank member


// Data with indexed IDs under event.base and event.ID (the standard data struct)
typedef struct __attribute__((__packed__)) eventPlusData{           //todo: use...?
    struct EVENT event;
    uint8_t data[];   //This "flexible array member" means dynamic allocation will be neccesary
} d_event_s;           //When you allocate space for this, you want to allocate the size of the struct plus the amount of space you want for the array


 //fullData: MAC address and data (send the stuff under data)
typedef struct __attribute__((__packed__)) macPlusData{
    macAddr mac;                //The MAC address of the recipient or sender, this is never passed through 
    uint8_t data[];                 //This "flexible array member" means dynamic allocation will be neccesary
} macAndData_s;           //When you allocate space for this, allocate the size of the MAC plus the amount of space you want for the array

//(Unused)  MAC address and data with access to the IDs (make sure to send IDs and data)
typedef struct __attribute__((__packed__)) macPlusIdData{
    macAddr mac;                //The MAC address of the recipient or sender, this is never passed through 
    struct EVENT event;
    uint8_t data[];                 //This "flexible array member" means dynamic allocation will be neccesary
} macIData;           //When you allocate space for this, allocate the size of the MAC plus the amount of space you want for the array



/*     -- GENERIC ID STRUCTURES --
    These structures are used by multiple data types
*/


//Data Separated by the \0 string end
typedef struct __attribute__((__packed__)){
    char* dynamicNameData;
} DynamicNameList;



/*     -- Device Level Data Types --      */

/* The player [and GM] struct (save data into a file)  */
typedef struct  __attribute__((__packed__)){
    NickName nickname;
    Name name;
    bool canGM;
    bool TrainingWheelsProtocol_Active;
} Player;

/* The character struct (save data into a file) */ 
typedef struct __attribute__((__packed__)) character_s{
    NickName nickname;
    Name name; 
    short HP;
    short XP10;
    sNum AC;
} PC;


struct __attribute__((__packed__)) PnC_s{           //TODO Use this as the info instead of the GM way    -> Add: Key key;
    Player Player;
    PC PC;
};

/*     - Connections Tracking and Naming -
    For GMs, this is the list of players
    For players, this is the list of possible GMs and the campaign names  //, and TODO should stop persisting after a GM is selected
*/
typedef struct __attribute__((__packed__)){
    Key key;
    Name p_name;   //P is Person/Player (AKA the IRL name)
    Name c_name;   //C is Campaign or Character Name, depending on if GM or PC
} ContactInfo;

typedef struct __attribute__((__packed__)) {
    macAddr MAC;
    ContactInfo info;
} ContactAddress;

struct __attribute__((__packed__)) ContactAddressBook{
    short maxContacts;           //Assigned at allocation time to track remaining space
    ContactAddress contact[];
};


//For the GM, this is local names and MAC is used for six bytes of other information
//For the player, this is the GMDevice info, including the MAC
    //TODO: add campaignKey info in here if that becomes a thing
struct  __attribute__((__packed__)) gmInfo{
    Name gmName;
    Name campaignName;          //Update this to longName if space
    union{
        macAddr MAC;
        struct{ //Up to 6 bytes of info can go in here
            Num playerCount;
        };
    };
};

/* ______  --- EVENT LOOP ---  ______
    This is the handle that alerts all code when something is updated.

    This can be an ESP-NOW receive, a local battle change, or connections and settings data

    To receive data, call something like esp_event_handler_instance_register_with(dndv_event_h, ESP_EVENT_ANY_BASE, ESP_EVENT_ANY_ID,rcvToLog,NULL,NULL);
                                                                                                EVENT_BASE_HERE     EVENT_ID_HERE      ^function name
    FORMATTING:
        Declare the base here with comments, then put an enumerator with all possible event IDs for that base.

        Be sure to Define the base in dndv_data.c!
*/

//The handle for all dndevice events
esp_event_loop_handle_t dndv_event_h;

//Initialize the event loop library
void eventLoop_init(void);

/*                  -- EVENT: BASES AND IDS --
    Here is the system for all the ID's used within the DnDevice.

    For sync IDs (see dndv_comms), the data contains the event to be received, not to send. 
    (e.g. a character update sending from a GM to a character would be EVENT_CHAR_UPDATE_RCV instead of EVENT_CHAR_UPDATE_REQuest)      (/TODO: Add to Reagme)

                     # FOR DEVELOPERS #
    Try not to collide names, even between events, seeing as each ID is only described as a number in an enumerator

    In the dndv_comms system, one byte is for bases, one byte is for IDs
    Although the Event Loop Library allows for up to 2^32 IDs, only the first 256 per base are allowed to be sent over our ESP-NOW implementation
    If you have an enumerator below that has more than 256 elements, please refactor by introducing a new base.
*/

//This will eventually be removed and is only here to support legacy code (in dndv_internals)
//This only works because these are defined first in init.c     //TODO:: REMOVE THIS
enum READABLE_BASE_NUMS{
    N_SYNC_BASE,
    N_GM_SYNC_BASE,
    N_MISC_BASE
};

/*             =-- Bases and ID Declaration --=
        Comment out anything that is currently unused
    __Formatting:_________(COPY BELOW)

    ESP_EVENT_DECLARE_BASE(NAME_OF_BASE);
    enum NAME_OF_B_ID{
        EVENT_STUFF_GOES_HERE,  //Would be nice to comment as well
    };

    struct __attribute__((__packed__)) stuff_goes_here_s {         //Finally, the actual format of the data gets its own struct for easy access (_s for struct)
        struct EVENT event;     //The base and ID struct
        uint8 the_data[248];    //
    };
*/

/*      --  GM_DEVICE_BASE  --
 For all GM-related local events. Only accessible to a GM.
 (See DEVICE_BASE for a similar idea)*/
ESP_EVENT_DECLARE_BASE(GM_DEVICE_BASE);
enum GM_DEVICE_B_ID{
    //EVENT_GM_KEYIN,         //A GM keyin is handled in DEVICE_BASE, since the GM is not yet a GM
    //EVENT_GM_NAME_CAMPAIGN

    EVENT_GM_ACTIVATE,       //[Uses no data]    When the GM is fully activated, broadcast out all the data (under EVENT_GM_INFO)
    EVENT_START_CAMPAIGN,
};


/* --  DEVICE_BASE   ---
For global changes to the state of the local device (that may require further messages) --
        Used primarily for editing dndv_internals and changing device state

    These functions will then call the appropriate 

    As a GM, these events will be handled differently if at all;
    See GM_DEVICE_BASE for GM-specific functions.
        */
ESP_EVENT_DECLARE_BASE(DEVICE_BASE);
enum DEVICE_B_ID{
    EVENT_GM_KEYIN,     //Transfer control to GM_DEVICE_BASE if a GM keys in successfully (had GM permissions)
    EVENT_CAMPAIGN_SELECT,        //When a player selects a campaign from a broadcasting GM
    EVENT_PLAYER_KEYIN,    //When a player is selected through a keyin (TODO: will need to get sync data about character)
    EVENT_PC_CHOSEN,        //When the user selects his/her character
    EVENT_ENTER_WORLD       //If the GM has started the adventure, this loads the dashboard screen and removes any old initialization data
};
//EVENT_KEVIN_LEVIN




/* --  COMMS_BASE  --
    This is a special base for sending ESP-NOW-ready data and other commands to dndv_comms
  Typically only used from dndv_internals, where dndv_comms is out of scope.
*/
ESP_EVENT_DECLARE_BASE(COMMS_BASE);
//Only use EVENT_SEND... for ESPNOW-ready data
enum COMMS_B_ID{
    EVENT_SEND,
    EVENT_SEND_BROADCAST,
    EVENT_SEND_TO_ALL_CONTACTS,    //For Players to send to all GMs, or a GM to send to all Players

    EVENT_BROADCAST_NEW_DEVICE
};


/* --  MISC_BASE: For any data received that doesn't have a specific place (yet) -- */
ESP_EVENT_DECLARE_BASE(MISC_BASE);  //Defined in the c file
//extern esp_event_base_t MISC_BASE = "MISC_BASE";    //TODO: Make more like this, plus add in GM version?
enum MISC_B_ID{ 
    //EVENT_SYS,
    EVENT_TEST,
    //EVENT_STRAIGHTTOLOG,
    EVENT_LOG,
    EVENT_PING                //TODO: Maybe add a timestamp for actual ping timing capabilities
};



#endif