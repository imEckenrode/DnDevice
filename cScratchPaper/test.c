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

int main(){
    
    call();
/*
    printTheNum(0);
    printf("\n")
    printTheNum(1);
*/
}