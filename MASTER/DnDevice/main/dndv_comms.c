//#pragma once

#include "dndv_comms.h"

#define TAG "DnDevice"  //TODO: This should be dynamic and label the PC or DM Name
#define BROADCAST_MAC {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}

macAddr broadcast_mac = BROADCAST_MAC;



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

//Send data to the specified MAC address
esp_err_t dndv_send(macAddr mac, uint8_t* data){
    esp_err_t err = esp_now_send(mac,(uint8_t*)&data,sizeof(data));

    if(err != ESP_OK)
    {
        ESP_LOGE(TAG, "Send error (%d)", err);
        return ESP_FAIL;
    }
    return ESP_OK;
}


/*  Send out any data posted to the event loop to the included MAC address if applicable
    This requires formatting to be done before sending, so it's recommended to use other methods */
void send_from_event(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        case EVENT_SEND_BROADCAST:
          ESP_LOGV(TAG, "Sending broadcast");
          esp_err_t err = esp_now_send(broadcast_mac,event_data,22);

          if(err != ESP_OK)
          {
              ESP_LOGE(TAG, "Send error (%d)", err);
              return;
          }
          ESP_LOGV(TAG, "Sending success, data away.");
          return;

/*
            dndv_send(broadcast_mac,(char*)event_data);
            break;
        case EVENT_SEND:
            dndv_send(((send_it*) event_data)->MAC,((send_it*) event_data)->data);   //Cast to the data type as you pass it through
            break;  */
        default:
            //dndv_send_to_all(event_data);
            printf("Here's where I send it to everyone...yeah, put it on the TODO...\n");  //TODO: send to all function
    }
}




//dndv_send_onAwake
//This function should be run when the device wakes up to broadcast its prescence to any DM devices
esp_err_t dndv_send_onAwake(void){
    //const uint8_t broadcast_mac[] = BROADCAST_MAC;

    struct IDs dat;
    dat.BASE = N_DM_RCV_BASE;                     //Set the correct base and ID for easy unpacking
    dat.ID = EVENT_AWAKE_BROADCAST_RCV;

    esp_err_t err = dndv_send(broadcast_mac,(uint8_t*)&dat);

    if(err != ESP_OK)
    {
        ESP_LOGE(TAG, "Send error (%d)", err);
        return ESP_FAIL;
    }
    return ESP_OK;
    //Could wait for callback here to call more times
}

//dndv_send_ping
//A test broadcast to test sending and receiving
void dndv_send_ping(void){
    //const uint8_t broadcast_mac[] = BROADCAST_MAC;

    rcvg_data dat;
    dat.BASE = N_MISC_BASE;                     //Set the correct base and ID for easy unpacking
    dat.ID = EVENT_PING;        //ID number 3 as of writing this...

    esp_now_send(broadcast_mac,(uint8_t*)&dat,sizeof(dat));
    //Could wait for callback here to call more times
}






/*      Receiving Function     

    When any ESP-NOW data is received, post it to the event loop (dndv_event_h, in dndv_internals)
  In any other file, use esp_event_handle_register_with to receive the data
*/

//When data is received, find the base and ID, then post the data to the event loop
void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len){
  esp_event_base_t base = Num2EventBase(data[0]);
  uint8_t id = data[1];     //TODO: strip the first two bytes from the data
  if (base == OUTGOING_BASE){     //This would automatically send the data, potentially causing an infinite loop. Do not send this base, or it will be caught in error here
      ESP_LOGE(TAG, "OUTGOING_BASE will cause an infinite loop!\nAvoid sending Outgoing Base if you want your data to arrive correctly\n");
      return;
  }
  esp_event_post_to(dndv_event_h, base, id, (void*)data,len,0);
  //Data is automatically managed by the event loop, so a pointer to the data is safe
}




/*    - Sync DM To Player -
    For syncing at startup

    Under SYNC_BASE 
*/



void comms_init(void){
  const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK( esp_netif_init());

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

    esp_event_handler_instance_register_with(dndv_event_h, OUTGOING_BASE, ESP_EVENT_ANY_ID, send_from_event, NULL,NULL);
}

//#endif