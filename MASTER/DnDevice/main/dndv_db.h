#pragma once
#include "dndv_data.h"

/*     -  -  -     The Database      -  -  -      
    This is where the permanent files are managed/held.

    This includes character files, key assignments per player, 
    
    This implementation can change as needed, and functions use the dndv_data structures for players and characters to remain universal

    Include this for access to the permanent files.
*/

esp_err_t db_write_player(Key key, Player player);

esp_err_t db_write_pc(Key key, PC pc);

Player db_read_player(Key key);

PC db_read_pc(Key key);

//TODO: Maybe code in a method for a PC to check locally for data, then/and ask for the DM's data