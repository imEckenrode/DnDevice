#pragma once
#include "nvs_flash.h"
#include "dndv_data.h"

/*     -  -  -     The Database      -  -  -      
    This is where the permanent files are managed/held.

    This includes character files, key assignments per player, 
    
    This implementation can change as needed, and functions use the dndv_data structures for players and characters to remain universal

    Include this for access to the permanent files.
*/

struct __attribute__((__packed__)) pcDesc{
    Key key;
    Name name;
};

typedef struct __attribute__((__packed__)){
    Player playerInfo;
    struct pcDesc pcList[];    //NOTE: can only send 8 out of ESP NOW at a time, but that's not a DB problem
} PlayerFile;

//This struct is for any additional attributes we would want to attach to a PC
typedef struct __attribute__((__packed__)){
    PC pc;
} PCFile;

/*
esp_err_t db_write_player(Key key, PlayerFile player);
esp_err_t db_write_pc(Key key, PCFile pc);
PlayerFile db_read_player(Key key);
PCFile db_read_pc(Key key);

*/
//TODO: Maybe code in a method for a PC to check locally for data, then/and ask for the DM's data