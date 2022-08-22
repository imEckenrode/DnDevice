#include "dndv_log.h"

#define LogTAG "DLog"
static void rcvToLog(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    //ESP_LOGV("LOG","Data Received!");
    struct IDs* data_rcv = (struct IDs*) event_data;
    //printf("\nBase Name: %s",Num2EventBase(data_rcv->event.BASE));
    //printf("\nBase:%d\nID:%d\n",data_rcv->event.BASE,data_rcv->event.ID);

    switch(EventBase2Num(base)){    //
        case 255:
            ESP_LOGV(LogTAG, "Unidentified Base");
            break;
        //case N_SYNC_BASE:

        default:
            printf("Received___\nBase: %s\n ID: %d\n",base, id);  //If there's nothing custom for the event, do the default behavior
    }

    //if(base!=Num2EventBase(data_rcv->BASE)){ESP_LOGI(LogTAG, "This data lacks the first two elements");}
}


void log_init(void){    //Uncomment here to log all events with the command above
    esp_event_handler_instance_register_with(dndv_event_h, ESP_EVENT_ANY_BASE, ESP_EVENT_ANY_ID, rcvToLog,NULL,NULL);
    return;
}

