#include "data_pc.h"

#include <string.h>
#include "esp_log.h"



//void pc_init(uint8_t* data){}

void default_pc_init(){
    ESP_LOGW("START", "Hello there!");
    PC = malloc(sizeof(struct fighter));
    PC->allConditions = 0;      //Do this to start all conditions at False (since we're overwriting all else, we malloc instead of calloc)

    PC->AC = 10;
    PC->HP = 20;
    PC->trueMaxHP = 30;
    PC->maxHP = PC->trueMaxHP;
    PC->condition.charmed = true;

    ESP_LOGW("OUTPUT", "HP: %d, MAX: %d, AC: %d, Conditions: %x", PC->HP, PC->maxHP, PC->AC, PC->allConditions);

    ESP_LOGW("SIZE", "%d", sizeof(*PC));

    //free(PC); if we ever become the DM
}

 
struct fighter readPC(){
    return *PC;
}

/* REMOVE: MOVE ALL BELOW TO ELSEWHERE */
void setHP(int a){
    PC->HP = a;
}

void adjustHP(int up){
    int temp = PC->HP + up;
    if(temp >= PC->maxHP){
        setHP(PC->maxHP);
    }else if(temp <= 0){
        setHP(0);
    }else{
        setHP(temp);
    }
}