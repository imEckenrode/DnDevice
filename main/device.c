#include "device.h"

void nvs_init(void){        //Needed for WiFi and the DB
    esp_err_t ret = nvs_flash_init();   //Initialize the nvs, and use the return to clear out if more space is needed
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
        .task_stack_size = 4096,      //Up the stack size if this keeps running out of memory, but it should be fine
        .task_core_id = tskNO_AFFINITY
    };
    esp_event_loop_create(&loop_args, &dndv_event_h);
}

/*    --- Event Loop Internal Code ---      
    UI uses LVGL's built-in handler and can be seen in screen_control.c
*/

    ESP_EVENT_DEFINE_BASE(DATA_CHANGED_BASE);
    //ESP_EVENT_DEFINE_BASE(SETTINGS_CHANGED_BASE);