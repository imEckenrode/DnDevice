#include "dndv_globals.h"

void device_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data);

//Initialize all global variables to the correct values
void globals_init(){
    current.isDM = false;
    localDevice.displayLogs = false;   //Change this to set if dndv_log logs
    //current.player = &currentPlayer;       //TODO: Pass all through current instead of three variables
    //current.character = &currentPC;

    esp_event_handler_instance_register_with(dndv_event_h, DEVICE_BASE, ESP_EVENT_ANY_ID, device_rcv, NULL,NULL);
}

/*     -- Local Functions (for use in dndv_globals.c) --   */

// Broadcast data by sending to the event loop
static bool comms_broadcastData(void* event_data, size_t event_data_size){
    esp_event_post_to(dndv_event_h, OUTGOING_BASE, EVENT_SEND_BROADCAST, event_data, event_data_size, 0); 
    return true;
}





/*     --- CRUD Functions ---     */

ContactInfo getMyContactInfo(){
    ContactInfo myInfo = current.info;
    return myInfo;
}

bool updateMyKey(KeyIdentifier newKey){current.info.key = newKey; return true;}

Player getMyPlayer(){
    return currentPlayer;
}

PC getMyPC(){
    return currentPC;
}

void updateMyPlayerName(char* name){    
    strcpy(currentPlayer.name, name);
    strcpy(current.info.p_name,name);
}

void updateMyPCName(char* name){            //TODO: Update this to P name and C name
    strcpy(currentPC.name, name); 
    strcpy(current.info.c_name, name);
}



/*          --- Data Retrieval System ---
        Here is the system for retrieving character data. 

        TODO: Move this to the SD card while still having this option
*/







/*  --- HOME OF DEVICE_BASE HANDLING :
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
            ; 
            struct dm_info_s to_send = {
                .event = {N_SYNC_BASE,EVENT_DM_INFO}, 
                .info =  getMyContactInfo()}; //current.info};

            comms_broadcastData((void*)&to_send, sizeof(to_send));
                    //esp_event_post_to(dndv_event_h, OUTGOING_BASE, EVENT_SEND_BROADCAST, (void*)&to_send, sizeof(to_send), 0); 
            printf("Sent, right?\n%s\n",to_send.info.c_name);
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
    esp_event_handler_instance_register_with(dndv_event_h, DM_DEVICE_BASE, ESP_EVENT_ANY_ID, DM_rcv, NULL,NULL);
    //esp_event_handler_instance_unregister_with(dndv_event_h, DEVICE_BASE, ESP_EVENT_ANY_ID, device_rcv);      
                //TODO: UNREGISTERING this means that you cannot deactivate DM mode without a reset (which is fine)
                    //(If this is entirely separate from the DM_rcv, the unregister comment can work)
            //Syncing is done by dndv_comms
    //Player List
    //PlayerToMAC List
    //NPC List  (Same layout as players, plus attack bonus?)

    esp_event_post_to(dndv_event_h, DM_DEVICE_BASE, EVENT_DM_ACTIVATE, NULL, 0, 0);
     //No need to divide size of a uint8 array, because sizeof(uint8) = 1
}



//And finally, tests

void testPCInit(void){
    Player examplePlayer = {1,"Bob",0,false};
    currentPlayer=examplePlayer;
    PC examplePC = {1,"PowerWizard",5,3};
    currentPC=examplePC;

    current.isDM = false;
    strcpy(current.info.p_name,currentPlayer.name);
    strcpy(current.info.c_name,currentPC.name);
    printf("Test Player Initialized\n");
}

void testDMInit(void){
    current.isDM = true;      //TODO: Could have a semaphore something or other on the global level
    current.info.key = 0;
    updateMyPlayerName("MeDM");
    updateMyPCName("AwesomeTitleHere");

    DM_Activate();
    printf("DM Mode Activated (Test DM Initialized)\n");
}