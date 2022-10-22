#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct end{
    int startmore;
    char and[];
};

struct start{
    short start;
    char and[];
};

struct end* convert(struct start* a){
    struct end* p = malloc(sizeof(a)+2);
    p->startmore = a->start;
    strcpy(p->and,  a->and);
    printf("%c", p->and);
    return p;
}

int main(){
    struct start *og = malloc(24);
   // *og = (const struct start){4};
    og->start = 4;
    char h[] = "Hello, World!";
    strcpy(og->and,h);
    struct end *better = convert(og);
    //printf("%c", better->and);
    printf("\n%d, %d\n", sizeof(*better), sizeof(*og));
    puts(og->and);
    printf("\n");
    puts(better->and);      //is this correct? or am i bypassing a pointer
}