#include <stdio.h>
#include <stdbool.h>
#include <string.h>


char SETUP_OPTIONS[2][30]={"New Character","Done Entering Characters"};
#define TURN_OPTIONS_COUNT 5
char TURN_OPTIONS[TURN_OPTIONS_COUNT][30]={"End Combat","End Turn","Attack Roll","Saving Throw","Print Initiative List"};  //Hold Turn, Heal
                    typedef enum turnStatus{endCombat, endTurn, attackRoll, savingThrow,seeInitiativeList,passTurn=5} turnStatus;

typedef struct fighter{
    short key;
    char name[16];
    short HP;
    short AC;
    short atkMod;
    short initiative;
    //short mac;
}
Fighter;

//NOTE: I had to run "Select IntelliSense Configuration..." and select gcc.exe, so may need to change back

struct __attribute__((__packed__)) gm_combatant_data{
    short HP;
    short AC;
    short atkMod;
    bool hasLegendaryActions;
};

typedef struct __attribute__((__packed__)) combatant{
    short key; //Also used to look up if player or enemy in the final product
    short initiative;
    bool isPlayer;     //Temporary, for readability
    bool halfHealth;           //False if full health, otherwise should not be on the board? Could change to two different booleans
    bool active;           //Does this combatant show up at all        //Should this combatant exist on the players' side if not active?
    bool obfuscated;       //Display the name of the combatant?

    struct gm_combatant_data gm;        //This should make it easier to pull the gm-specific data in the final product
    char name[16];  //Could make dynamic struct for dynamic name lengths

} Combatant;

//Both sides will have the friendsList (TODO: Rename to pList?)
#define fMAX_SIZE 10
Fighter fList[fMAX_SIZE];
short fSize;

//Only the GM will have the enemyDB
Fighter eList[fMAX_SIZE];
short eSize;

#define MAX_COMBATANT_COUNT 24
Combatant combatants[MAX_COMBATANT_COUNT];
short combatantCount = 0;

//Active initiative position (for the combatants array)
short activePos = 0;
short getActivePos(){
    return activePos;
}

//This is currently also used for assistant functions, so turn start functions should not be called here
short incrementActivePos(){
    if(activePos<combatantCount-1){
        activePos++;
    }else{
        activePos = 0;
    }
    printf("%d out of %d,\n",activePos,combatantCount);
    return activePos;
}

void setActivePos(short activPos){
    if(activPos<combatantCount){
        activePos = activPos;
    }
}

Combatant fighter2combatant(Fighter fighter, bool isPlayer, bool active){
    struct gm_combatant_data new = {fighter.HP, fighter.AC, fighter.atkMod, false};
    Combatant newCombatant = {fighter.key, fighter.initiative, isPlayer, false, active, false, new};
    strcpy(newCombatant.name, fighter.name);
    return newCombatant;
}

int optionSelect(char options[][30],short count){    //This should give me access -(pointer)- to an array of character arrays (strings)  
    printf("\n");
    for (int i=0;i<count;++i){
        printf("%d) %s\n",i,options[i]);
    }
    printf("Type a number: ");
    short selection;
    scanf("%d",&selection);
    printf("\n");
    
    //We need to clear the newline character, then we should be good to go
    getchar();
    return selection;
}

int numberPrompt(char text[]){
    printf("%s",text);
    int selection;
    scanf("%d",&selection);
    printf("\n");
        getchar();
    return selection;
}

Combatant* chooseTarget(){
    printf("Choose target:\n");
    for (int i=0;i<combatantCount;i++){
        printf("%d) %s\n",i,combatants[i].name);
    }
    printf("> ");
    int selection;
    scanf("%d",&selection);
    printf("\n");
    getchar();
    Combatant *chosen = &combatants[selection];

    printf("DEBUG: Targeting %s. AC: %d, Atk: %d\n", chosen->name, chosen->gm.AC, chosen->gm.atkMod);
    return chosen;
}

#include <stdlib.h>
#define RAND_MAX 20
int rollD20(){
    return rand() + 1;
}

