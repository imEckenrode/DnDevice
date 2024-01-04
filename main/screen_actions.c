#include "screen_actions.h"

#include "data_pc.h"
#include "helper_functions.h"

#include "esp_log.h"
//Here's all the externs for all the variables I manipulate
//Never need to extern functions, but here 

struct fighter dndv_getPC(){
   return readPC();
}

#include "stdlib.h"
#include "esp_log.h"

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

int dndv_healPC(char* input){
    int heal = (int) stringToLong(input);
    adjustHP(heal);

    return PC->HP;  //REMOVE: This will be factored out
}
