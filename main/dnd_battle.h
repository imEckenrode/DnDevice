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


typedef struct __attribute__((__packed__)) combatant{
    char name[8];  //Could make dynamic struct for dynamic name lengths
    Key key;          //Also used to look up if player or enemy
    Num initiative;       //This will be a "Num"
    bool isPlayer;     //Temporary, for readability
    bool halfHealth;           //False if full health, otherwise should not be on the board? Could change to two different booleans
    bool active;           //Does this combatant show up at all        //Should this combatant exist on the players' side if not active?
    bool obfuscated;       //Display the name of the combatant?
} Combatant;



#define MAX_COMBATANT_COUNT 25  //this gives 10 bytes per combatant (8 is just the name...)


//And for the GM only:
typedef struct __attribute__((__packed__)) gm_combatant_data{
    Key key;
    short HP;
    short maxHP;
    short AC;
    short atkMod;
    bool hasLegendaryActions;       //This could be a universal property?
} EnemyData;


struct game{
    Combatant combatantList[MAX_COMBATANT_COUNT];       //This entire array gets sent 
    EnemyData * gmEnemyList;                        //Only allocated for the GM
    Num combatantIndex;
};