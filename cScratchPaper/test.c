#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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
    //printf("%d\n%d\n%d\n%s.\n%d\n%d\n.\n",theStruct.inner.in,theStruct.out, *theStruct.inner.again, theStruct.inner.hello,  theStruct.inner, theStruct);
}

struct __attribute__((__packed__)) readAll{
    char and;
    char now[];
};

struct __attribute__((__packed__)) readCopy{
    struct readAll book;
};

struct __attribute__((__packed__)) readMore{
    char one;
    char two;
    char now[];
};


void structTesting2(void){   
    printf("\nNow start\n");
    char* reading_p = malloc(6);
    if (reading_p==NULL){
        printf("\nAllocation failed!\n");
        return;
    }

    char a = 'a';
    *reading_p = a;
    //memcpy(reading_p,&a,1);
    strcpy(reading_p+1,"abcd");

    printf("%d, %d, %s", *((short*)reading_p), ((struct readAll*)reading_p)->and, ((struct readAll*)reading_p)->now);
    //The first one is 97*256+97, which means the array data is right next to the first character. Success!

    /*struct readCopy readingTime = {*((struct readAll*) reading_p)};
    printf("\n%d != %d", &readingTime.book.now, &((struct readAll*)reading_p)->now);    //The memory addresses are not the same (where is it going to?) */

    struct readCopy* readingTime = malloc(6);
    readingTime->book.and = ((struct readAll*)reading_p)->and;
    strcpy(readingTime->book.now, ((struct readAll*)reading_p)->now);

    printf("\n%d, %d, %s", *((short*) readingTime), readingTime->book.and, readingTime->book.now);
        //As expected, would need to memcpy the h

    printf("\n%d, %d, %s", *((short*)reading_p), ((struct readMore*)reading_p)->one, ((struct readMore*)reading_p)->now);   //Can use a different pointer to get different data

    printf("\nNow free\n");
    free(reading_p);
    free(readingTime);
}


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
    structTesting2();
    //byteTesting();
    //call();

   // powerTrip();
/*
    printTheNum(0);
    printf("\n")
    printTheNum(1);
*/

}