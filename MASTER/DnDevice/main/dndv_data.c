#include "dndv_data.h"

void nvs_init(void){        //TODO: Needed for WiFi (I believe) and the DB
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


/* _- Auxillary Functions -_
    Nice assistant functions    */

//Memcopy commands for Mac Addresses
void *maccpy(void *dest, const void * src){
    return memcpy(dest,src,MAC_ADDR_SIZE);
}

bool printMAC(macAddr MAC){
    printf("%x:%x:%x:%x:%x:%x", MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5]);
    return true;
}


/*    --- Event Loop Internal Code ---      */

/* -EVENT LOOP BASE DEFINITIONS-
    C doesn't like defining a global variable every time .h is included, so it must be defined in the .c file

    This is not a comprehensive list, since events can be defined anywhere.
    For example, see dndv_comms.h for the syncing events.
*/
    ESP_EVENT_DEFINE_BASE(GM_DEVICE_BASE);
    ESP_EVENT_DEFINE_BASE(DEVICE_BASE);
    ESP_EVENT_DEFINE_BASE(COMMS_BASE);
    ESP_EVENT_DEFINE_BASE(MISC_BASE);

