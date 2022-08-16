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
#define MAX_NAME_LENGTH 32  //Cound split this into Player and PC names
//#define MAX_NICKNAME_LENGTH 8

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

//For the raw data to send
//typedef uint8_t bytes[];

/*     -- Device Level Data Types --      */

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

/* FOR DM: Keeps track of connected characters.
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

/*       -- GLOBAL VARIABLES --          */
Character currentPC;        //The currently selected player character
Player currentPlayer;       //The currently selected player
struct user_s currentUser;      //The current user, global to the DnDevice  //IMPORTANT


/*      -- Visible Function Declarations --       */ 

/* Initialize the non-volatile storage library to persist data 
    Required for: ESP-NOW   */
void nvs_init(void);

/*  If the user just became a DM, start linking all */
void DM_start(void);


// And finally, tests:      
    //(TODO: pull player from storage instead of initializing)      //TODO: MOVE TO dnd.c
void testPCInit(void);  //Initialize a test character into the currentPC 
void testDMInit(void);  //set DM boolean to true (Does not currently clear the currentPlayer)

#endif