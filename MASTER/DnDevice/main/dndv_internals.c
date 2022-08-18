#include "dndv_internals.h"

//Initialize all global variables to the correct values
void internals_init(){
    current.isDM = false;
        
    //current.player = &currentPlayer;       //TODO: Pass all through current instead of three variables
    //current.character = &currentPC;
}


/*      - DM EXCLUSIVE FUNCTIONS -
    Here are the functions exclusive to the DM

    To keep this exclusivity, DM_Activate activates the handle for DM only events

*/
//The handler for any DM exclusive data
void dm_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        /*case EVENT_AWAKE_BROADCAST_RCV:       //This code has been moved to the sync_rcv in dndv_comms.c
            printf("A device just woke up.\n");
            break;  */
        default:
            printf("Heard some stuff out there...as a DM\n");
    }
}



//  Initialize all the DM functions, handles, and variables.
//      currentPlayer = DM Name
//      currentPC = Campaign Name Stuff (TODO: Find uses for HP numbers or remove this functionality)
void DM_Activate(void){
    //int size = 22;
    //arr to_send = {22, malloc()
    uint8_t to_send[2+MAX_NAME_LENGTH] = {N_SYNC_BASE,EVENT_DM_INFO};
    memcpy(&to_send[2], currentPC.name,20);  //I can simply use 20 becasue the data is uint8
    esp_event_handler_instance_register_with(dndv_event_h, DM_RCV_BASE, ESP_EVENT_ANY_ID, dm_rcv, NULL,NULL);
    esp_event_handler_instance_register_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, dm_rcv, NULL,NULL);
    //Player List
    //PlayerToMAC List
    //NPC List  (Same layout as players, plus attack bonus?)

    esp_event_post_to(dndv_event_h, DEVICE_BASE, EVENT_DM_ACTIVATE, (void*)currentPC.name, sizeof(currentPC.name), 0);
    esp_event_post_to(dndv_event_h, OUTGOING_BASE, EVENT_SEND_BROADCAST, (void*)to_send, sizeof(to_send), 0);  //No need to divide size of a uint8 array, because sizeof(uint8) = 1
}



//And finally, tests

void testPCInit(void){
    Player examplePlayer = {1,"Bob",0,false};
    currentPlayer=examplePlayer;
    PC examplePC = {1,"PowerWizard",5,3};
    currentPC=examplePC;

    current.isDM = false;
    strcpy(current.p_name,currentPlayer.name);
    strcpy(current.c_name,currentPC.name);
    printf("Test Player Initialized\n");
}

void testDMInit(void){
    current.isDM = true;      //TODO: Could have a semaphore something or other on the global level
    strcpy(currentPC.name, "MeDM");
    strcpy(currentPC.name, "AwesomeCampaignTitle");
    DM_Activate();
    printf("DM Mode Activated (Test DM Initialized)\n");
}