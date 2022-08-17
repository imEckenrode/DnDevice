#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "b.h"

int five = 5;

int f1(){
    return 1;
}

int f2(){
    return 100;
}

static int (*ptr[])(void) = {       //Yay it works
    f1,     //The first function is at 0
    f2      //The second function is at 1, etc
};

//void printTheNum(int);

void printTheNum(int num){
    printf("%d",(ptr[num])());
}



struct inside{
    short in;
    short side;
    int* again;
    unsigned char* hello;
};

struct outside{
    int out;
    struct inside inner;
};

typedef char* bytes;

void structTesting(void){
    int wellwell = 5;
    int* ptr = &wellwell;
    char* intro = "Hello, World!";
    struct inside hi = {1,1,ptr, intro};
    struct outside theStruct = {3,hi};

    printf("%d\n%d\n%d\n%s.\n%d\n%d\n.\n",theStruct.inner.in,theStruct.out, *theStruct.inner.again, theStruct.inner.hello,  theStruct.inner, theStruct);
}

#include <stdlib.h>
void byteTesting(void){
    bytes a = (bytes) malloc(10);
    printf("%s\n",a);       //Lots of junk data
    char* b = "Heya";
    memcpy(&a[1],(void*)b,strlen(b)+1);
    printf("%s\n",a);       //Now there's one junk data before and then actual data
    free(a);
}



struct end{
            short tenThousand;
            short one;
        };

struct power{
    struct{
        int a;
        int b;
    } start;
    union hello{
        struct end bye;
        int fullPower;
    } pie;
};


void powerTrip(void){
    struct power ultimate = {1,2,0,1};
    printf("%d %d %d %d %d\n",ultimate.start.a, ultimate.pie.bye, ultimate.pie.bye.one, ultimate.start, ultimate.pie);

    printf("%d\n", ultimate.pie.fullPower);
}



int main(){
    //structTesting();
    //byteTesting();
    //call();

    powerTrip();
/*
    printTheNum(0);
    printf("\n")
    printTheNum(1);
*/

}