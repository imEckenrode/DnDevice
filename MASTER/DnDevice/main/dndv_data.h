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

/*     -- Lowest Level Data Types --      */

//  THIS IS AN ARRAY DATA TYPE! MacAddr is defined to make any MAC address assignments more readable
typedef unsigned char macAddr[6];

// identifier (for players and PCs) - a unique number
typedef unsigned short Identifier;    //Can change this implementation as needed

// An array struct that gives a parameter for storing the size of the data  
/*
typedef struct {
    int size;
    uint8_t data[];
} arr;  */

//For the raw data to send, use uint8_t* 
//typedef uint8_t* data_p;

//*  Device-level data is managed in dndv_internals


/*      Sending Structures and Functions
    These are the generic sending structures
    See the sending structures per ID under "Bases and IDs"
*/



/*  ID and Data - Data Structure */
typedef struct __attribute__((__packed__)) idsAndData{
    uint8_t BASE;
    uint8_t ID;
    uint8_t* data;   //This "flexible array member" means dynamic allocation will be neccesary
} rcvg_data;           //When you allocate space for this, you want to allocate the size of the struct plus the amount of space you want for the array


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
    Here is the system for all the ID's used within the DnDevice
                    #IMPORTANT NOTE
    In the dndv_comms system, one byte is for bases, one byte is for IDs
    Although the Event Loop Library allows for up to 2^32 IDs, only the first 256 per base are allowed to be sent over our ESP-NOW implementation
    If you have an enumerator below that has more than 256 elements, please refactor by introducing a new base.
*/

/* -  MISC_BASE: For any data received that doesn't have a specific place (yet)  */
ESP_EVENT_DECLARE_BASE(MISC_BASE);  //Defined in the c file
//extern esp_event_base_t MISC_BASE = "MISC_BASE";    //TODO: Make more like this, plus add in DM version?
enum MISC_B_ID{ 
  EVENT_SYS,
  EVENT_TEST,
  EVENT_STRAIGHTTOLOG,
  EVENT_PING
};



/* -  DEVICE_BASE: For global changes to the local device (that may require further messages) 
        Used primarily for editing dndv_internals then updating accordingly
        */
ESP_EVENT_DECLARE_BASE(DEVICE_BASE);
enum DEVICE_B_ID{
    EVENT_KEVIN,            //EVENT_KEYIN!
    EVENT_DM_ACTIVATE,      //When the DM is activated
    EVENT_PLAYER_CHOSEN,    //When a player is selected
    EVENT_PC_CHOSEN,        //When the user selects his/her character
    //EVENT_LOG,
};

//EVENT_KEVIN_LEVIN

/* -  SYNC_BASE: For syncing DMs and Player devices
        Used primarily by dndv_comms
        */
ESP_EVENT_DECLARE_BASE(SYNC_BASE);
enum SYNC_B_ID{
    EVENT_DM_INFO,         //Broadcasted when a device becomes a DM. Transmits the DM
    //EVENT_DM_TITLE_INFO,             //Send the campaign name to 
};

//struct sync_dmInfo{}

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
    These are DM exclusive actions that should only heard by DM_ACTIVATE (minus the logs file)
        TODO: See if this is the best way
*/
ESP_EVENT_DECLARE_BASE(DM_RCV_BASE);
enum DM_RCV_B_ID{
    EVENT_AWAKE_BROADCAST_RCV,      //Broadcasted on awake, so this active DMs can send directly to this new device
    EVENT_SYNC_REQUEST,         //When a player device asks for the DM info
    EVENT_KEYDATA_REQUEST,      //A device requested the player name and character data for a specified key. Return the names.
    EVENT_PC_JOINED,            //A PC has joined the adventure!.
    //EVENT_PC_READY
};



/* BASE CONVERSION
    ESP-NOW defines bases as a character array. These methods convert back and forth to our custom numbering */
//To convert from the ELL Base to our custom numbers
uint8_t EventBase2Num(esp_event_base_t base);
//To convert back to the ELL Base from our custom numbers
esp_event_base_t Num2EventBase(uint8_t num);

enum{          //TODO: stop using this. Fast, but have to maintain separately
    N_MISC_BASE,
    N_DEVICE_BASE,
    N_SYNC_BASE,
    N_OUTGOING_BASE,
    N_DM_RCV_BASE,
}; //Use N_ your base to get the number automatically.
      //Make sure this matches EventBases in dndv_internals.c

//TODO: do this better, store numbers in a struct in that array, then somehow make it visible

/*  TODO:    - DM EXCLUSIVE FUNCTIONS -
    DM exclusive functions should always be verified by the global isDM variable...
   
*/
#endif