#include <stdio.h>

int five;
//Integer from here is not defined until test.c

void call(void){
    printf("%d",five);
}