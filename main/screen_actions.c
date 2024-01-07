#include "screen_actions.h"

#include "data_pc.h"
#include "helper_functions.h"
#include "stdlib.h"
#include "esp_log.h"
//Here's all the externs for all the variables I manipulate
//Never need to extern functions, but here 

struct fighter dndv_getPC(){
   return readPC();
}

long int stringToLong(char* input){
    char *leftovers;
    long num = strtol(input, &leftovers, 10);

    //This stops at the first character that is not a digit, plus, minus, or whitespace
    //Could check for garbage/success by looking at leftovers

    if(*leftovers!='\0'){
        ESP_LOGE("DnDevice", "Could not parse full string to number!");

        //TODO: throw an error
    }

    return num;
}

void dndv_healPC(char* input){
    int heal = (int) stringToLong(input);
    adjustHP(heal);
}

void dndv_refresh(){
    //temporarily, 
    writePC(readPC());
}


void dndv_HP_healXdmg(lv_event_t * e){return;}
void dndv_HP_modifyHpTemp(lv_event_t * e){return;}
void dndv_HP_modifyHpCurrent(lv_event_t * e){return;}
void dndv_HP_modifyHpMax(lv_event_t * e){return;}
void dndv_PP_refresh(lv_event_t * e){return;}
void dndv_PP_condRight(lv_event_t * e){return;}
void dndv_PP_condLeft(lv_event_t * e){return;}
void dndv_PP_condMore(lv_event_t * e){return;}
void dndv_PP_InitScreen(lv_event_t * e){return;}
void dndv_PP_condMoreClose(lv_event_t * e){return;}