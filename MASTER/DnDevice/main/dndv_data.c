#include "dndv_data.h"

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
        .task_stack_size = 4096,      //Up the stack size if this keeps running out of memory, but it should be fine
        .task_core_id = tskNO_AFFINITY
    };

    esp_event_loop_create(&loop_args, &dndv_event_h);
}

/* -EVENT LOOP BASE DEFINITIONS-
Because C doesn't like defining a global variable every time .h is included, so it must be defined here
*/
    ESP_EVENT_DEFINE_BASE(MISC_BASE);
    ESP_EVENT_DEFINE_BASE(DEVICE_BASE);
    ESP_EVENT_DEFINE_BASE(SYNC_BASE);
    ESP_EVENT_DEFINE_BASE(OUTGOING_BASE);

    ESP_EVENT_DEFINE_BASE(DM_RCV_BASE); //Positioned last because DM exclusive

/*  To convert back and forth between the number to send and the local base definition...
        Uses the addresses of the variables, as the names are not required (and are not defined yet)
*/
static esp_event_base_t* EventBases[] = {
    &MISC_BASE,
    &DEVICE_BASE,
    &SYNC_BASE,
    &OUTGOING_BASE,
    
    &DM_RCV_BASE
};//Make sure the N_ enum in dndv_data.h matches above!

//Use this function if you don't have the base hard coded. 
//For hard coded values, simply use N_(name_of_base_here)
uint8_t EventBase2Num(esp_event_base_t base){
    uint8_t size = sizeof(EventBases)/sizeof(esp_event_base_t*);
    for(int i=0; i<size; i++){
        if(*(EventBases[i])==base){         //!(strcmp(*(EventBases[i]),base))){  //If the event base matches the passed in base      //TODO: Check if comparing pointers is enough
            return i;
        }
    }
    printf("Could not locate the specified Event Base.....\n");
    //ESP_LOGE("eventBaseError","Could not locate the specified Event Base.");    //Check above to make sure it exists there
    return 255; //(same as returning -1 for an unsigned integer)
}

//Convert the number to the event base. See above.
esp_event_base_t Num2EventBase(uint8_t num){
    if(num<(sizeof(EventBases)/sizeof(EventBases[0]))){
        return *(EventBases[num]);  //Return the value pointed at because EventBases is filled with pointers to the data
    }
    ESP_LOGE("Num2EventBase","Event base out of range");
    return MISC_BASE;
    //printf("Retrieved %s\n",*(EventBases[num]));
}