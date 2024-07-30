#include "helper_functions.h"
//This isn't found for some reason...that's why screen_actions.c has a duplicate
#include "stdlib.h"
#include "esp_log.h"

long int stringToLong(char* input, int defaultVal){
    char *leftovers;

    if(*input == '\0'){
        return defaultVal;
    }

    long num = strtol(input, &leftovers, 10);

    //This stops at the first character that is not a digit, plus, minus, or whitespace
    //Could check for garbage/success by looking at leftovers

    if(*leftovers!='\0'){
        ESP_LOGW("DnDevice", "Could not parse full string to number!");

        //TODO: throw an error
    }

    return num;
}
