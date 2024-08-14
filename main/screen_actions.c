#include "screen_actions.h"

#include "data_pc.h"
#include "helper_functions.h"
#include "stdlib.h"
#include "esp_log.h"
#include "screen_control.h"
//Here's all the externs for all the variables I manipulate
//Never need to extern functions, but here 

#define TAG "ScreenActions"

#define SECRET_CANCEL_CONSTANT -29135 //If there is no input to the field, default to this value and prevent value modifications (TODO: Use for char type too)

void dndv_refresh(){
    // This takes long which makes it work? ScreenLoading should be deleted, exclusively use refresh (SCREEN_LOADED)
    writePC(readPC());
}

void dndv_textAreaClearAndRelabel(lv_obj_t * t, char* label){
    lv_textarea_set_placeholder_text(t, label);
    lv_textarea_set_text(t, "");
}

#define HP_MODIFY_TEXT_LABEL_TEMP "Enter New TempHP"
#define HP_MODIFY_TEXT_LABEL_CURRENT "Insert HP Amount"
#define HP_MODIFY_TEXT_LABEL_MAX "Enter New MaxHP"
#define HP_MODIFY_TEXT_LABEL_SHORT_REST "Enter HP Gained from Rest"


void dndv_HP_screenLoading(lv_event_t * e){dndv_refresh();}
void dndv_HP_healXdmg(lv_event_t * e){return;}
void dndv_HP_longRest(lv_event_t * e){longRest();}
void dndv_HP_shortRest(lv_event_t * e){dndv_textAreaClearAndRelabel(ui_HP_numTextArea, HP_MODIFY_TEXT_LABEL_SHORT_REST);} //TODO make a popup and use numConfirm
void dndv_HP_modifyHpTemp(lv_event_t * e){dndv_textAreaClearAndRelabel(ui_HP_numTextArea, HP_MODIFY_TEXT_LABEL_TEMP);}
void dndv_HP_modifyHpCurrent(lv_event_t * e){dndv_textAreaClearAndRelabel(ui_HP_numTextArea, HP_MODIFY_TEXT_LABEL_CURRENT);}
void dndv_HP_modifyHpMax(lv_event_t * e){ESP_LOGI(TAG, "Editing Max"); dndv_textAreaClearAndRelabel(ui_HP_numTextArea, HP_MODIFY_TEXT_LABEL_MAX);}
void dndv_HP_numConfirm(lv_event_t * e){
    char* label = lv_textarea_get_placeholder_text(ui_HP_numTextArea);
    //NOTE: Casting it to a short could cause over/underflow and there's no guarantee negatives stay
    short num = stringToLong(lv_textarea_get_text(ui_HP_numTextArea), SECRET_CANCEL_CONSTANT);
    //If nothing was input, fall back to original value
    if(num == SECRET_CANCEL_CONSTANT){return;}
    if(strcmp(label, HP_MODIFY_TEXT_LABEL_TEMP)==0){
        setTempHP(num);
        ESP_LOGI(TAG, "Temp Triggered");
    }else if(strcmp(label, HP_MODIFY_TEXT_LABEL_CURRENT)==0){
        setHP(num);
    }else if(strcmp(label, HP_MODIFY_TEXT_LABEL_MAX)==0){
        setMaxHP(num); //trueMaxHP is the actual maxHP
    }else if(strcmp(label, HP_MODIFY_TEXT_LABEL_SHORT_REST)==0){
        shortRest(num);
    }
}


void PP_displayConditions(){ //TODO: For later additions, this will utilize "struct conditions"
    // Display the correct conditions. TOOD: Calculate on the fly here (vs. going through a player)
    return;
}


void dndv_PP_screenLoading(lv_event_t * e){dndv_refresh();}
void dndv_PP_refresh(lv_event_t * e){return;}

void dndv_PP_toggleCond(lv_event_t * e){  //All conditions toggle this and we update accordingly here
    uint8_t pos = ((uint8_t) lv_obj_get_user_data(lv_event_get_target(e))) + condPage*(DNDV_CONDITIONS_COUNT/DNDV_UI_CONDITIONS_PAGE_COUNT); //This should always be 5 unless we do a huge structural change
    toggleCondition(pos2Cond[pos]);
};    //TODO: If implementing Long Press To Clear, catch Long Press and manually escape if pressed here


