#include "screen_actions.h"

#include "data_pc.h"
#include "helper_functions.h"
#include "stdlib.h"
#include "esp_log.h"
//Here's all the externs for all the variables I manipulate
//Never need to extern functions, but here 

#define TAG "ScreenActions"

struct fighter dndv_getPC(){
   return readPC();
}

void dndv_healPC(char* input){
    int heal = (int) stringToLong(input);
    adjustHP(heal);
}

void dndv_refresh(){
        //TODO: Phase this out
    //Since data change triggers a ui_refresh, we do this
    writePC(readPC());
}

void dndv_textAreaClearAndRelabel(lv_obj_t * t, char* label){
    lv_textarea_set_placeholder_text(t, label);
    lv_textarea_set_text(t, "");
}

#define HP_MODIFY_TEXT_LABEL_TEMP "Enter New TempHP"
#define HP_MODIFY_TEXT_LABEL_CURRENT "Insert HP Amount"
#define HP_MODIFY_TEXT_LABEL_MAX "Enter New MaxHP"

void dndv_HP_screenLoading(lv_event_t * e){dndv_refresh();}
void dndv_HP_healXdmg(lv_event_t * e){return;}
void dndv_HP_longRest(lv_event_t * e){return;}
void dndv_HP_shortRest(lv_event_t * e){return;}
void dndv_HP_modifyHpTemp(lv_event_t * e){dndv_textAreaClearAndRelabel(ui_HP_numTextArea, HP_MODIFY_TEXT_LABEL_TEMP);}
void dndv_HP_modifyHpCurrent(lv_event_t * e){dndv_textAreaClearAndRelabel(ui_HP_numTextArea, HP_MODIFY_TEXT_LABEL_CURRENT);}
void dndv_HP_modifyHpMax(lv_event_t * e){ESP_LOGI(TAG, "Editing Max"); dndv_textAreaClearAndRelabel(ui_HP_numTextArea, HP_MODIFY_TEXT_LABEL_MAX);}
void dndv_HP_numConfirm(lv_event_t * e){
    char* label = lv_textarea_get_placeholder_text(ui_HP_numTextArea);
    //NOTE: Casting it to a short could cause over/underflow and there's no guarantee negatives stay
    short num = stringToLong(lv_textarea_get_text(ui_HP_numTextArea));
    if(strcmp(label, HP_MODIFY_TEXT_LABEL_TEMP)==0){
        setTempHP(num)
        ESP_LOGI(TAG, "Temp Triggered");
    }else if(strcmp(label, HP_MODIFY_TEXT_LABEL_CURRENT)==0){
        setHP(num)
    }else if(strcmp(label, HP_MODIFY_TEXT_LABEL_MAX)==0){
        setMaxHP(num) //trueMaxHP is the actual maxHP
    }
}

void dndv_PP_screenLoading(lv_event_t * e){dndv_refresh();}
void dndv_PP_refresh(lv_event_t * e){return;}
void dndv_PP_exhaustIncrement(lv_event_t * e){return;}
void dndv_PP_condRight(lv_event_t * e){return;}
void dndv_PP_condLeft(lv_event_t * e){return;}
void dndv_PP_condMore(lv_event_t * e){return;}
void dndv_PP_InitScreen(lv_event_t * e){return;}
void dndv_PP_numConfirm(lv_event_t * e){return;}
void dndv_PP_condMoreClose(lv_event_t * e){return;}
void dndv_IS_screenLoading(lv_event_t * e){return;}
void dndv_PC_screenLoading(lv_event_t * e){return;}
void dndv_PC_profPicNext(lv_event_t * e){return;}
void dndv_PC_profPicPrev(lv_event_t * e){return;}
void dndv_PC_dataConfirm(lv_event_t * e){return;}
void dndv_PC_numConfirm(lv_event_t * e){return;}
void dndv_PC_wordConfirm(lv_event_t * e){return;}
void dndv_PC_nameEdit(lv_event_t * e){return;}
void dndv_PC_hpEdit(lv_event_t * e){return;}
void dndv_PC_acEdit(lv_event_t * e){return;}

//ESP_LOGI(TAG,"Placement Correct"); dndv_textAreaClearAndRelabel(ui_PC_numInput, "Hi");