//#pragma once
#ifndef DNDV_INTERNALS_H    //Cannot start with an E or an underscore, so may rename to H_...
#define DNDV_INTERNALS_H
#include <stdbool.h>
#include "esp_event.h"
#include "nvs_flash.h"

/*               - - - THIS FILE DESCRIPTION - - -
 
 All global varibles and structures for the DnDevice can be found in here


 That means functions can be called from the screen, from comms, from console, or from wherever else
    Just import "dndv_internals.h"

    This will allow the usage of the internal variables anywhere that includes "dndv_internals.h"

order:      (global variables on top, then)
    Title
    Struct
    Comment about what the function will do
    Function
*/

/*         - GLOBAL DEFINITIONS -          */
#define MAX_PLAYER_COUNT 16
#define MAX_NAME_LENGTH 64  //Cound split this into Player and PC names
//#define MAX_NICKNAME_LENGTH 8

/*     - Lowest Level Data Types -      */

//  THIS IS AN ARRAY DATA TYPE! MacAddr is defined to make any MAC address assignments more readable
typedef unsigned char macAddr[6];

// identifier (for players and PCs) - a unique number
typedef unsigned short Identifier;    //Can change this implementation as needed


/*     - Device Level Data Types -      */

/* The character struct (save data into a file) */
typedef struct character_s{
    Identifier id;
    char name[MAX_NAME_LENGTH];
    //char nicknames[MAX_NICKNAME_LENGTH];
    short MaxHP;
    short HP;
    //uint8 level;
} Character;

/* The player [and DM] struct (save data into a file)  */
typedef struct player_s{
    Identifier id;
    char name[MAX_NAME_LENGTH];
    bool canDM;
    //bool babyMode;    //Training Wheels Protocol
} Player;


/*  & FOR DM: Keeps track of connected characters.
        Initialize this when 
*/
struct PlayerDevice{
    macAddr MAC;
    Identifier PlayerId;
};

struct PlayerDeviceList{
    struct PlayerDevice players[MAX_PLAYER_COUNT];
};


/*  PER USER: Structure for keeping track of the device's user data   */
struct user_s{      //change this into a union
    bool DM;
    Player* player;
    Character* character;
};





/*       - GLOBAL VARIABLES -          */
Character currentPC;        //The currently selected player character
Player currentPlayer;       //The currently selected player
struct user_s currentUser;      //The current user, global to the DnDevice  //IMPORTANT


/*      - Visible Function Declarations -       */ 

/* Initialize the non-volatile storage library to persist data 
    Required for: ESP-NOW   */
void nvs_init(void);

/*  If the user just became a DM, start linking all */
void DM_start(void);


// And finally, tests:      
    //(TODO: pull player from storage instead of initializing)      //TODO: MOVE TO dnd.c
void testPCInit(void);  //Initialize a test character into the currentPC 
void testDMInit(void);  //set DM boolean to true (Does not currently clear the currentPlayer)




/*          -- EVENT LOOP --    
    This is the handle that alerts all code when something is updated.

    This can be an ESP-NOW receive, a local battle change, or connections and settings data

    To receive data, call something like esp_event_handler_instance_register_with(dndv_event_h, ESP_EVENT_ANY_BASE, ESP_EVENT_ANY_ID,rcvToLog,NULL,NULL);
                                                                                                EVENT_BASE_HERE     EVENT_ID_HERE      ^function name
    FORMATTING:
        Declare and define the 
*/

//The handle for all dndevice events
esp_event_loop_handle_t dndv_event_h;

//Initialize the event loop library
void eventLoop_init(void);

/* MISC_BASE: For any data received that doesn't have a specific place (yet)  */
ESP_EVENT_DECLARE_BASE(MISC_BASE);  //Defined in the c file
//ESP_EVENT_DEFINE_BASE(MISC_BASE);
//extern esp_event_base_t MISC_BASE = "MISC_BASE";    //TODO: Make more like this, plus add in DM version

//A temporary example of IDs for this
enum { 
  EVENT_FIGHT_ACTION,
  EVENT_FIGHT_CONTROL,
  EVENT_SYS,
  EVENT_TEST,
  EVENT_STRAIGHTTOLOG
};

/* DEVICE_BASE: For global changes to the local device (that may require further messages) 
        Used primarily for editing dndv_internals then updating accordingly

ESP_EVENT_DECLARE_BASE(DEVICE_BASE);
ESP_EVENT_DEFINE_BASE(DEVICE_BASE);
*/
//A temporary example of IDs for this
enum {
    EVENT_KEVIN,            //EVENT_KEYIN!
    EVENT_DM_ACTIVATE,      //When the DM is activated
    EVENT_PLAYER_CHOSEN,    //When a player is selected
    EVENT_PC_CHOSEN,        //When the user selects his/her character
    //EVENT_LOG,
};


/* SYNC_BASE: For syncing DMs and Player devices
        Used primarily by dndv_comms

ESP_EVENT_DECLARE_BASE(SYNC_BASE);
ESP_EVENT_DEFINE_BASE(SYNC_BASE);
*/
//A temporary example of IDs for this
enum {
    EVENT_DM_BROADCAST_RCV,         //Broadcasted when a device becomes a DM. Transmits the DM
    EVENT_DM_TITLE_INFO,             //Send the campaign name to 
};




/*  And finally,
DM_RCV_BASE: For all events targeted to the DM from other devices
    These are DM exclusive actions that should only heard by DM_ACTIVATE (minus the logs file)
        TODO: See if this is the best way

ESP_EVENT_DECLARE_BASE(DM_RCV_BASE);
ESP_EVENT_DEFINE_BASE(DM_RCV_BASE);
*/
//A temporary example of IDs for this
enum {
    EVENT_AWAKE_BROADCAST_RCV,      //Broadcasted on awake, so this active DMs can send directly to this new device
    EVENT_SYNC_REQUEST,         //When a player device asks for the DM info
    EVENT_KEYDATA_REQUEST,      //A device requested the player name and character data for a specified key. Return the names.
    EVENT_PC_JOINED,            //A PC has joined the adventure!
    //EVENT_PC_READY
};


/*  TODO:    - DM EXCLUSIVE FUNCTIONS -
    DM exclusive functions should always be verified by the global isDM variable...
   
*/


#endif