//#pragma once

#include "dndv_comms.h"
#include "dndv_internals.h"

#include "esp_wifi.h"
#include "esp_log.h"

#define TAG "DnDevice"
#define BROADCAST_MAC {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}

void comms_init(void){
  const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK( esp_netif_init());
    ESP_ERROR_CHECK( esp_event_loop_create_default() );
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );      //default is Flash, can turn into RAM
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_APSTA) );     //Should this be APSTA?
    ESP_ERROR_CHECK( esp_wifi_start() );
    ESP_ERROR_CHECK( esp_now_init() );
    ESP_ERROR_CHECK( esp_now_register_recv_cb(rcv_cb) );
    ESP_ERROR_CHECK( esp_now_register_send_cb(sent_cb) );
    //ESP_ERROR_CHECK( esp_now_set_pmk((const uint8_t *)MY_ESPNOW_PMK) );

    const esp_now_peer_info_t broadcast_destination = {
        .peer_addr = BROADCAST_MAC,
        .channel = 1,
        .ifidx = ESP_IF_WIFI_AP
    };

    ESP_ERROR_CHECK( esp_now_add_peer(&broadcast_destination) );


    esp_event_loop_args_t loop_args = {
        .queue_size = 5,
        .task_name = "rcv_task",     //A task will be created automatically 
        .task_priority = uxTaskPriorityGet(NULL),
        .task_stack_size = 2048,      //Up the stack size if this keeps running out of memory, but it should be fine
        .task_core_id = tskNO_AFFINITY
    };

    esp_event_loop_create(&loop_args, &rcv_event_handle);
}


void sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status){
  if (mac_addr == NULL) {
      ESP_LOGE(TAG, "Send cb arg error");
      return;
  }

  if(status==0){
    ESP_LOGI(TAG, "Successfully sent data.");
  }else{
    ESP_LOGE(TAG, "Failed to send data.");
  }
  printf("Send Status: %d (0 is Success)\n",status);
  //xEventGroupSetBits(s_evt_group, BIT(status));
}

/*      Sending Functions      */

//dndv_send_onAwake
//This function should be run when the device wakes up to broadcast its prescence to any DM devices
esp_err_t dndv_send_onAwake(void){
    const uint8_t broadcast_mac[] = BROADCAST_MAC;

    sending_data dat;
    dat.ID = 1;

    esp_err_t err = esp_now_send(broadcast_mac,(uint8_t*)&dat,sizeof(dat));

    if(err != ESP_OK)
    {
        ESP_LOGE(TAG, "Send error (%d)", err);
        return ESP_FAIL;
    }
    return ESP_OK;
    //Could wait for callback here to call more times
}








/*      Receiving Function     

    When any ESP-NOW data is received, post it to the event loop
  In another file, use esp_event_handle_register_with to receive the 
*/

ESP_EVENT_DECLARE_BASE(RCV_BASE);
ESP_EVENT_DEFINE_BASE(RCV_BASE);

enum {
  EVENT_AWAKE_BROADCAST,
  EVENT_KEYIN,
  EVENT_SYNC_REQUEST,
  EVENT_FIGHT_ACTION,
  EVENT_FIGHT_CONTROL,
  EVENT_SYS,
  EVENT_TEST
};

void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len){
  ESP_LOGI(TAG, "Saw some data out there.");
  esp_event_post_to(rcv_event_handle, RCV_BASE,EVENT_TEST,data,len,0);
  ESP_LOGI(TAG, "Should be recorded now.");
  //Data is automatically managed by the event loop, so a pointer to the data is safe
}









//#endif