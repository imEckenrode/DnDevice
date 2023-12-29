#pragma once

#include <stdbool.h>
#include <stdint.h>

/*

This contains all game variables and manipulations of said variables

This is for the Player device, so it contains HP

For device-level data, see device_data.
All Player data is device-level since it does not need shared from this device. The Key is used as an ID, and thus is included here

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
};

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

#define DATA_SIZE_PC 12

//For additions: deathsaves and deathfails can be brought down to 2 each, while AC can be brought down to 6
volatile struct __attribute__((__packed__)) {
    union{  //2 bytes
        struct conditions condition;
        uint16_t allConditions; //This is simply 16 bits to set all conditions to 0
    };

    short HP;           //2 bytes
    short maxHP;        //2 bytes   //This could be reduced by an effect
    short trueMaxHP;    //2 bytes
    short tempHP;       //2 bytes
                    //All below is 2 bytes
    uint8_t AC;
    uint8_t deathsaves:4;  
    uint8_t deathfails:4;


    
    //Above is exactly 12 bytes (as seen in DATA_SIZE_PC)

    char name[];
} *PC;

void default_pc_init();


//Manipulations of the struct, in order:

//Conditions

//HP
void adjustHP(int up);