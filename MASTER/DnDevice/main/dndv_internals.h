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
    AWAIT_START_S,      //Character is selected, awaiting GM.
    RECOVERY_S,         //This device can go into recovery mode if messaged with current data from another device upon wakeup

    ADVENTURE_S,        //In the adventure, but not currently battling
    BATTLE_S,           //Currently battling
} deviceStates;
*/

/* CURRENT DEVICE SETTINGS: Structure for keeping track of local settings  */
struct __attribute__((__packed__)) cd_settings{
    bool displayLogs;               
};

/*  CURRENT DEVICE: Structure for keeping track of the device's user data   */
struct __attribute__((__packed__)) current_device_s {
    //deviceStates state;     //The state the device is in (See "Device States" above)
    Key myKey;
    struct gmInfo gmInfo;
    union {
        struct ContactAddressBook *contacts;
        struct PnC_s *my; //would
    };                                                  //Anonymous Union works in C11
    bool isGM;          //Is the current device a GM?
    struct cd_settings settings;
};



/*              -- GLOBAL VARIABLES --               */
struct current_device_s current;      //The current user, global to the DnDevice  //IMPORTANT

/*          ---- Visible Function Declarations ----          */ 

/*   Initialize all the global variables correctly
            (Set isGM to False, allocate the hashmap, etc)*/
void globals_init(void);

/*               --- CRUD Functions ---                 */
//Check if the current device is a GM
bool isGM();
bool isPlayer();
//Turn GM Status on or off (should be triggered through an event)
bool updateGMStatus(bool isGM);

//For the GM_MAC, see GM_MAC in dndv_comms (TODO?)

ContactInfo getMyContactInfo();
bool updateMyContactInfo(ContactInfo info);

/*  -- Player Updating And Retrieving --  */
Key getMyKey();
Player getMyPlayer();
PC getMyPC();

bool updateMyKey(Key newKey);
bool updateMyPlayer(Player player);
bool updateMyPC(PC pc);

//Get the key, p_name, and c_name of the local device
ContactInfo getMyContactInfo();

/*  -- Contact Data System --
CRUD functions primarily use the MAC address, since the MAC should be unique per entry*/
short sizeOfContactBook();

bool contactExistWithMAC(macAddr mac);
//returns -1 on non-existent
short indexOfContactWithMAC(macAddr mac);
bool createContact(ContactAddress cAddr);
ContactAddress readContact(macAddr mac);
bool createOrUpdateContact(ContactAddress cAddr);
bool updateContact(ContactAddress cAddr);
bool deleteContact(macAddr mac);

ContactAddress readContactByKey(Key key);


/*  - Updating Local Player Data -          TODO: This is most likely overwritten by above, so delete this */
bool updateCurrentKey(Key key);
bool updateCurrentPlayer(Player player);
bool updateCurrentPC(PC character);



/*  If the user just became a GM, start linking all */
void GM_start(void);

// And finally, tests:      
    //(TODO: pull player from storage instead of initializing)      //TODO: MOVE TO dnd.c?
void testPCInit(void);  //Initialize a test character into the currentPC 
void testGMInit(void);  //set GM boolean to true (Does not currently clear the currentPlayer)

#endif