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
 
 All global varibles and internal workings for the DnDevice can be found in here
    For the event loop library, structs, and ID-level operations, see dndv_data

 That means functions can be called from the screen, from comms, from console, or from wherever else
    Just import "dndv_internals.h"

    This will allow the usage of the globally-scoped variables anywhere that includes "dndv_internals.h"
*/


/*   - Device States -                                          (TO IMPLEMENT LATER)
All possible states the device can be in, from wakeup to active battle
typedef enum {
    WAKEUP_S,    //On awake, initialize 
    LOGIN_S,        //Key is in, currently logging in
    AWAIT_START_S,      //Character is selected, awaiting DM.
    RECOVERY_S,         //This device can go into recovery mode if messaged with current data from another device upon wakeup

    ADVENTURE_S,        //In the adventure, but not currently battling
    BATTLE_S,           //Currently battling
} deviceStates;
*/

/* CURRENT DEVICE SETTINGS: Structure for keeping track of local settings 
struct __attribute__((__packed__)) cd_settings{                 //(TO IMPLEMENT LATER)
    bool displayLogs;               
};
*/

/*  CURRENT DEVICE: Structure for keeping track of the device's user data   */
struct __attribute__((__packed__)) current_device_s {
    //deviceStates state;     //The state the device is in (See "Device States" above)
    //struct cd_settings settings;
    ContactInfo info;       //The current device's info                             //TODO: If you need a few more bytes, remove this and format the rest to reference currentPlayer
    struct ContactAddressBook *contacts;
    bool isDM;          //Is the current device a DM?
    //struct cd_settings settings;
};


/*              -- GLOBAL VARIABLES --               */
struct current_device_s current;      //The current user, global to the DnDevice  //IMPORTANT


PC currentPC;        //The currently selected player character          //TODO: Move PC and Player away from being a global     [Initialize LATER]
Player currentPlayer;       //The currently selected player


/*          ---- Visible Function Declarations ----          */ 

/*   Initialize all the global variables correctly
            (Set isDM to False, allocate the hashmap, etc)
*/
void globals_init(void);

/*     --- CRUD Functions ---     */

//Get the key, p_name, and c_name of the local device
ContactInfo getMyContactInfo();

/*  -- Contact Data System --
CRUD functions primarily use the MAC address, since the MAC should be unique per entry*/
short sizeOfContactBook();

//bool contactExistWithMAC(macAddr mac);
//returns -1 on non-existent
short indexOfContactWithMAC(macAddr mac);

bool createContact(ContactAddress cAddr);
ContactAddress readContact(macAddr mac);
bool createOrUpdateContact(ContactAddress cAddr);
bool updateContact(ContactAddress cAddr);
bool deleteContact(macAddr mac);

ContactAddress readContactByKey(Key key);



/*  If the user just became a DM, start linking all */
void DM_start(void);

// And finally, tests:      
    //(TODO: pull player from storage instead of initializing)      //TODO: MOVE TO dnd.c?
void testPCInit(void);  //Initialize a test character into the currentPC 
void testDMInit(void);  //set DM boolean to true (Does not currently clear the currentPlayer)

#endif