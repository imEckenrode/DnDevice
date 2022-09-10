#include "dndv_internals.h"

void device_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data);

//Initialize all global variables to the correct values
void internals_init(){
    current.isDM = false;
    localDevice.displayLogs = false;   //Change this to set if dndv_log logs
    //current.player = &currentPlayer;       //TODO: Pass all through current instead of three variables
    //current.character = &currentPC;

    esp_event_handler_instance_register_with(dndv_event_h, DEVICE_BASE, ESP_EVENT_ANY_ID, device_rcv, NULL,NULL);
}


/*  HOME OF DEVICE_BASE HANDLING
This function receives all DEVICE_BASEd events and processes them accordingly, possibly redirecting them to other functions.
*/
void device_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        case EVENT_DM_KEYIN:
            testDMInit();       //Temporary (TODO)
            break;

        case EVENT_CAMPAIGN_SELECT:
            break;
        default:
            ESP_LOGE("DnDevice Internal", "Did not recognize the internal event.");
    }

}


/*      - DM EXCLUSIVE FUNCTIONS -
    Here are the functions exclusive to the DM.

    To keep this exclusivity, DM_Activate activates the handle for DM only events

*/

//The handler for any DM exclusive data (DM_DEVICE_BASE)
void DM_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        case EVENT_DM_ACTIVATE:
            struct dm_activate_s to_send = {N_SYNC_BASE,EVENT_DM_INFO,currentPlayer.name,currentPC.name}; //TODO: Can I just put everything in here and not strcpy???
            //strcpy(to_send.dmName, currentPlayer.name);    //Copy in the DM's name
            //strcpy(to_send.campaignName, currentPC.name);    //Copy in the campaign name
            esp_event_post_to(dndv_event_h, OUTGOING_BASE, EVENT_SEND_BROADCAST, (void*)&to_send, sizeof(to_send), 0); 
            break;
        default:
            ESP_LOGE("DM Internal", "Did not recognize the internal event.");
    }
}



/* --------TODO: Below this point should be refactored above. This should no longer be needed soon. */


//  Initialize all the DM functions, handles, and variables.
//      currentPlayer = DM Name
//      currentPC = Campaign Name Stuff (TODO: Find uses for HP numbers or remove this functionality)
void DM_Activate(void){
    //int size = 22;
    //arr to_send = {22, malloc()
    uint8_t to_send[2+MAX_NAME_LENGTH] = {N_SYNC_BASE,EVENT_DM_INFO};
    memcpy(&to_send[2], currentPC.name,20);  //I can simply use 20 becasue the data is uint8
    esp_event_handler_instance_register_with(dndv_event_h, DM_RCV_BASE, ESP_EVENT_ANY_ID, DM_rcv, NULL,NULL);
     
    esp_event_handler_instance_unregister_with(dndv_event_h, DEVICE_BASE, ESP_EVENT_ANY_ID, device_rcv); 
                //TODO: UNREGISTERING this means that you cannot deactivate DM mode without a reset (which is fine)
    
            //Syncing is done by dndv_comms
    //Player List
    //PlayerToMAC List
    //NPC List  (Same layout as players, plus attack bonus?)

    esp_event_post_to(dndv_event_h, DM_DEVICE_BASE, EVENT_DM_ACTIVATE, NULL, NULL, 0);
     //No need to divide size of a uint8 array, because sizeof(uint8) = 1
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
    strcpy(currentPlayer.name, "MeDM");
    strcpy(currentPC.name, "AwesomeCampaignTitle");
    DM_Activate();
    printf("DM Mode Activated (Test DM Initialized)\n");
}