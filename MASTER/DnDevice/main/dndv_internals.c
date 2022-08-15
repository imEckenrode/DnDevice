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
    currentUser.DM = true;

    printf("DM Mode Activated (Test DM Initialized)\n");
}