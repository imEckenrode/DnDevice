#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct __attribute__((__packed__)) combatant{
    short key; //Also used to look up if player or enemy in the final product   
    //I don't need to pass Initiative

    bool displayHP;

    //If displaying HP, pass in a Num for HP

    bool isGroup;
        //May add in more health sensitivity (divide into 8?)

    bool isPlayer;     //Temporary, for readability
    bool halfHealth;           //False if full health, otherwise should not be on the board? Could change to two different booleans
    bool active;           //Does this combatant show up at all        //Should this combatant exist on the players' side if not active?
    bool obfuscated;       //Display the name of the combatant?

    char name[12];  //Could make dynamic struct for dynamic name lengths

} Combatant;   //Size 15 = 16 per group



/*

    Groups are treated as special 





*/

