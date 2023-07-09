#include "dnd_battle.h"
#include "dndv_data.h"

// Shared Code:
struct game game;

// Player Code:

void pc_dnd_init(){

}

void updateCombatantList(Combatant list[MAX_COMBATANT_COUNT]){
    memcpy(game.combatantList, list, sizeof(Combatant * MAX_COMBATANT_COUNT));
}

//TODO: Also check if game.combatantList[newIndex] has the same key as received by this method (as checksum)
void updateCombatantIndex(Num newIndex){
    game.combatantIndex = newIndex;
}
// GM Code:

void gm_dnd_init(){
    struct game game;
    game.gmEnemyList = malloc(sizeof(EnemyData)*25);
    //game.gmPlayerList

    //TODO: pass the list of players when outside battle (probably)
}  





