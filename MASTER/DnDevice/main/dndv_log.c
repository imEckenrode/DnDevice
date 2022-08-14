#include "dndv_log.h"
#include "dndv_comms.h"

#include "esp_event.h"
#include "esp_log.h"

static void rcvToLog(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
   // ESP_LOGI(TAG,"Data Received!");
    printf("Data is %d", (int) &event_data);     //Bad because the size of the pointers don't match...currently just wanna see any number at all
}


void log_init(void){
    esp_event_handler_instance_register_with(dndv_event_h, ESP_EVENT_ANY_BASE, ESP_EVENT_ANY_ID,rcvToLog,NULL,NULL);
}

