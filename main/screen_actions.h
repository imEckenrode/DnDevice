#pragma once

/*

This maps all display changes to their respective actions.

    For every screen action that manipulates a variable, add a function here

Start with dndv so it is clear in ui.c which functions are custom
*/

//Getting and setting data is done by creating a struct copy, updating the variables, and posting it back
struct fighter dndv_getPC();

struct fighter dndv_updatePC();

int dndv_healPC(char* input); //Adjust HP by this number and return the resulting HP



//Specific initializations for pulling the values into a screen from the database

//TODO: create the updateScreen bit with extern lv_obj_t * ui_hpInfoScrn;