void predefined(){          
            //Fighter is:  short key  char name[16]  short HP  short AC  short atkMod  int initiative;
    Fighter tempBuf = {1,"Char1",3,20,-1,7};   //Can only initialize struct this way at declaration time, so I just declare new ones and copy the struct
    fList[0]=tempBuf;
    Fighter tempBuf1 = {2,"Char2",165,13,4,13};
    fList[1]=tempBuf1;
    Fighter tempBuf2 = {3,"Char3",1,15,5,21};
    fList[2]=tempBuf2;
    fSize=3;
}

void enemies(){
    Fighter tempBuf = {64,"Gob1",30,10,2,12};   //Can only initialize struct this way at declaration time, so I just declare new ones and copy the struct
    eList[0]=tempBuf;
    Fighter tempBuf1 = {65, "Gob2",30,10,2,12};      //TODO: duplicate the monster instead of creating a new one
    eList[1]=tempBuf1;
    Fighter tempBuf2 = {66, "Boss",200,14,7,14};
    eList[2]=tempBuf2;
    eSize=3;
}

void setup(){
    printf("Party Creation:");
    char options[3][30]={"New Character","Done Entering Characters","Use Predefined Party"};
    bool next = false;
    fSize = 0;
    while(!next){
        switch(optionSelect(options,3)){
            case 0:
                if(fSize<fMAX_SIZE){
                    Fighter new; //{"CharName",0,0,NULL};
                    printf("Character Name: ");
                    scanf("%s",new.name);
                    printf("Character HP: ");
                    scanf("%d",&new.HP);

                        getchar();

                    printf("Character AC: ");
                    scanf("%d",&new.AC);

                        getchar();

                    printf("Character Attack Modifier: ");
                    scanf("%d",&new.atkMod);
                        getchar();

                    printf("Initiative Rolled: ");
                    scanf("%d",&new.initiative);
                        getchar();

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
                printf("Party Created.");
                next = true;
                break;
            case 2:
                predefined();
                printf("Predefined Characters Loaded.");
                next = true;
                break;
            default:
                printf("Bad input, please try again...\n");
    }}
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
            if(list[j].initiative>fTopInit.initiative){
                fTopInit = list[j];
                bigPos = j;
        }}
        list[bigPos] = list[i]; //Move the current one to the position occupied by the highest initiative
        list[i] = fTopInit;     //Move the highest initiative to the top
    }
}   //Could do with Cycle Sort to cut memory writes in half, but it all stays in the same memory, so it'll be fine



void initializeCombatantArray(Fighter fList[], int fSize, Fighter eList[], int eSize){
    int fPos = 0;
    int ePos = 0;
    combatantCount = fSize + eSize;
    for(int i = 0; i<combatantCount; i++){
        //Check whether to pick from the enemy list...
        if(fPos == fSize || fList[fPos].initiative < eList[ePos].initiative){ //Players go before enemies if tied
            combatants[i] = fighter2combatant(eList[ePos++], false, true);
        }else{      //...or the player list
            combatants[i] = fighter2combatant(fList[fPos++], true, true);
        }
    }
}

void addToCombatantArray(Combatant a){
    int pos = 0;
    if(a.isPlayer){     //This case is probably not needed
        for(int i = 0; i<combatantCount; i++){
            if(combatants[i].initiative<=a.initiative){
                pos = i;
                break;
            }
        }
    }else{      //Place new monsters after the combatants if they match
        for(int i = 0; i<combatantCount; i++){
            if(combatants[i].initiative<a.initiative){
                pos = i;
                break;
            }
        }
    }

    combatantCount++;
    //Now shift down all combatants and assign the new one to its position
    for(int j = combatantCount-1; j>=pos; j--){
        combatants[j+1] = combatants[j];
    }
    combatants[pos] = a;

    //TODO: Finally, if this combatant is added before the active player, be sure to move up the current combatant variable by one
    if(pos<=getActivePos()){
        incrementActivePos;
    }
}



