#pragma once

#include "lvgl/lvgl.h"
#include "ui/ui.h" //This is circular but allowed because we define both files once

/*
This maps all display changes to their respective actions.

    For every screen action that manipulates a variable, add a function here

Custom events are also defined here if triggered by a user action
    Start with dndv so it is clear in ui.c which functions are custom

    Updating the screen is then done in screen_control
*/
// This forces a refresh by pretending to update the local PC
void dndv_refresh();

void dndv_textAreaClearAndRelabel(lv_obj_t * t, char* label);

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
void dndv_PP_toggleCond(lv_event_t * e);
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
void dndv_PC_inputConfirm(lv_event_t * e);
void dndv_PC_numConfirm(lv_event_t * e);
void dndv_PC_nameEdit(lv_event_t * e);
void dndv_PC_hpEdit(lv_event_t * e);
void dndv_PC_acEdit(lv_event_t * e);