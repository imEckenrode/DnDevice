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

/*         -- GLOBAL DEFINITIONS --          */
#define MAX_PLAYER_COUNT 16
#define MAX_NAME_LENGTH 32  //Cound split this into Player/Person and PC/Campaign names
//#define MAX_NICKNAME_LENGTH 8

//Lowest Level Data Types in dndv_data.h

/*     -- Device Level Data Types --      */

/* The player [and DM] struct (save data into a file)  */
typedef struct __attribute__((__packed__)) player_s{
    Identifier id;
    char name[MAX_NAME_LENGTH];
    bool canDM;
    bool TrainingWheelsProtocol_Active;
} Player;

/* The character struct (save data into a file) */ 
typedef struct character_s{
    Identifier id;
    char name[MAX_NAME_LENGTH];
    //char nicknames[MAX_NICKNAME_LENGTH];
    short MaxHP;
    short HP;
    //uint8 level;
} PC;

/*     - Connections Tracking and Naming -
    For DMs, this is the list of players
    For players, this is the list of possible DMs and the campaign names  //, and TODO should stopstops persisting after a 
*/
struct Contact{
    macAddr MAC;
    Identifier Id;
    char p_name[MAX_NAME_LENGTH];   //P is Person/Player (AKA the IRL name)
    char c_name[MAX_NAME_LENGTH];   //C is Campaign or Character Name, depending on if DM or PC
};

/*  PER USER: Structure for keeping track of the device's user data   */
struct user_s{      //change this into a union
    bool isDM;
    char p_name[MAX_NAME_LENGTH];   //P is Person/Player (AKA the IRL name)
    char c_name[MAX_NAME_LENGTH];   //C is Campaign or Character Name, depending on if DM or PC
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

/*          -- Visible Function Declarations --          */ 

/*Initialize the global variables correctly
    (Set isDM to False)
*/
void internals_init(void);

/*  If the user just became a DM, start linking all */
void DM_start(void);


// And finally, tests:      
    //(TODO: pull player from storage instead of initializing)      //TODO: MOVE TO dnd.c
void testPCInit(void);  //Initialize a test character into the currentPC 
void testDMInit(void);  //set DM boolean to true (Does not currently clear the currentPlayer)

#endif