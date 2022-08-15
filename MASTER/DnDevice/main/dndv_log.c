#include "dndv_log.h"

static void rcvToLog(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
   // ESP_LOGI(TAG,"Data Received!");
    sending_data* data_rcv = (sending_data*) event_data;
    printf("\nBase:%s\nID:%d\n",Num2EventBase(data_rcv->BASE),data_rcv->ID);
}


void log_init(void){    //Uncomment here to log all events with the command above
    esp_event_handler_instance_register_with(dndv_event_h, ESP_EVENT_ANY_BASE, ESP_EVENT_ANY_ID, rcvToLog,NULL,NULL);
    return;
}

