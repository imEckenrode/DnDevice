#pragma once



/*
    This is the module for all the DND (5e) specific items.
    Any battle-relevant info is contained here (turn order, initiative, health)

    This is for any high-level battle sequence functions to call from anywhere.
    Initiative order, attacks, and turn management is all done in this file.

    Lower-level structures, like the identifier definition for character files, are handled by dndv_internals

*/

//Need 2 things: a table of keys to active fighters, and
//               a list of keys in initiative order




#define MAX_COMBATANT_COUNT 25  //this gives 10 bytes per combatant (8 is just the name...)

struct game{
    Combatant combatantList[MAX_COMBATANT_COUNT];       //This entire array gets sent 
    EnemyData * gmEnemyList;                        //Only allocated for the GM
    Num combatantIndex;
};