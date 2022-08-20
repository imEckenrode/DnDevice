//#pragma once

#include "dndv_comms.h"

#define TAG "DnDevice"  //TODO: This should be dynamic and label the PC or DM Name
#define BROADCAST_MAC {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}

macAddr broadcast_mac = BROADCAST_MAC;


/*     -- Sending Functions --     */

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

    IMPORTANT: Returns True if the peer already exists                */
bool addIfNewPeer(macAddr mac){
    bool peerExists = esp_now_is_peer_exist(mac);
    if(peerExists){
        return true;
    }
    //Now, since the peer doesn't exist, add it

    const esp_now_peer_info_t info = {
        .channel = 1,
        .ifidx = ESP_IF_WIFI_AP,
        .encrypt = false,
    };
    memcpy(info.peer_addr,mac,MAC_ADDR_SIZE);
    esp_now_add_peer(&info);
    return false;
}

//Send data to the specified MAC address
esp_err_t dndv_send(macAddr mac, void* data, size_t size){
    esp_err_t err = esp_now_send(mac,(void*)data,size);

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
    dat.BASE = N_SYNC_BASE;                     //Set the correct base and ID for easy unpacking
    dat.ID = EVENT_AWAKE_BROADCAST_RCV;

    esp_err_t err = dndv_send(broadcast_mac,(void*)&dat,sizeof(dat));

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
    dat.event.BASE = N_MISC_BASE;                     //Set the correct base and ID for easy unpacking
    dat.event.ID = EVENT_PING;        //ID number 3 as of writing this...

    esp_now_send(broadcast_mac,(uint8_t*)&dat,sizeof(dat));
    //Could wait for callback here to call more times
}






/*      -- Receiving Function --     

    When any ESP-NOW data is received, post it to the event loop (dndv_event_h, in dndv_internals)
  In any other file, use esp_event_handle_register_with to receive the data
*/

//When data is received, find the base and ID, then post the data to the event loop
//Note: this is run in the WiFi task, so this will take precedence over other tasks
void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len){
    esp_event_base_t base = Num2EventBase(data[0]);
    uint8_t id = data[1];     //TODO: strip the first two bytes from the data
    if (base == OUTGOING_BASE){     //This would automatically send the data, potentially causing an infinite loop. Do not send this base, or it will be caught in error here
        ESP_LOGE(TAG, "OUTGOING_BASE will cause an infinite loop!\nAvoid sending Outgoing Base if you want your data to arrive correctly\n");
        return;
    }
    //The length of the mac and data struct
    short fullDataLen = len+MAC_ADDR_SIZE+sizeof(uint8_t);     //The macAndData struct will have the length of a Mac + dataLen (a uint8 to track data) + the data length
    macAndData* fullData = malloc(fullDataLen);     
    //TODO: Throw an error if malloc fails here!    
    memcpy(fullData->mac,mac_addr,MAC_ADDR_SIZE);   //Append the MAC address to the data just in case that is wanted
    fullData->dataLen = len;
    memcpy(fullData->data,data,len);                             //Alternatively, just assign to the pointer fullData+MAC_ADDR_SIZE+sizeof(uint8_t)
    esp_event_post_to(dndv_event_h, base, id, (void*)data,fullDataLen,0);
    free(fullData); //This frees the malloc'd memory
  //Data is automatically managed by the event loop, so a pointer to the data is safe
}




/*    -- Sync DM and Player --
    For syncing at startup

    Under SYNC_BASE 
*/


/*  -DM Sync Actions (in order)- */

//Direct Message the Dungeon Master Data
bool DM_DM_Data(macAndData* da){
    //dndv_send();
    return false;
}

bool addPotentialDevice(){return false;}

bool addConfirmedPC(){return false;}


/*  -PC Sync Actions (in order)- */

bool addPotentialDM(){return false;}


bool selectDM(){return false;}

/*  When any sync data is passed, act on it.
        Different actions for DM vs. non-DM     */
void sync_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    macAndData* da = (macAndData*) event_data;
    if(current.isDM){
        switch(id){ //If DM and you receive stuff, call functions here
            case EVENT_AWAKE_BROADCAST_RCV:
                ;   //This is required because C doesn't allow for a symbol like "bool" right after the case statement
                bool addedBefore = addIfNewPeer(da->mac);
                if(addedBefore){ESP_LOGI(TAG, "I already sent to this device today, did he go offline? Continuing.");}
                DM_DM_Data(da);
                break;
            case EVENT_INFO_ACK:
                addPotentialDevice();
                break;
            default:
                printf("Heard some syncs, but not for the DM.\n");
        }
    }else{
        switch(id){ //If not DM and you receive stuff, call functions here
            case EVENT_DM_INFO:
                addPotentialDM();
                break;
            default:
                printf("Heard some syncs, but I'm not a DM.\n");
        }
    }
}

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
    esp_event_handler_instance_register_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, send_from_event, NULL,NULL);
}

//#endif