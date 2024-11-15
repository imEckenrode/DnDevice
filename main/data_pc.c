#include "data_pc.h"

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
    PC->allConditions = 0;      //Do this to start all conditions at False (since we're overwriting all else, we could malloc instead of calloc)

    PC->tempHP = 5;
    PC->AC = 12;
    PC->statusAC = 0;
    PC->HP = 20;
    PC->trueMaxHP = 30;
    PC->maxHP = PC->trueMaxHP;
    PC->pfp = DNDV_PFP_WARLOCK;

    strcpy(PC->nickname, "Blanky McNothing");

    ESP_LOGW("OUTPUT", "HP: %d, MAX: %d, AC: %d, Conditions: %x", PC->HP, PC->maxHP, PC->AC, PC->allConditions);
    ESP_LOGW("SIZE", "%d", sizeof(*PC));

    //free(PC); if we ever become the DM
}

 
struct fighter readPC(){
    return *PC;
}

//TODO: Check if this is atomic to do
bool writePC(struct fighter newPC){
    *PC = newPC;
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
    return true;
}

//Long Rest and Short Rest functionality
void longRest(){
    setHP(1000000); //Anything higher than maxHP will set to maxHP haha
}

//You can't lose HP while completing a short rest
void shortRest(int hp){
    if(hp>0){adjustHP(hp);}
}

/* On the backend, we always use Read and Write PC from within our spinlock, so everything below is wrapper functions */
//TODO: May need a special method for reaching 0 HP
void setHP(int hp){
    taskENTER_CRITICAL(&pcDataSpinlock);
    if(hp >= PC->maxHP){PC->HP = PC->maxHP;}else if(hp <= 0){PC->HP = 0;}else{PC->HP = hp;}
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}

void setTempHP(int hp){
    taskENTER_CRITICAL(&pcDataSpinlock);
    if(hp <= 0){PC->tempHP = 0;}else{PC->tempHP = hp;}
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}

    //TODO: If this causes problems, move the If conditions outside the lock and set temporary variables. Currently we save space over time.
void setMaxHP(int hp){
    taskENTER_CRITICAL(&pcDataSpinlock);
    if(hp >= PC->trueMaxHP){PC->maxHP = PC->trueMaxHP;}else if(hp <= 0){PC->maxHP=0;}else{PC->maxHP=hp;}
    if(PC->maxHP < PC->HP){PC->HP = PC->maxHP;} //Reduce HP to maxHP if applicable
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}

void setTrueMaxHP(int hp){
    taskENTER_CRITICAL(&pcDataSpinlock);
    if(hp <= 0){PC->trueMaxHP = 0;}else{PC->trueMaxHP = hp;}
    PC->maxHP = PC->trueMaxHP;  //Reset maxHP to align with trueMaxHP (TODO: Take the difference)
    if(PC->maxHP < PC->HP){PC->HP = PC->maxHP;} //Reduce HP to maxHP if applicable
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}


void setAC(int ac){
    taskENTER_CRITICAL(&pcDataSpinlock);
    if(ac <= 0){PC->AC = 0;}else{PC->AC = ac;}
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}

void setCover(int ac){
    taskENTER_CRITICAL(&pcDataSpinlock);
    if(ac <= 0){PC->statusAC = 0;}else{PC->statusAC = ac;}
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}


bool hasCondition(uint8_t address){
    return ((PC->allConditions & (1 << address%DNDV_CONDITIONS_COUNT)) != 0);
}

void setCondition(uint8_t address, bool set){
    if(address == DNDV_COND_EXHAUSTION){
        setExhaustionLevel(1&set);  //Send a 1 if we're setting it on and 0 if we're setting it off
    }else{
        if(set){
            taskENTER_CRITICAL(&pcDataSpinlock);
            PC->allConditions |= (1 << (address%DNDV_CONDITIONS_COUNT));
            taskEXIT_CRITICAL(&pcDataSpinlock);
        }else{
            taskENTER_CRITICAL(&pcDataSpinlock);
            PC->allConditions &= ~(1 << (address%DNDV_CONDITIONS_COUNT));
            taskEXIT_CRITICAL(&pcDataSpinlock); 
        }
        esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);//TODO: Make a new base specific to conditions?
    }
}

void toggleCondition(uint8_t address){
    // If we're toggling the Exhaustion condition, increment the level by 1 instead of a simple on and off
    if(address == DNDV_COND_EXHAUSTION){
        setExhaustionLevel(PC->exhaustionLevel+1);
    }else{
        bool newBool = !hasCondition(address); //The compiler should bring in the one line of code here, so this is the most readable
        setCondition(address, newBool);
    }
}

uint8_t getExhaustionLevel(){
    return PC->exhaustionLevel;
}

void setExhaustionLevel(uint8_t level){
    taskENTER_CRITICAL(&pcDataSpinlock);
    PC->exhaustionLevel = level%7;  //Exhaustion can only be a value between 0 and 6
    if(PC->exhaustionLevel!=0){
        PC->condition.exhaustion = 1;
    }else{
        PC->condition.exhaustion = 0;
    }
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}

void clearConditions(){
    taskENTER_CRITICAL(&pcDataSpinlock);
    PC->allConditions = 0;
    PC->exhaustionLevel = 0;
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}


void setPFP(short newPFP){
    uint8_t actual = (newPFP % DNDV_PFPS_COUNT + DNDV_PFPS_COUNT) % DNDV_PFPS_COUNT; //This guarantees a positive modulus
    taskENTER_CRITICAL(&pcDataSpinlock);
    PC->pfp = actual;
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}

void setName(char* newName){
    taskENTER_CRITICAL(&pcDataSpinlock);
    strncpy(PC->nickname, newName, DATA_FIGHTER_NAME_LEN - 1);
    PC->nickname[DATA_FIGHTER_NAME_LEN-1] = '\0';  //Fighter is filled up with null terminals now, but make sure the last one is a null terminal
    taskEXIT_CRITICAL(&pcDataSpinlock);
    esp_event_post_to(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, NULL, 0,0);
}


void adjustHP(int up){
    setHP(PC->HP + up);
}