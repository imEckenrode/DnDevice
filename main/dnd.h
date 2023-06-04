#pragma once



/*
    This is the module for all the DND (5e) specific items.
    Any battle-relevant info is contained here (turn order, initiative, health)

    This is for any high-level battle sequence functions to call from anywhere.
    Initiative order, attacks, and turn management is all done in this file.

    Lower-level structures, like the identifier definition for character files, are handled by dndv_internals
    
    

*/

//Should initiative be a linked list of players?

//Need 2 things: a table of keys to active fighters, and
//               a list of keys in initiative order