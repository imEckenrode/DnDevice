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

 This file resulted from a refactoring of dndv_internals
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

// identifier (for players and PCs) - a unique number
typedef short Identifier;    //Can change this implementation as needed



//For the raw data to send, use uint8_t* 
//typedef uint8_t* data_p;

/*   Device-level data is managed in dndv_internals   */



/*      Sending Structures and Functions
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
} d_ids;           //When you allocate space for this, you want to allocate the size of the struct plus the amount of space you want for the array


 //fullData: MAC address and data (send the stuff under data)
typedef struct __attribute__((__packed__)) macPlusData{
    macAddr mac;                //The MAC address of the recipient or sender, this is never passed through 
    short dataLen;          //The length of the data, for easy sending
    uint8_t data[];                 //This "flexible array member" means dynamic allocation will be neccesary
} macAndData;           //When you allocate space for this, allocate the size of the MAC plus the amount of space you want for the array

 //fullData: MAC address and data (send the stuff under data)
typedef struct __attribute__((__packed__)) macPlusIdData{
    macAddr mac;                //The MAC address of the recipient or sender, this is never passed through 
    short dataLen;          //The length of the data, for easy sending
    uint8_t data[];                 //This "flexible array member" means dynamic allocation will be neccesary
} macIData;           //When you allocate space for this, allocate the size of the MAC plus the amount of space you want for the array


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
}; //Use N_ your base to get the number automatically.
      //Make sure this matches EventBases in dndv_data.c
//TODO: do this better, store numbers in a struct in that array, then somehow make it visible


/*             -- Bases and ID Declaration --
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

/* -  MISC_BASE: For any data received that doesn't have a specific place (yet)  */
ESP_EVENT_DECLARE_BASE(MISC_BASE);  //Defined in the c file
//extern esp_event_base_t MISC_BASE = "MISC_BASE";    //TODO: Make more like this, plus add in DM version?
enum MISC_B_ID{ 
    //EVENT_SYS,
    EVENT_TEST,
    //EVENT_STRAIGHTTOLOG,
    EVENT_LOG,
    EVENT_PING                //TODO: Maybe add a timestamp for actual ping timing capabilities
};


/* -  DEVICE_BASE: For global changes to the state of the local device (that may require further messages) 
        Used primarily for editing dndv_internals and changing device state
        */
ESP_EVENT_DECLARE_BASE(DEVICE_BASE);
enum DEVICE_B_ID{
    //EVENT_KEVIN,            //EVENT_KEYIN!
    EVENT_DM_KEYIN,         //When a DM keys in (keyin without selecting a campaign)
    //EVENT_DM_NAME_CAMPAIGN
    EVENT_DM_ACTIVATE,       //When the DM is activated
    EVENT_DM_START_CAMPAIGN

    EVENT_CAMPAIGN_SELECTED,        //When a player selects a campaign from a broadcasting DM
    EVENT_PLAYER_KEYIN,    //When a player is selected through a keyin (TODO: will need to get sync data about character)
    EVENT_PC_CHOSEN,        //When the user selects his/her character

    EVENT_ENTER_WORLD       //
};

//EVENT_KEVIN_LEVIN



/* -  SYNC_BASE: For syncing data DMs and Player devices
        Used primarily by dndv_comms
    Contains all data for syncing. Players should stop listening to these events once in.
        */
ESP_EVENT_DECLARE_BASE(SYNC_BASE);
enum SYNC_B_ID{
    EVENT_AWAKE_BROADCAST_RCV,      //Broadcasted on awake, so active DMs can send directly to this new device
    EVENT_DM_INFO,                    //Broadcasted when a device becomes a DM. Transmits the DM name and campaign name
    EVENT_INFO_ACK,                           //DM Info Acknowledged, letting the DM keep track of potential users (in case a DM wants to directly assign a character)

    EVENT_KEYDATA_REQ,      //A device requested the player name and character data for a specified key, so return the data 
    EVENT_KEYDATA_RCV,       //The data requested was received


    EVENT_READY_TO_START_CAMPAIGN    //When the DM says Start, allow the players to start
};





/* - OUTGOING_BASE
    This is a special base only for sending ESP-NOW-ready data.
  Typically only used from dndv_internals, where dndv_comms is out of scope.
*/
ESP_EVENT_DECLARE_BASE(OUTGOING_BASE);
enum OUTGOING_B_ID{
    EVENT_SEND,
    EVENT_SEND_BROADCAST,
    //EVENT_SEND_TO_ALL_CONTACTS    //For Players to send to all DMs, or a DM to send to all Players
};


/*  And finally,
-  DM_RCV_BASE: For all events targeted to the DM from other devices
    These are DM exclusive actions that should only heard by DM_ACTIVATE (and whatever logs want it)
        TODO: See if this is the best way
*/
ESP_EVENT_DECLARE_BASE(DM_RCV_BASE);
enum DM_RCV_B_ID{
    EVENT_SYNC_REQUEST,         //When a player device asks for the DM info
    //EVENT_PC_JOINED,            //A PC has joined the adventure!
    //EVENT_PC_READY
};




/*  TODO:    - DM EXCLUSIVE FUNCTIONS -
    DM exclusive functions should always be verified by the global isDM variable...
   
*/
#endif