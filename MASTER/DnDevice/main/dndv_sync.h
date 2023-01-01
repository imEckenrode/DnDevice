#pragma once // Is this needed? Is anything including this?
#include "dndv_comms.h"
#include "dndv_db.h"

/*
    Before the game can start, the devices need to sync up.

    There are two sides to this: the GM syncing, and the players syncing.

    This includes the following:
    
    Upon wakeup, broadcast so GMs can send you the data
    Upon becoming a GM, let everyone know so they can join your game
    Players asking for player/PC data
    
    And finally, starting the game is contained in here.
*/