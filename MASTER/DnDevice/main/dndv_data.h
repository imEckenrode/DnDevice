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

/*     -- Lowest Level Data Types --      */

//  THIS IS AN ARRAY DATA TYPE! MacAddr is defined to make any MAC address assignments more readable
#define MAC_ADDR_SIZE 6     //uints and chars are 1 byte each, so the size should always be 6*1
typedef unsigned char macAddr[MAC_ADDR_SIZE];

// identifier (for players and PCs) - a unique number, used to key in
typedef short KeyIdentifier;    //Can change this implementation as needed


/*         -- GLOBAL DEFINITIONS --          */
#define MAX_PLAYER_COUNT 16
#define MAX_NAME_LENGTH 32  //Cound split this into Player/Person and PC/Campaign names
#define MAX_NICKNAME_LENGTH 8


//For the raw data to send, use uint8_t* 
//typedef uint8_t* data_p;

/*   Device-level data is managed in dndv_internals   */


/* _- Auxillary Functions -_

    Nice assistant functions    */

//Pretty prints the MAC address
bool printMAC(macAddr MAC);



/*  ---  Sending Structures and Functions ---

    These are the generic sending structures
    See the sending structures per ID under "Bases and IDs"
*//*
struct __attribute__((__packed__)) raw_data{
    uint8_t data[];         //This "flexible array member" means dynamic allocation will be neccesary
};  */

/*  ID as Data (no other data = no Malloc required) - Data Structure */
struct __attribute__((__packed__)) IDs{
    uint8_t BASE;
    uint8_t ID;
};

/*
typedef struct __attribute__((__packed__)) idsPlusData{
    uint8_t data[];   //This "flexible array member" means dynamic allocation will be neccesary
} d_pure;   */      //Cannot have only a blank member


// Data with indexed IDs under event.base and event.ID (the standard data struct)
typedef struct __attribute__((__packed__)) idsPlusData{
    struct IDs event;
    uint8_t data[];   //This "flexible array member" means dynamic allocation will be neccesary
} d_ids_s;           //When you allocate space for this, you want to allocate the size of the struct plus the amount of space you want for the array


 //fullData: MAC address and data (send the stuff under data)
typedef struct __attribute__((__packed__)) macPlusData{
    macAddr mac;                //The MAC address of the recipient or sender, this is never passed through 
    short dataLen;          //The length of the data, for easy sending
    uint8_t data[];                 //This "flexible array member" means dynamic allocation will be neccesary
} macAndData_s;           //When you allocate space for this, allocate the size of the MAC plus the amount of space you want for the array

//(Unused)  MAC address and data with access to the IDs (make sure to send IDs and data)
typedef struct __attribute__((__packed__)) macPlusIdData{
    macAddr mac;                //The MAC address of the recipient or sender, this is never passed through 
    short dataLen;          //The length of the data, for easy sending
    struct IDs ids;
    uint8_t data[];                 //This "flexible array member" means dynamic allocation will be neccesary
} macIData;           //When you allocate space for this, allocate the size of the MAC plus the amount of space you want for the array


/*     -- GENERIC ID STRUCTURES --
    These structures are used by multiple data types
*/

typedef char name[MAX_NAME_LENGTH];
typedef char nick[MAX_NICKNAME_LENGTH];
typedef char* dynamicName;


//Data Separated by the \0 string end
typedef struct __attribute__((__packed__)){
    char* dynamicNameData;
} DynamicNameList;

//The structure for providing the ID of a character
typedef struct __attribute__((__packed__)){
    KeyIdentifier key;
    nick nick;
} pcNick;



typedef struct __attribute__((__packed__)){
    KeyIdentifier key;
    name p_name;   //P is Person/Player (AKA the IRL name)
    name c_name;   //C is Campaign or Character Name, depending on if DM or PC
} ContactInfo;


