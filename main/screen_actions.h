#pragma once

/*
This maps all display changes to their respective actions.

    For every screen action that manipulates a variable, add a function here

Start with dndv so it is clear in ui.c which functions are custom

    Updating the screen is then done in screen_control
*/

//Getting and setting data is done by creating a struct copy, updating the variables, and posting it back
struct fighter dndv_getPC();
struct fighter dndv_setPC();

void dndv_healPC(char* input); //Adjust HP by this number (negative numbers mean down)

void dndv_refresh();