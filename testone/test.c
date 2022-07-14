#include <stdio.h>
#include <stdbool.h>


char SETUP_OPTIONS[2][30]={"New Character","Done Entering Characters"};
short const TURN_OPTIONS_COUNT = 4;
char TURN_OPTIONS[TURN_OPTIONS_COUNT][30]={"End Turn","End Combat","Attack","AoE"};  //Hold Turn, Heal
                    typedef enum turnStatus{endTurn,endCombat,ERROR,passTurn=4} turnStatus;

typedef struct{
    char name[30];
    short HP;
    short Initiative;
    //struct Fighter *nextFighter;
}
Fighter;



short const fMAX_SIZE = 10;
Fighter fList[10];
short fSize;

int optionSelect(char options[][30],short count){    //This should give me access -(pointer)- to an array of character arrays (strings)  
    printf("\n");
    for (int i=0;i<count;++i){
        printf("%d) %s\n",i,options[i]);
    }
    printf("Type a number: ");
    short selection;
    scanf("%d",&selection);
    printf("\n");
    return selection;
}

void setup(){
    char options[2][30]={"New Character","Done Entering Characters"};
    bool next = false;
    fSize = 0;
    while(!next){
        switch(optionSelect(options,2)){
            case 0:
                if(fSize<fMAX_SIZE){
                    Fighter new; //{"CharName",0,0,NULL};
                    printf("Character Name: ");
                    scanf("%s",new.name);
                    printf("Character HP: ");
                    scanf("%d",&new.HP);

                    printf("Initiative Rolled: ");
                    scanf("%d",&new.Initiative);

                    printf("'%s' is ready to go with %d HP",new.name,new.HP);
                    fList[fSize++]=new;
                }else{
                    printf("Max Characters Reached.\n");
                }
                printf("\nCurrent List of Fighters:\n");
                for(int i=0;i<fSize;++i){
                    printf("%s\n",fList[i].name);
                }
                break;
            case 1:
                printf("Now it's time to battle.");
                next = true;
                break;
            default:
                printf("Bad input, please try again...\n");
    }}
}

void predefined(){
    Fighter tempBuf = {"Char1",3,7};    //Can only initialize struct this way at declaration time, so I just declare new ones and copy the struct
    fList[0]=tempBuf;
    Fighter tempBuf1 = {"Char2",165,13};
    fList[1]=tempBuf1;
    Fighter tempBuf2 = {"Char3",1,17};
    fList[2]=tempBuf2;
    fSize=3;
}

void initiative(){
    printf("Will Implement Rerolling Here, Rolled In Character Creation For Now\n");
}

void orderArray(Fighter list[], short size){
    //Currently implemented with a Selection Sort (described below)
    //Loop through list, find highest initiative, move the current start to that position, and move the highest value to the start
        //Repeat this through the whole list until the whole list is sorted
    for(short i=0;i<size;i++){
        Fighter fTopInit = list[i];
        short bigPos = i;
        for(short j=i+1;j<size;j++){
            if(list[j].Initiative>fTopInit.Initiative){
                fTopInit = list[j];
                bigPos = j;
        }}
        list[bigPos] = list[i]; //Move the current one to the position occupied by the highest initiative
        list[i] = fTopInit;     //Move the highest initiative to the top
    }
}   //Could do with Cycle Sort to cut memory writes in half, but it all stays in the same memory, so it'll be fine


void makeAtk(Fighter attacker){
    printf("This is next.");
}

short turn(Fighter f){     //Change this to a pointer.      //Instead of passing a fighter, we'd have an Active Fighter (which would be the fighter per device)
    printf("%s, what would you like to do?",f.name);
    while(true){
        switch (optionSelect(TURN_OPTIONS,TURN_OPTIONS_COUNT)){
            case endTurn:
                return endTurn;
            case endCombat:
                return endCombat;
            case 2:                     //It'd be real nice to define the enum and char arrays to the same values
                makeAtk(f);
            case 3:
                aoe(f);
            default:
                printf("Invalid option/not implemented yet.\n");
        }
        printf("%s, what else would you like to do?",f.name);
    }
}

void battle(){  //A function that runs the battle simulation until 
    initiative();
    short currentTurn = 0;
    int currentRound = 1;

    orderArray(fList,fSize);          //Eventually only use pointers, but passing everything is fine for demo
    
    printf("Top of %d fighters is %s",fSize,fList[0]);
    printf("\n----- Battle Begin! -----");
    while(true){
        for(currentTurn=0;currentTurn<fSize;currentTurn++){
            turn(fList[currentTurn]);         //Simple "turn" function for now, will need more complex in the future
        }
        
    }
};

int main(){
    printf("\n Code Start! \n");
    //setup();
    predefined();

    battle();
    printf("\n Output Done \n");
    return 0;
}