/*Data broadcasted when the DM is set up, or messaged directly when requested by a player
    Used by EVENT_DM_ACTIVATE, EVENT_DM_INFO,
*/
struct __attribute__((__packed__)) dm_info_s {
        struct IDs event;               //The base and ID struct
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



/*                  -- BASES AND IDS --
    Here is the system for all the ID's used within the DnDevice.

    For sync IDs, the data contains the event to be received, not to send. 
    (e.g. a character update sending from a DM to a character would be EVENT_CHAR_UPDATE_RCV instead of EVENT_CHAR_UPDATE_REQuest)      (/TODO: Add to Readme)

                     # FOR DEVELOPERS #
    Try not to collide names, even between events, seeing as they are only enumerators

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
    N_SYNC_BASE,            //For syncing data between DMs and Players
    N_OUTGOING_BASE,         
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
        struct IDs event;     //The base and ID struct
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



/* --  SYNC_BASE: For syncing data DMs and Player devices  --
        Used primarily by dndv_comms
    Contains all data for syncing. Players should stop listening to these events once in.
        */
ESP_EVENT_DECLARE_BASE(SYNC_BASE);
enum SYNC_B_ID{
    EVENT_AWAKE_BROADCAST_RCV,      //Broadcasted on awake, so active DMs can send directly to this new device
    EVENT_DM_INFO,          //[Uses dm_info_s]. Broadcasted when a device becomes a DM. Transmits the DM name and campaign name

    EVENT_KEYDATA_REQ,      //Return the data requested for a specified key.
                                //Either the player list and character list  or  character data was requested   */
    EVENT_KEYDATA_RCV,       //The Key Data         requested through the key was received
    EVENT_PCDATA_RCV,        //The Character Data   requested through the key was received
    EVENT_KEYANDPC_RCV,     //The Key and Character Data, for 

    EVENT_START_ADVENTURE    //When the DM says Start, allow the players to start
};

    //EVENT_DM_INFO uses dm_info_s

struct __attribute__((__packed__)) keydata_req_s{
    KeyIdentifier key;
};
//KeyData returns player info if the key is for a player, and it returns 


struct __attribute__((__packed__)) keydata_rcv_s{
    KeyIdentifier key;
    Player playerInfo;      //How does this header know what Player is?
    pcNick pcList[];         //And return a list of all the possible characters
};

struct __attribute__((__packed__)) pcdata_rcv_s{
    KeyIdentifier key;
    PC pcInfo;      //How does this header know what Player is?
};



/* --  OUTGOING_BASE  --
    This is a special base only for sending ESP-NOW-ready data.
  Typically only used from dndv_internals, where dndv_comms is out of scope.
*/
ESP_EVENT_DECLARE_BASE(OUTGOING_BASE);
enum OUTGOING_B_ID{
    EVENT_SEND,
    EVENT_SEND_BROADCAST,
    //EVENT_SEND_TO_ALL_CONTACTS    //For Players to send to all DMs, or a DM to send to all Players
};




/*  == And finally, DM Stuff ==
  --  DM_RCV_BASE: For all events targeted to the DM from other devices  --
    These are DM exclusive actions that should only heard by DM_ACTIVATE (and whatever logs want it)
        TODO: See if this is the best way
*/
ESP_EVENT_DECLARE_BASE(DM_RCV_BASE);
enum DM_RCV_B_ID{
    EVENT_SYNC_REQUEST,         //When a player device asks for the DM info
    //EVENT_PC_JOINED,            //A PC has joined the adventure!
    //EVENT_PC_READY
};



/*      --  DM_DEVICE_BASE  --
For all DM-related local events. Only accessible to a DM.
*/
ESP_EVENT_DECLARE_BASE(DM_DEVICE_BASE);
enum DM_DEVICE_B_ID{
    //EVENT_DM_KEYIN,         //A DM keyin is handled in DEVICE_BASE, since the DM is not yet a DM
    //EVENT_DM_NAME_CAMPAIGN

    EVENT_DM_ACTIVATE,       //[Uses no data]    When the DM is fully activated, broadcast out all the data (under EVENT_DM_INFO)
    EVENT_START_CAMPAIGN,
};



#endif