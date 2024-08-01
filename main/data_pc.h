#pragma once

#include <stdbool.h>
#include <stdint.h>

/*

This contains all game variables and manipulations of said variables

This is for the Player device, so it contains HP

For device-level data, see device_data.
All Player data is device-level since it does not need shared from this device. The Key is used as an ID, and thus is included here

The helper functions all use a dedicated spinlock to guarantee no interference across cores/threads

*/


struct conditions{  //Since these are all the same type, they won't jump another block
    bool blinded:1;
    bool charmed:1;
    bool therest:1;
    bool d:1;
    bool e:1;
    bool f:1;
    bool g:1;
    bool h:1;
    bool i:1;
    bool j:1;
    bool k:1;
    bool l:1;
    bool m:1;
    bool n:1;
    bool o:1;
    bool p:1;
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
    union{  //2 bytes
        struct conditions condition;
        uint16_t allConditions; //This is simply 16 bits to set all conditions to 0
    };

    short HP;           //2 bytes
    short maxHP;        //2 bytes   //This could be reduced by an effect, hence the trueMaxHP
    short trueMaxHP;    //2 bytes
    short tempHP;       //2 bytes
                    //All below is 2 bytes
    uint8_t AC:6;
    uint8_t itemAC:3;            //This is currently unused
    uint8_t statusAC:3; //Cover, shield, etc. (all together will put over this limit...)
    uint8_t deathsaves:2;  
    uint8_t deathfails:2;

    char nickname[DATA_FIGHTER_NAME_LEN]; //Full name is a device-level attribute, but for now we allow for the full name here. This also means that PC is fixed size
} *PC;
//TODO: Lock this behind a mutex

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


//Name
void setName(char* newName);