//-------------------------------------------------------------------------ERROR: (TODO) Need to pass in pointer to target and not a copy (or return the combatant)
void adjustHP(Combatant *target, int hp){
    target->gm.HP += hp;             
    //TODO: add "drop to 0" logic
}


void makeAtk(Combatant attacker){
    Combatant *target = chooseTarget();
    if(attacker.isPlayer){
        int roll = numberPrompt("Enter attack roll: ");
        if(roll<target->gm.AC){
            printf("Attack Missed\n");
            return;
        }
    }else{
        if(rollD20()+attacker.gm.atkMod < target->gm.AC){    // Do this on the GM side, of course
            printf("Enemy Attack Missed\n");
            return;
        }
    }
    int dmg = numberPrompt("Hit! Enter Damage: ");
    adjustHP(target, -dmg);
}

void makeSaveAtk(Combatant attacker, bool halfOnSave){ //, bool dex){
    printf("DEBUG: Need to beat a %d. \n",attacker.gm.atkMod+8);
    Combatant *target = chooseTarget();
    int dmg = numberPrompt("Enter Damage: ");

    if(target->isPlayer){
        int roll = numberPrompt("Enter saving throw roll: "); //TODO: Types of Saving Throws
        if(roll> (attacker.gm.atkMod+8)){
            printf("%s Saved\n", target->name);
            if(halfOnSave){                     //TODO: evasion negating all damage
                dmg /= 2;
            }
            return;
        }else{
            printf("%s Failed\n", target->name);
        }
    }else{
        if(rollD20() > (attacker.gm.atkMod + 8)){    //TODO: apply saving throw modifier
            printf("%s Saved\n", target->name);
            if(halfOnSave){                     //TODO: evasion negating all damage
                dmg /= 2;
            }
            return;
        }else{
            printf("%s Failed\n", target->name);
        }
    }
    adjustHP(target, -dmg);
    printf("%s took %d damage!\n",target->name, dmg);
}

void printCombatantList(){
    printf("\n------Combatant List------\n");
    for (int i=0;i<combatantCount;i++){
        printf("%s:\t\tHP: %d\tInitiative:%d\n",combatants[i].name,combatants[i].gm.HP,combatants[i].initiative);
    }
    printf("\n");
}

short turn(Combatant* f){     //Change this to a pointer (not really needed tbh).      //Instead of passing a fighter, we'd have a Combatant (the active fighter per device)
    printf("%s, what would you like to do?",f->name);
    while(true){
        switch (optionSelect(TURN_OPTIONS,TURN_OPTIONS_COUNT)){
            case endTurn:
                return endTurn;
            case endCombat:
                return endCombat;
            case attackRoll:
                makeAtk(*f);
                break;
            case savingThrow:
                makeSaveAtk(*f, true);
                break;
            case seeInitiativeList:
                printCombatantList();
            default:
                printf("Invalid option/not implemented yet.\n");
        }
        printf("%s, what else would you like to do?",f->name);
    }
}


void battle(){  //A function that runs the battle simulation until "end combat"
    initiative();
    //short currentTurn = 0;
    //int currentRound = 1;
    short result=0;

    orderArray(fList,fSize);
    orderArray(eList,eSize);

    // Combine the enemies and friends' initiatives now. Feel free to rewrite to sort in same space
    initializeCombatantArray(fList,fSize, eList,eSize);

    printf("First 3 in Initiative: \n");
    printf("%s\n",combatants[0].name);
    printf("%s\n",combatants[1].name);
    printf("%s\n",combatants[2].name);

    //printf("Top of %d fighters is %s",fSize,fList[0]);
    printf("\n----- Battle Begin! -----\n");
    while(true){
        //for(currentTurn=0;currentTurn<combatantCount;currentTurn++){

        result=turn(&combatants[activePos]);         //Simple "turn" function to encapsulate everything
        if(result==endCombat){
            return;
        }
        incrementActivePos();

        //}
        //currentRound++;
    }
};

int main(){
    printf("\n Code Start! \n");
    //setup();
    predefined();
    enemies();
    

    battle();
    printf("\n Output Done \n");
    return 0;
}