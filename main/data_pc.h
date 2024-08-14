#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "device.h"

/*

This contains all game variables and manipulations of said variables

This is for the Player device, so it contains HP

For device-level data, see device_data.
All Player data is device-level since it does not need shared from this device. The Key is used as an ID, and thus is included here

The helper functions all use a dedicated spinlock to guarantee no interference across cores/threads

*/


struct __attribute__((packed)) conditions{  //Since these are all the same type, they won't jump another block
    bool blinded:1;
    bool charmed:1;
    bool deafened:1;
    bool disarmed:1;
    bool exhaustion:1;
    bool frightened:1;
    bool grappled:1;
    bool hidden:1;
    bool incapacitated:1;
    bool invisible:1;
    bool obscured:1;
    bool paralyzed:1;
    bool petrified:1;
    bool poisoned:1;
    bool prone:1;
    bool raging:1;
    bool restrained:1;
    bool surprised:1;
    bool stunned:1;
    bool unconscious:1;
}; //rage, disarmed, that too...but 18 total so it'll be there!

/*struct stats {  //This is not used by this iteration
    unsigned st:5;
    unsigned de:5;
    unsigned co:5;
    unsigned wi:5;
    unsigned in:5;
    unsigned ch:5;
    unsigned altered:1; //If a stat is altered by an attack, we should track it
    unsigned dead:1;    //filled space here
};*/

//THiS is the structure for all PCs and enemies

#define DATA_FIGHTER_NAME_LEN 32
struct __attribute__((packed)) fighter{
    short HP;           //2 bytes
    short maxHP;        //2 bytes   //This could be reduced by an effect, hence the trueMaxHP
    short trueMaxHP;    //2 bytes
    short tempHP;       //2 bytes
                    //All below is 2 bytes
    uint8_t AC; //This is up from 6
    uint8_t itemAC:4;            //This is currently unused
    uint8_t statusAC:4; //Cover, shield, etc.  TODO: this would be easiest to separate into cover and not
    uint8_t deathsaves:2;  
    uint8_t deathfails:2;

    uint8_t exhaustionLevel:3;   //This keeps exhaustion level separate from the toggleable and keeps the conditions struct uniform
    union{  //bytes
        struct conditions condition;
        uint32_t allConditions:DNDV_CONDITIONS_COUNT;
    };

    uint8_t pfp; //This is a shortened "enum DNDV_PFPS" attribute
    char nickname[DATA_FIGHTER_NAME_LEN]; //Full name is a device-level attribute, but for now we allow for the full name here. This also means that PC is fixed size
} *PC;

void default_pc_init();


// This returns a copy of PC
struct fighter readPC();

// This updates the PC data to whatever is passed in. Make sure it isn't a bunch of zeros
bool writePC(struct fighter newPC);

//Long Rest and Short Rest functionality
void longRest();
void shortRest(int hp);

// Below are the wrappers for manipulating the struct, in order (with data correction)):

//Conditions

//HP
void setHP(int hp);
void setTempHP(int hp);
void setMaxHP(int hp);
void setTrueMaxHP(int hp);
void adjustHP(int up);

//AC
void setAC(int ac);
void setCover(int ac);

//Conditions
bool hasCondition(uint8_t address);
void setCondition(uint8_t address, bool set);
void toggleCondition(uint8_t address);
void setExhaustionLevel(uint8_t level);
void clearConditions();

//Profile Picture
void setPFP(short newPFP);
//Name
void setName(char* newName);