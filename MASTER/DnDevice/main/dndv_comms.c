//#pragma once

#include "dndv_comms.h"

#define TAG "DnDevice"  //TODO: This should be dynamic and label the PC or DM Name
#define BROADCAST_MAC {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}

macAddr broadcast_mac = BROADCAST_MAC;


/*     --- Sending Functions ---     */

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
    memcpy(info.peer_addr,mac,MAC_ADDR_SIZE);
    esp_now_add_peer(&info);
    return true;
}


/*  -- Primary Sending Functions --  */

//Send data to the specified MAC address
esp_err_t dndv_send(macAddr mac, void* data, size_t size){
    esp_err_t err = esp_now_send(mac,(void*)data,size);

    if(err != ESP_OK){
        ESP_LOGE(TAG, "Send error (%d)", err);
        return ESP_FAIL;
    } 
    return ESP_OK;
}

//Send data to the specified MAC address with a macAndData_s struct pointer
esp_err_t dndv_sendMAD(macAndData_s* mad, size_t size){
    esp_err_t err = dndv_send(mad->mac,(void*)(mad->data),size);
    if(err != ESP_OK){
        ESP_LOGE(TAG, "Send error (%d)", err);
        return ESP_FAIL;
    } 
    return ESP_OK;
}

/*  Send out any data posted to the event loop to the included MAC address if applicable
    This requires formatting to be done before sending, so it's recommended to use other methods
            //TODO?: Standardize This
*/
void send_from_event(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        case EVENT_SEND_BROADCAST:
          ESP_LOGV(TAG, "Sending broadcast");
          esp_err_t err = esp_now_send(broadcast_mac,event_data,sizeof(*event_data));

          if(err != ESP_OK){
              ESP_LOGE(TAG, "Send error (%d)", err);
              return;
          }
          ESP_LOGV(TAG, "Sending success, data away.");
          return;
/*
            dndv_send(broadcast_mac,(char*)event_data);
            break;  */
        case EVENT_SEND:
            dndv_sendMAD(((macAndData_s*) event_data), sizeof(event_data));   //Do I need to copy the data instead of using the data from the event loop? TODO
            break;
        default:
            ESP_LOGE(TAG, "Received bad send event ID, discarding\n");
    }
}


//dndv_send_onAwake
//This function should be run when the device wakes up to broadcast its prescence to any DM devices
esp_err_t dndv_send_onAwake(void){
    //const uint8_t broadcast_mac[] = BROADCAST_MAC;

    struct EVENT dat;
    dat.BASE = N_SYNC_BASE;                     //Set the correct base and ID for easy unpacking
    dat.ID = EVENT_AWAKE_BROADCAST_RCV;             //TODO: Formalize this into the streamlined IDs system

    esp_err_t err = dndv_send(broadcast_mac,(void*)&dat,sizeof(dat));

    if(err != ESP_OK){
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

    struct EVENT dat;     //If there's no actual data being passed, no need to malloc anything (specific to this function)
    dat.BASE = N_MISC_BASE;                     //Set the correct base and ID for easy unpacking
    dat.ID = EVENT_PING;                    //ID number 3 as of writing this...

    dndv_send(broadcast_mac,&dat,sizeof(dat));
    //esp_now_send(broadcast_mac,(uint8_t*)&dat,sizeof(dat));
    //Could wait for callback here to call more times
}






/*      -- Receiving Function --     

    When any ESP-NOW data is received, post it to the event loop (dndv_event_h, in dndv_data)
  In any other file, use esp_event_handle_register_with to receive the data
*/

//When data is received, find the base and ID, then post the data to the event loop
//Note: this is run in the WiFi task, so this will take precedence over other tasks
void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len){
    esp_event_base_t base = Num2EventBase(data[0]);
    uint8_t id = data[1];     //TODO: strip the first two bytes from the data
    if (base == OUTGOING_BASE){     //This would automatically send the data, potentially causing an infinite loop. Do not send this base, or it will be caught in error here
        ESP_LOGE(TAG, "OUTGOING_BASE is not a sendable base...\nTerminating this call to Outgoing Base\n");
        return;     //TODO: Validate this data on receive. That way, no one can pretend to be sending from a different device
    }

    short fullDataLen = sizeof(macAndData_s)+len;    //The length of the mac and data struct
    macAndData_s* fullData = malloc(fullDataLen);             //The macAndData_s struct will have the length of a Mac + dataLen
    //TODO: Throw an error if malloc fails here!                    //Could also malloc with len+sizeof(fullData)

    memcpy(fullData->mac,mac_addr,MAC_ADDR_SIZE);   //Append the MAC address to the data (so no device ever needs to send its MAC inside the data)
    memcpy(fullData->data,data,len);                             //Alternatively, just assign to the pointer fullData+MAC_ADDR_SIZE+sizeof(uint8_t)
    esp_event_post_to(dndv_event_h, base, id, (void*)fullData,fullDataLen,0);
      //Data is automatically managed by the event loop, so a pointer to the data is safe
    free(fullData); //This frees the local malloc
}




