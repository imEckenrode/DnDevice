#pragma once
//#ifndef the_functions.h   //(I think these need quotations around the name)
//# define the_functions.h

#include <stdbool.h>



/* What is this?

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

/*

// current_context tracks what state the device is in, so it cannot attack when no one is logged in
struct context_s{
    bool connected;         //Set to True when the device connects to the DM    (set DM to True)
    bool loggedIn;          //Set to True when the player
    bool onePC;             //Set to True if one character is selected 
    bool DMHere;            //Set to True if the DM is selected (so there's no point sending ESPNow to yourself in the event of MultiPlayers)
    //bool multiPlayers;       //Set to True if the device is hosting more than one player (which means it has to worry about routing) DM included
} current_context = {false,false,false,false};

*/

void nvs_init(void);

//#endif