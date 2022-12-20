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
#define MAX_PLAYER_COUNT 16

#define MAC_ADDR_SIZE 6     //uints and chars are 1 byte each, so the size should always be 6*1
/*     -- LOWEST LEVEL DATA TYPES --      */

// Key(Identifier) (for players and PCs) - a unique number, used to key in and track each character
typedef short Key;    //Can change this implementation as needed


//  - ARRAY DATA TYPES -
typedef uint8_t DynData[]; //Dynamic Data type, must be last in the struct and must allocate room for it. \\TODO: Implement this in place of all the other uint8_t datas
//may need typedef uint8_t* data_p; for raw data...

//MacAddr is defined to make any MAC address assignments more readable
typedef unsigned char macAddr[MAC_ADDR_SIZE];

typedef char NickName[8];
typedef char StandardName[24];
typedef char FullName[96];
typedef char Msg[192];


/*   Device-level data is managed in dndv_internals   */


/* _- Auxillary Functions -_

    Nice assistant functions    */

//Pretty prints the MAC address
bool printMAC(macAddr MAC);



/*  ---  Sending Structures and Functions ---

    These are the generic sending structures
    See the sending structures per ID under "Bases and IDs"

*/
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



typedef struct __attribute__((__packed__)){
    Key key;
    StandardName p_name;   //P is Person/Player (AKA the IRL name)
    StandardName c_name;   //C is Campaign or Character Name, depending on if DM or PC
} ContactInfo;


/*     -- Device Level Data Types --      */

/* The player [and DM] struct (save data into a file)  */
typedef struct  __attribute__((__packed__)){
    Key key;
    NickName nickname;
    StandardName name;
    bool canDM;
    bool TrainingWheelsProtocol_Active;
} Player;

/* The character struct (save data into a file) */ 
typedef struct __attribute__((__packed__)) character_s{
    Key key;
    NickName nickname;
    StandardName name;
    short MaxHP;
    short HP;
    short XP10;
} PC;

/*     - Connections Tracking and Naming -
    For DMs, this is the list of players
    For players, this is the list of possible DMs and the campaign names  //, and TODO should stop persisting after a DM is selected
*/

//*** contactInfo stores the ID, the player name, and the character name

struct Contact{
    macAddr MAC;
    ContactInfo info;
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

    For sync IDs, the data contains the event to be received, not to send. 
    (e.g. a character update sending from a DM to a character would be EVENT_CHAR_UPDATE_RCV instead of EVENT_CHAR_UPDATE_REQuest)      (/TODO: Add to Readme)

                     # FOR DEVELOPERS #
    Try not to collide names, even between events, seeing as each ID is only described as a number in an enumerator

    In the dndv_comms system, one byte is for bases, one byte is for IDs
    Although the Event Loop Library allows for up to 2^32 IDs, only the first 256 per base are allowed to be sent over our ESP-NOW implementation
    If you have an enumerator below that has more than 256 elements, please refactor by introducing a new base.
*/

/* BASE CONVERSION
    ESP-NOW defines bases as a character array. These methods convert back and forth to our custom numbering */
//To convert from the ELL Base to our custom numbers
uint8_t EventBase2Num(esp_event_base_t base);
//To convert back to the ELL Base from our custom numbers
esp_event_base_t Num2EventBase(uint8_t num);

enum base_numbers{                       //TODO: stop using this. Fast, but have to maintain separately
    N_MISC_BASE,
    N_DEVICE_BASE,
    N_OUTGOING_BASE, 
    N_SYNC_BASE,            //For syncing data between DMs and Players
    N_DM_RCV_BASE,
    N_DMDEVICE_BASE,            //DEVICE BASE, but for DMs
}; //Use N_ your base to get the number automatically.
      //Make sure this matches EventBases in dndv_data.c
//TODO: move this near the base struct, store numbers in a struct in that array, then somehow make it visible


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

/* --  MISC_BASE: For any data received that doesn't have a specific place (yet) -- */
ESP_EVENT_DECLARE_BASE(MISC_BASE);  //Defined in the c file
//extern esp_event_base_t MISC_BASE = "MISC_BASE";    //TODO: Make more like this, plus add in DM version?
enum MISC_B_ID{ 
    //EVENT_SYS,
    EVENT_TEST,
    //EVENT_STRAIGHTTOLOG,
    EVENT_LOG,
    EVENT_PING                //TODO: Maybe add a timestamp for actual ping timing capabilities
};




/* --  DEVICE_BASE: For global changes to the state of the local device (that may require further messages) --
        Used primarily for editing dndv_internals and changing device state

    These functions will then call the appropriate 

    As a DM, these events will be handled differently if at all;
    See DM_DEVICE_BASE for DM-specific functions.
        */
ESP_EVENT_DECLARE_BASE(DEVICE_BASE);
enum DEVICE_B_ID{
    EVENT_DM_KEYIN,     //Transfer control to DM_DEVICE_BASE if a DM keys in successfully (had DM permissions)

