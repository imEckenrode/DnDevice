#pragma once

#include "lvgl/lvgl.h"
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


// All of the ui_events from ui_events.h are instead defined here
void dndv_HP_screenLoading(lv_event_t * e);
void dndv_HP_healXdmg(lv_event_t * e);
void dndv_HP_longRest(lv_event_t * e);
void dndv_HP_shortRest(lv_event_t * e);
void dndv_HP_modifyHpTemp(lv_event_t * e);
void dndv_HP_modifyHpCurrent(lv_event_t * e);
void dndv_HP_modifyHpMax(lv_event_t * e);
void dndv_HP_numConfirm(lv_event_t * e);
void dndv_PP_screenLoading(lv_event_t * e);
void dndv_PP_refresh(lv_event_t * e);
void dndv_PP_exhaustIncrement(lv_event_t * e);
void dndv_PP_condRight(lv_event_t * e);
void dndv_PP_condLeft(lv_event_t * e);
void dndv_PP_condMore(lv_event_t * e);
void dndv_PP_InitScreen(lv_event_t * e);
void dndv_PP_numConfirm(lv_event_t * e);
void dndv_PP_condMoreClose(lv_event_t * e);
void dndv_IS_screenLoading(lv_event_t * e);
void dndv_PC_screenLoading(lv_event_t * e);
void dndv_PC_profPicNext(lv_event_t * e);
void dndv_PC_profPicPrev(lv_event_t * e);
void dndv_PC_dataConfirm(lv_event_t * e);
void dndv_PC_numConfirm(lv_event_t * e);
void dndv_PC_wordConfirm(lv_event_t * e);
void dndv_PC_nameEdit(lv_event_t * e);
void dndv_PC_hpEdit(lv_event_t * e);
void dndv_PC_acEdit(lv_event_t * e);