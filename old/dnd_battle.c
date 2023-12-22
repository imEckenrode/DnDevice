#include "dnd_battle.h"
#include "dndv_data.h"

// Shared Code:
struct game game;

// Player Code:

void refreshInitUI(){
    printf("TODO: Refresh Combatant List Display Here");
}

void updateCombatantList(Combatant list[MAX_COMBATANT_COUNT]){
    memcpy(game.combatantList, list, sizeof(Combatant * MAX_COMBATANT_COUNT));
    refreshInitUI();
}

//TODO: Also check if game.combatantList[newIndex] has the same key as received by this method (as checksum)
void updateCombatantIndex(Num newIndex){
    game.combatantIndex = newIndex;
    refreshInitUI();
}



void pc_dnd_init(){

}


// GM Code:

void sendPlayerList();


void gm_dnd_init(){
    //{0} initializes the entire combatantList to 0s (otherwise could use memset)
    struct game game = {{0},malloc(sizeof(EnemyData)*25),0};
    //game.gmPlayerList

    //TODO: pass the list of players when outside battle (probably)
}  





