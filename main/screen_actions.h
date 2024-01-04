#pragma once

/*

This maps all display changes to their respective actions.

    For every screen action that manipulates a variable, add a function here

Start with dndv so it is clear in ui.c which functions are custom
*/

// struct playerCharacter *dndv_getPCPointer();

int dndv_healPC(char* input); //Adjust HP by this number and return the resulting HP



//Specific initializations for pulling the values into a screen from the database

//TODO: create the updateScreen bit with extern lv_obj_t * ui_hpInfoScrn;