    EVENT_CAMPAIGN_SELECT,        //When a player selects a campaign from a broadcasting DM
    EVENT_PLAYER_KEYIN,    //When a player is selected through a keyin (TODO: will need to get sync data about character)
    EVENT_PC_CHOSEN,        //When the user selects his/her character

    EVENT_ENTER_WORLD       //If the DM has started the adventure, this loads the dashboard screen and removes any old initialization data
};
//EVENT_KEVIN_LEVIN




/* --  OUTGOING_BASE  --
    This is a special base only for sending ESP-NOW-ready data.
  Typically only used from dndv_internals, where dndv_comms is out of scope.

  USE OTHER FUNCTIONS IF POSSIBLE //TODO
*/
ESP_EVENT_DECLARE_BASE(OUTGOING_BASE);
enum OUTGOING_B_ID{
    EVENT_SEND,
    EVENT_SEND_BROADCAST,
    //EVENT_SEND_TO_ALL_CONTACTS    //For Players to send to all DMs, or a DM to send to all Players
};



/*      __  Sync Bases   __        
    For talking at startup between players and DM
*/

/* --  SYNC_BASE: For syncing data DMs and Player devices  --
        Used primarily by dndv_comms
    Contains all data for syncing. Players should stop listening to these events once in.
        */
ESP_EVENT_DECLARE_BASE(SYNC_BASE);
enum SYNC_B_ID{
    EVENT_AWAKE_BROADCAST_RCV,      //Broadcasted on awake, so active DMs can send directly to this new device
    EVENT_DM_INFO,          //[Uses dm_info_s]. Broadcasted when a device becomes a DM. Transmits the DM name and campaign name
                                //Either the player list and character list  or  character data was requested   */
    EVENT_KEYDATA_RCV,       //The Key Data         requested through the key was received
    EVENT_PCDATA_RCV,        //The Character Data   requested through the key was received
    EVENT_KEYANDPC_RCV,     //The Key and Character Data, for 

    EVENT_START_ADVENTURE    //When the DM says Start, allow the players to start
};
    
/* Data broadcasted when the DM is set up, or messaged directly when requested by a player */
struct __attribute__((__packed__)) dm_info_s {
        struct EVENT event;               //The base and ID struct
        ContactInfo info;
};


struct __attribute__((__packed__)) keydata_rcv_s{
    Key key;
    Player playerInfo;
    bool nickNamesRcv;  //This is True if there are more than 8 characters to send
    bool longNamesRcv;  //This is True if there are only 1 or 2 characters to send and you prefer to use the long names
    union pcList
    {
        //For more than 8 characters
        struct __attribute__((__packed__)) {  //10 Bytes Each
            Key key;
            NickName name;
        } nickList[21];        //Currently 21 since Key+Player < 40

        //For between 2 and 8 characters
        struct __attribute__((__packed__)) {
            Key key;
            StandardName name;
        } pcList[8];           //Currently 8 since Key+Player < 40

        //For only 1 or 2 characters, can send the full names if desired
        struct __attribute__((__packed__)) {
            Key key;
            NickName nick;
        } pcList[2];           //2 long names = 192
    };
};


struct __attribute__((__packed__)) pcdata_rcv_s{
    Key key;
    PC pcInfo;
};


/* --  DM_SYNC_BASE: For all events targeted to the DM from other devices  --
    These are DM exclusive actions that should only heard by DM_ACTIVATE (and whatever logs want it)*/
ESP_EVENT_DECLARE_BASE(DM_SYNC_BASE);
enum DM_RCV_B_ID{
    EVENT_SYNC_REQ,         //When a player device asks for the DM info
    EVENT_KEYDATA_REQ,      //Return the data requested for a specified key.
    EVENT_PC_REQ,       //Return the date for the requested player character

    //EVENT_PC_JOINED,            //A PC has joined the adventure!
    //EVENT_PC_READY
};

//KeyData returns player info if the key is for a player       //TODO: Return NPC data as well
struct __attribute__((__packed__)) keydata_req_s{
    Key key;
};




/*  ==  The Final DM Base  ==
      --  DM_DEVICE_BASE  --
 For all DM-related local events. Only accessible to a DM.*/
ESP_EVENT_DECLARE_BASE(DM_DEVICE_BASE);
enum DM_DEVICE_B_ID{
    //EVENT_DM_KEYIN,         //A DM keyin is handled in DEVICE_BASE, since the DM is not yet a DM
    //EVENT_DM_NAME_CAMPAIGN

    EVENT_DM_ACTIVATE,       //[Uses no data]    When the DM is fully activated, broadcast out all the data (under EVENT_DM_INFO)
    EVENT_START_CAMPAIGN,
};



#endif