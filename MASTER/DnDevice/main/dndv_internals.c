#include "dndv_internals.h"

void nvs_init(void){
    esp_err_t ret = nvs_flash_init();   //Initialize the nvs, and use "ret"urn to clear out if more space is needed
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK( nvs_flash_erase() );
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void eventLoop_init(void){
    ESP_ERROR_CHECK( esp_event_loop_create_default() );

    esp_event_loop_args_t loop_args = {
        .queue_size = 20,
        .task_name = "eventLoopTask",     //A task will be created automatically 
        .task_priority = uxTaskPriorityGet(NULL),
        .task_stack_size = 2048,      //Up the stack size if this keeps running out of memory, but it should be fine
        .task_core_id = tskNO_AFFINITY
    };

    esp_event_loop_create(&loop_args, &dndv_event_h);
}

/* -EVENT LOOP BASE DEFINITIONS-
Because C doesn't like me defining a global variable every time .h is included
*/
    ESP_EVENT_DEFINE_BASE(MISC_BASE);




/*      - DM EXCLUSIVE FUNCTIONS -
    Here are the functions exclusive to the DM

    To keep this exclusivity, DM_Activate brings 

*/

void dmAct(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    printf("Heard some stuff out there...as a DM\n");
}



//  Initialize all the DM functions, handles, and variables.
void DM_Activate(void){
    //Player List
    //PlayerToMAC List
    //NPC List  (Same layout as players, plus attack bonus?)
    
    esp_event_handler_instance_register_with(dndv_event_h, ESP_EVENT_ANY_BASE, ESP_EVENT_ANY_ID, dmAct, NULL,NULL);
}       //TODO: Change back to DM_RCV_BASE 




void testPCInit(void){

    Player examplePlayer = {1,"Bob",0};
    currentPlayer=examplePlayer;
    Character examplePC = {1,"PowerWizard",5,3};
    currentPC=examplePC;

    currentUser.DM = false;
    currentUser.player = &currentPlayer;
    currentUser.character = &currentPC;
    printf("Test Player Initialized\n");
}

void testDMInit(void){
    currentUser.DM = true;      //TODO: Could have a semaphore something or other on the global level
    DM_Activate();
    printf("DM Mode Activated (Test DM Initialized)\n");
}