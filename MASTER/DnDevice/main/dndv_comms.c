//#pragma once
#include "dndv_comms.h"

#define TAG "Comms"  //TODO: This should be dynamic and label the PC or GM Name

macAddr broadcast_mac = BROADCAST_MAC;
//               !--  Event Base Lookup --!

//With only a few bases possible, a for loop is sufficient
Num EventBaseP2Num(esp_event_base_t* baseAddress){
    for(Num i = 0; i < EVENT_BASE_ARRAY_SIZE; i++){
        if(baseAddress == EVENT_BASE_ARRAY[i]){
            return i;
        }
    }
    //TODO handle this 255 return and remove this error throw
    abort();
    return -1;
}

esp_event_base_t Num2EventBase(Num num){
    return *EVENT_BASE_ARRAY[num];
}


/*                          --- Sending Functions ---                                 */


/*  -- Auxilary Sending Functions --  */

// - Sending Callback to verify the data sent (automatically returns true for a broadcast) -
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


/*  Calls ESP-NOW's add_peer function if the MAC address is not currently a peer.
        "Peer" = Can be sent to by ESP-NOW
    This is independent of the ContactAddressBook since we can send to devices that aren't in the contact book (i.e. they just woke up and aren't aiming to connect yet)
    
    IMPORTANT: Returns False if the peer already exists                */
bool addIfNewPeer(macAddr mac){
    bool peerExists = esp_now_is_peer_exist(mac);
    if(peerExists){
        return false;
    }
    //Now, since the peer doesn't exist, add it

    const esp_now_peer_info_t info = {
        .channel = 1,
        .ifidx = ESP_IF_WIFI_AP,
        .encrypt = false,
    };
    maccpy(info.peer_addr,mac);
    esp_now_add_peer(&info);
    return true;
}


/*  -- Primary Sending Functions --  */

//Send data to the specified MAC address with event data already included
esp_err_t dndv_send_raw(macAddr mac, void* data, size_t size){
    esp_err_t err = esp_now_send(mac,(void*)data,size);

    if(err != ESP_OK){
        ESP_LOGE(TAG, "Send error (%d)", err);
        return ESP_FAIL;
    } 
    return ESP_OK;
}

//Send data to the specified mac with the specified EVENT and corresponding data
//size is the size of the data alone
esp_err_t dndv_send(macAddr mac, Num eventBaseNum, Num eventIdNum, void* data, size_t size){
    size_t newSize = size+2;
    uint8_t* allData = malloc(newSize);  //This could be a void pointer
    allData[0] = eventBaseNum;
    allData[1] = eventIdNum;
    memcpy(allData+2,data,size);
    esp_err_t result = dndv_send_raw(mac,allData,newSize);
    free(allData);
    return result;
}

esp_err_t dndv_send_blank(macAddr mac, Num eventBaseNum, Num eventIdNum){
    return dndv_send(mac, eventBaseNum, eventIdNum, 0, 0);
}

//Send data to the specified MAC address with a macAndData_s struct pointer (this is a raw way to send)
esp_err_t dndv_sendMAD(macAndData_s* mad, size_t size){
    esp_err_t err = dndv_send_raw(mad->mac,(void*)(mad->data),size);
    if(err != ESP_OK){
        ESP_LOGE(TAG, "Send error (%d)", err);
        return ESP_FAIL;
    } 
    return ESP_OK;
}


//dndv_send_ping
//A test broadcast to test sending and receiving
void dndv_send_ping(void){
    //const uint8_t broadcast_mac[] = BROADCAST_MAC;keyin

    dndv_send_blank(broadcast_mac,N_MISC_BASE,EVENT_PING);
    //esp_now_send(broadcast_mac,(uint8_t*)&dat,sizeof(dat));
    //Could wait for callback here to call more times
}





/*      -- Receiving Function --     

    When any ESP-NOW data is received, post it to the event loop (dndv_event_h, in dndv_data)
  In any other file, use esp_event_handle_register_with to receive the data
*/

//When data is received, find the base and ID, then post the data to the event loop                                 *
//Note: this is run in the WiFi task, so this will take precedence over other tasks
void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len){
    esp_event_base_t base = Num2EventBase(data[0]);
    uint8_t id = data[1];     //TODO: strip the first two bytes from the data
    if (base == COMMS_BASE){     //This would automatically send the data, potentially causing an infinite loop. Do not send this base, or it will be caught in error here
        ESP_LOGE(TAG, "COMMS_BASE is not a sendable base, ended\n");
        return;     //TODO: Validate this data on receive. That way, no one can pretend to be sending from a different device
    }

    short fullDataLen = sizeof(macAndData_s)+len;    //The length of the mac and data struct
    macAndData_s* fullData = malloc(fullDataLen);             //The macAndData_s struct will have the length of a Mac + dataLen
    //TODO: Throw an error if malloc fails here!                    //Could also malloc with len+sizeof(fullData)

    maccpy(fullData->mac,mac_addr);   //Append the MAC address to the data (so no device ever needs to send its MAC inside the data)
    memcpy(fullData->data,data,len);                             //Alternatively, just assign to the pointer fullData+MAC_ADDR_SIZE+sizeof(uint8_t)
    esp_event_post_to(dndv_event_h, base, id, (void*)fullData,fullDataLen,0);
      //Data is automatically managed by the event loop, so a pointer to the data is safe
    free(fullData); //This frees the local malloc
}






/*  This is the function for handling COMMS_BASE events
AKA sending straight from DNDV_Internals or updating comms based on device occurrences*/
void comms_local_event(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        case EVENT_SEND_BROADCAST:
          ESP_LOGV(TAG, "Sending broadcast");
          esp_err_t err = esp_now_send(broadcast_mac,event_data,sizeof(*event_data));

          if(err != ESP_OK){
              ESP_LOGE(TAG, "Send error (%d)", err);
              return;
          }
          ESP_LOGV(TAG, "Success, data away");
          return;
            /*dndv_send_raw(broadcast_mac,(char*)event_data);
            break;  */
        case EVENT_SEND:
            dndv_sendMAD((macAndData_s*) event_data, sizeof(event_data));   //Do I need to copy the data instead of using the data from the event loop? TODO
            break;
        case EVENT_SEND_TO_ALL_CONTACTS:
            dndv_send_raw (NULL, event_data, sizeof(event_data)); //NULL MAC sends to all peers
            break;
        default:
            ESP_LOGE(TAG, "Received bad send event ID, discarding\n");
    }
}


/*      --- Finally, Communication Initialization ---       */
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

    esp_event_handler_instance_register_with(dndv_event_h, COMMS_BASE, ESP_EVENT_ANY_ID, comms_local_event, NULL,NULL);
}

//#endif