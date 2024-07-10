#include "data_pc.h"

#include "device.h"
#include <string.h>
#include "esp_log.h"
#include "esp_event.h"


//void pc_init(uint8_t* data){}

// We use a spinlock (like a mutex) while accessing the PC data to make sure we don't access from two places at once
// Use taskENTER_CRITICAL(&pcDataSpinlock) and taskEXIT_CRITICAL(&spinlock)
static portMUX_TYPE pcDataSpinlock = portMUX_INITIALIZER_UNLOCKED;


void default_pc_init(){
    ESP_LOGW("START", "Hello there!");
    PC = calloc(1,sizeof(struct fighter));
    PC->allConditions = 0;      //Do this to start all conditions at False (since we're overwriting all else, we malloc instead of calloc)

    PC->tempHP = 5;
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

//TODO: Check if this is safe to do
bool writePC(struct fighter newPC){
    *PC = newPC;
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
    return true;
}


/* On the backend, we always use Read and Write PC from within our spinlock, so everything below is wrapper functions */
void setHP(int hp){
    taskENTER_CRITICAL(&pcDataSpinlock);
    if(hp >= PC->maxHP){PC->HP = PC->maxHP;}else if(hp <= 0){PC->HP = 0;}else{PC->HP = hp;}
    taskEXIT_CRITICAL(&pcDataSpinlock);
}

//TODO: setTempHP, etc...

void adjustHP(int up){
    setHP(PC->HP + up);
}