void dndv_PP_exhaustIncrement(lv_event_t * e){return;}
void dndv_PP_condRight(lv_event_t * e){dndv_set_condPage(true,1);}
void dndv_PP_condLeft(lv_event_t * e){dndv_set_condPage(true,-1);}
void dndv_PP_condMore(lv_event_t * e){ui_PPP_update_conditions();;}
void dndv_PP_InitScreen(lv_event_t * e){return;} //Navigate to Initiative Screen...can hijack with Player Creation
void dndv_PP_numConfirm(lv_event_t * e){
    short num = stringToLong(lv_textarea_get_text(ui_PP_acTextArea), SECRET_CANCEL_CONSTANT);
    if(!lv_obj_has_flag(ui_PP_acCover_half, LV_OBJ_FLAG_HIDDEN)){setCover(2);}
    else if(!lv_obj_has_flag(ui_PP_acCover_threeQuarter, LV_OBJ_FLAG_HIDDEN)){setCover(5);}
    else if(!lv_obj_has_flag(ui_PP_acCover_total, LV_OBJ_FLAG_HIDDEN)){setCover(7);}   //Full cover grants immunity to attacks. TODO: migrate cover to 2 bits of info
    else{setCover(0);}
    if(num != SECRET_CANCEL_CONSTANT){setAC(num);}
    lv_textarea_set_text(ui_PP_acTextArea, "");
}

void dndv_PP_condMoreClose(lv_event_t * e){ui_PP_update_conditions();}
void dndv_PPP_toggleCond(lv_event_t * e){
    uint8_t pos = ((uint8_t) lv_obj_get_user_data(lv_event_get_target(e))); //This should always be 5 unless we do a huge structural change
    toggleCondition(pos2Cond[pos]);
};


void dndv_IS_screenLoading(lv_event_t * e){return;}

#define PC_INPUT_LABEL_SET_NAME "Enter Name"
#define PC_INPUT_LABEL_SET_HP "Enter Max HP"
#define PC_INPUT_LABEL_SET_AC "Enter AC"
#define PC_INPUT_LABEL_CHANGE_NAME "Enter New Name"
#define PC_INPUT_LABEL_CHANGE_HP "Enter New Max HP"
#define PC_INPUT_LABEL_CHANGE_AC "Enter New AC"

void dndv_PC_screenLoading(lv_event_t * e){return;}
void dndv_PC_profPicNext(lv_event_t * e){setPFP(readPC().pfp+1);}
void dndv_PC_profPicPrev(lv_event_t * e){setPFP(readPC().pfp-1);
        _ui_flag_modify(ui_PC_Input, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE); //Temporary for testing purposes
        dndv_textAreaClearAndRelabel(ui_PC_InputTextArea, PC_INPUT_LABEL_SET_NAME);}
void dndv_PC_dataConfirm(lv_event_t * e){return;} //Looks Good, Continue
void dndv_PC_inputConfirm(lv_event_t * e){
    char* label = lv_textarea_get_placeholder_text(ui_PC_InputTextArea);
    char* input = lv_textarea_get_text(ui_PC_InputTextArea);
    if(*input!='\0'){   //If the name is empty, we're not changing it
        setName(input);
    }
    if(strcmp(label, PC_INPUT_LABEL_SET_NAME)==0){
        _ui_flag_modify(ui_PC_numInput, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE); // We edit ui flags within ui.c normally, but we're manually opening this here
        dndv_textAreaClearAndRelabel(ui_PC_numTextArea, PC_INPUT_LABEL_SET_HP);
    }
}

void dndv_PC_numConfirm(lv_event_t * e){
    char* label = lv_textarea_get_placeholder_text(ui_PC_numTextArea);
    short num = stringToLong(lv_textarea_get_text(ui_PC_numTextArea), SECRET_CANCEL_CONSTANT);
    //If nothing was input, fall back to original value
    if(num != SECRET_CANCEL_CONSTANT){
        if(strstr(label, "AC")!=0){ //If AC is found
            setAC(num);
        }else{
            setTrueMaxHP(num);
        }
    }
    if(strcmp(label, PC_INPUT_LABEL_SET_HP)==0){ //If the labels match
        _ui_flag_modify(ui_PC_numInput, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE); // We edit ui flags within ui.c normally, but we're manually opening this here
        dndv_textAreaClearAndRelabel(ui_PC_numTextArea, PC_INPUT_LABEL_SET_AC);
    } //In all other three scenarios, we are closing out
}
void dndv_PC_nameEdit(lv_event_t * e){dndv_textAreaClearAndRelabel(ui_PC_InputTextArea, PC_INPUT_LABEL_CHANGE_NAME);}
void dndv_PC_hpEdit(lv_event_t * e){dndv_textAreaClearAndRelabel(ui_PC_numTextArea, PC_INPUT_LABEL_CHANGE_HP);}
void dndv_PC_acEdit(lv_event_t * e){dndv_textAreaClearAndRelabel(ui_PC_numTextArea, PC_INPUT_LABEL_CHANGE_AC);}

//ESP_LOGI(TAG,"Placement Correct"); dndv_textAreaClearAndRelabel(ui_PC_numInput, "Hi");