/*    --- Sync DM and Player ---
    For syncing at startup
    Under SYNC_BASE and DM_SYNC_BASE */


/*  -- DM Sync Actions (in order) -- */

//Direct Message the Dungeon Master Data to the desired MAC
esp_err_t DM_DM_Data(macAddr da){
    struct dm_info_s to_send = {
        .event = {N_SYNC_BASE,EVENT_DM_INFO}, 
        .info =  getMyContactInfo()}; //current.info};
    esp_err_t err = dndv_send(da,&to_send,sizeof(to_send));        //Send the struct with both DM name and campaign name alongside the IDs
    if(err != ESP_OK){
        ESP_LOGE(TAG, "Could not send data to the new device.");
        return ESP_FAIL;
    } 
    return ESP_OK;
}

bool addConfirmedPC(){return false;}



/*  -- PC Sync Actions (in order) --  */

bool addPotentialDM(macAndData_s* mad){

    struct dm_info_s* data = (struct dm_info_s*(mad->data));
    ContactInfo* info = &(data->info);
    printf("New DM info received:\nName: %s\nCampaign: %s\nMAC: ",info->p_name,info->c_name);          //TODO: Testing TESTINGs
    printMAC(mad->mac);

    //FOR NOW: CONNECT IMMEDIATELY
    //TODO: CHANGE THIS

    return false;
} 


bool selectDM(){return false;}

/*  When any sync data is passed, act on it.
        This is for the player    */
void sync_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    macAndData_s* da = (macAndData_s*) event_data;
    switch(id){ //If not DM and you receive stuff, call functions here
        case EVENT_DM_INFO:
            addPotentialDM(da);
            break;
        default:
            printf("Someone's syncing out there\n");
    }
}

void dm_sync_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    macAndData_s* da = (macAndData_s*) event_data;
    printf("Heard Syncing...\n");
    switch(id){ //If DM and you receive stuff, call functions here
        case EVENT_AWAKE_BROADCAST_RCV:
            ;   //This is required because C doesn't allow for a symbol like "bool" right after the case statement
            bool newlyAdded = addIfNewPeer(da->mac);
            if(!newlyAdded){ESP_LOGI(TAG, "I already know this device. Sending anyway.\n");}
            DM_DM_Data(da->mac);
            break;
        default:
            printf("Someone's syncing out there\n");
    }


//Update the event handler if the device is/isn't a DM
void update_comms_sync_mode(bool isDM){
    if(isDM){
        esp_event_handler_instance_register_with(dndv_event_h, DM_SYNC_BASE, ESP_EVENT_ANY_ID, dm_sync_rcv, NULL,NULL);
        esp_event_handler_instance_unregister_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, sync_rcv, NULL,NULL);
    }else{
        esp_event_handler_instance_register_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, sync_rcv, NULL,NULL);
        esp_event_handler_instance_unregister_with(dndv_event_h, DM_SYNC_BASE, ESP_EVENT_ANY_ID, dm_sync_rcv, NULL,NULL);
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

    esp_event_handler_instance_register_with(dndv_event_h, OUTGOING_BASE, ESP_EVENT_ANY_ID, send_from_event, NULL,NULL);
    esp_event_handler_instance_register_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, sync_rcv, NULL,NULL);
}

//#endif