//#pragma once
#ifndef DNDV_INTERNALS_H    //Cannot start with an E or an underscore, so may rename to H_...
#define DNDV_INTERNALS_H
#include <stdbool.h>
#include <string.h> //for base comparison
#include "esp_event.h"
#include "esp_err.h"
#include "esp_log.h"

#include "dndv_data.h"
/*               - - - THIS FILE DESCRIPTION - - -
 
 All global varibles and higher-level structures for the DnDevice can be found in here
    For the event loop library and ID-level operations, see dndv_data

 That means functions can be called from the screen, from comms, from console, or from wherever else
    Just import "dndv_internals.h"

    This will allow the usage of the internal variables anywhere that includes "dndv_internals.h"

order:      (global variables on top, then)
    Title
    Struct
    Comment about what the function will do
    Function
*/

// ***Lowest Level Data Types in dndv_data.h***

/*     -- Device Level Data Types --      */

/* The player [and DM] struct (save data into a file)  */
typedef struct __attribute__((__packed__)) player_s{
    KeyIdentifier key;
    char name[MAX_NAME_LENGTH];
    bool canDM;
    bool TrainingWheelsProtocol_Active;
} Player;

/* The character struct (save data into a file) */ 
typedef struct character_s{
    KeyIdentifier key;
    char name[MAX_NAME_LENGTH];
    //char nicknames[MAX_NICKNAME_LENGTH];
    short MaxHP;
    short HP;
    //uint8 level;
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


/*   - Device States -   
All possible states the device can be in, from wakeup to active battle
*/
typedef enum {
    WAKEUP_S,    //On awake, initialize 
    LOGIN_S,        //Key is in, currently logging in
    AWAIT_START_S,      //Character is selected, awaiting DM.
    RECOVERY_S,         //This device can go into recovery mode if messaged with current data from another device upon wakeup

    ADVENTURE_S,        //In the adventure, but not currently battling
    BATTLE_S,           //Currently battling
} deviceStates;


/*  PER USER: Structure for keeping track of the device's user data   */
struct user_s {
    bool isDM;      //Is the current device a DM?
    deviceStates state; //The state the device is in (See "Device States" from abive)
    ContactInfo info;    //The current device's info
    struct Contact devices[MAX_PLAYER_COUNT];
};

/* PER DEVICE: Structure for keeping track of local settings */
struct __attribute__((__packed__)) l_Device{
    bool displayLogs;
};

/*              -- GLOBAL VARIABLES --               */
PC currentPC;        //The currently selected player character          //TODO: Move PC and Player away from being a global
Player currentPlayer;       //The currently selected player
struct user_s current;      //The current user, global to the DnDevice  //IMPORTANT

struct l_Device localDevice;    //Settings for the local device

//TODO: have a pointer to a DM list that holds a dummy value until DM is initialized?

/*          ---- Visible Function Declarations ----          */ 

/*Initialize the global variables correctly
    (Set isDM to False)
*/
void internals_init(void);

/*     --- CRUD Functions ---     */

//Get the key, p_name, and c_name
ContactInfo getMyContactInfo();




/*  If the user just became a DM, start linking all */
void DM_start(void);

// And finally, tests:      
    //(TODO: pull player from storage instead of initializing)      //TODO: MOVE TO dnd.c
void testPCInit(void);  //Initialize a test character into the currentPC 
void testDMInit(void);  //set DM boolean to true (Does not currently clear the currentPlayer)

#endif