//#pragma once

#include "dndv_comms.h"

#define TAG "DnDevice"  //TODO: This should be dynamic and label the PC or GM Name
#define BROADCAST_MAC {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}

macAddr broadcast_mac = BROADCAST_MAC;

/*  --- BASE DEFINITIONS --- */
ESP_EVENT_DEFINE_BASE(SYNC_BASE);
ESP_EVENT_DEFINE_BASE(GM_SYNC_BASE);


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

/*          --  SYNC_BASE: For syncing data GMs and Player devices  --
        Used primarily by dndv_comms
    Contains all data for syncing. Players should stop listening to these events once in the campaign
        */
enum SYNC_B_ID{
    EVENT_AWAKE_BROADCAST_RCV,      //Broadcasted on awake, mostly so active GMs can send directly to this new device   (TODO: make sure it's safe, then remove it from here)
    EVENT_GM_INFO,          //[Uses gm_info_s]. Broadcasted when a device becomes a GM. Transmits the GM name and campaign name

    EVENT_KEYDATA_RCV,       //The Key Data         requested through the key was received
    EVENT_PCDATA_RCV,        //The Character Data   requested through the key was received
    EVENT_KEYANDPC_RCV,     //The Key and Character Data
};  
    
/* Data broadcasted when the GM is set up, or messaged directly when requested by a player */
//see ContactAddress

struct __attribute__((__packed__)) keydata_rcv_s{
    Key key;
    Player playerInfo;
    bool nickNamesRcv;  //This is True if there are more than 8 characters to send
    bool longNamesRcv;  //This is True if there are only 1 or 2 characters to send and you prefer to use the long names
    union{
        //For more than 8 characters
        struct __attribute__((__packed__)) {  //10 Bytes Each
            Key key;
            NickName name;
        } nickList[21];        //Currently 21 since Key+Player < 40

        //For between 2 and 8 characters
        struct __attribute__((__packed__)) {
            Key key;
            Name name;
        } nameList[8];           //Currently 8 since Key+Player < 40

        //For only 1 or 2 characters, can send the full names if desired
        struct __attribute__((__packed__)) {
            Key key;
            FullName nick;
        } fullnameList[2];           //2 long names = 192
    } pcList;
};


struct __attribute__((__packed__)) pcdata_rcv_s{
    Key key;
    PC pcInfo;
};


/*          --  GM_SYNC_BASE: For all events targeted to the GM from other devices  --
    These are GM exclusive actions that should only heard by GM_ACTIVATE (and whatever logs want it)*/
enum GM_RCV_B_ID{
    EVENT_AWAKE_BROADCAST_GM_RCV,      //Broadcasted on awake, so active GMs can send directly to this new device
    EVENT_SYNC_REQ,         //When a player device asks for the GM info
    EVENT_KEYDATA_REQ,      //Return the data requested for a specified key.
    EVENT_PC_REQ,       //Return the date for the requested player character

    //EVENT_PC_JOINED,            //A PC has joined the adventure!
    //EVENT_PC_READY
};

//KeyData returns player info if the key is for a player       //TODO: Return NPC data as well
struct __attribute__((__packed__)) keydata_req_s{
    Key key;
};



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
    memcpy(info.peer_addr,mac,MAC_ADDR_SIZE);
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
    //const uint8_t broadcast_mac[] = BROADCAST_MAC;

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

    memcpy(fullData->mac,mac_addr,MAC_ADDR_SIZE);   //Append the MAC address to the data (so no device ever needs to send its MAC inside the data)
    memcpy(fullData->data,data,len);                             //Alternatively, just assign to the pointer fullData+MAC_ADDR_SIZE+sizeof(uint8_t)
    esp_event_post_to(dndv_event_h, base, id, (void*)fullData,fullDataLen,0);
      //Data is automatically managed by the event loop, so a pointer to the data is safe
    free(fullData); //This frees the local malloc
}





            /*    --- Sync Player and GM ---
                For syncing at startup
            Under SYNC_BASE and GM_SYNC_BASE respectively as listed above */    //TODO: Maybe move those bases down here with the other sync actions
// First, any manual functions (should be exposed in dndv_comms.h)



/*  -- Automatic PC Sync Actions (in order) --  */

bool addPotentialGM(ContactAddress* mad){
    createOrUpdateContact(*mad);
    printf("New GM: %s, %s",*mad->info.p_name,*mad->info.c_name);
    return true;
} 


bool selectGM(){return false;}

/*  Finally, the event receiver to answer the requests (that the player receives) */
void sync_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    macAndData_s* da = (macAndData_s*) event_data;
    switch(id){ //If not GM and you receive stuff, call functions here
        case EVENT_GM_INFO:
            addPotentialGM(da);
            break;
        case EVENT_KEYDATA_RCV:     //TODO: Add a device event KEYDATA_UPDATE for when the updating here finishes
            
            //current.info.key = 
            //current.info.p_name = 
            break;
        case EVENT_PCDATA_RCV:
            //current.info.c_name =
            
            break;

        case EVENT_AWAKE_BROADCAST_RCV:
            break;
        default:
            printf("Someone's syncing out there\n");
    }
}





/*              -- GM Sync Actions --           */

//Direct Message the Game Master Data to the desired MAC
esp_err_t GM_DM_Data(macAddr da){
    ContactInfo myInfo = getMyContactInfo();    //could take directly from current.Key and go a few more steps (since gmInfo is right there), but we'll be safe
    esp_err_t err = dndv_send(da,N_SYNC_BASE,EVENT_GM_INFO,&myInfo,sizeof(ContactInfo));
    if(err != ESP_OK){
        ESP_LOGE(TAG, "Could not send data to the new device.");
        return ESP_FAIL;
    } 
    return ESP_OK;
}

bool addConfirmedPC(){return false;}


/*      - Automatic GM Sync Actions (in order)  - */



void gm_sync_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    macAndData_s* da = (macAndData_s*) event_data;
    printf("Heard Syncing...\n");
    switch(id){ //If GM and you receive stuff, call functions here
        case EVENT_AWAKE_BROADCAST_RCV:
            ;   //This is required because C doesn't allow for a symbol like "bool" right after the case statement
            bool newlyAdded = addIfNewPeer(da->mac);
            if(!newlyAdded){ESP_LOGI(TAG, "I already know this device. Sending anyway.\n");}
            GM_DM_Data(da->mac);
            break;
        case EVENT_SYNC_REQ:         //When a player selects the GM's campaign, let the GM know so the player isn't left behind.        Not implemented yet (nor needed, likely)
            if(contactExistWithMAC(da->mac)){
                ContactAddress ca = {da->mac, {0,da->mac,""}};
                createContact(ca);
            }else{print("%d rejoined", da->mac);}
            break;
        case EVENT_KEYDATA_REQ:
            //retrieveAndSendKey(da);      //Cast into correct type (and TODO actually define the thing)
            //createOrUpdateContact();
            break;
        case EVENT_PC_REQ:
            //retrieveAndSendPC(da);
            //createOrUpdateContact();
            break;
        default:
            printf("Sync not known\n");
    }
}

//Update the event handler if the device is/isn't a GM
void update_comms_sync_mode(bool isGM){
    if(isGM){
        esp_event_handler_instance_register_with(dndv_event_h, GM_SYNC_BASE, ESP_EVENT_ANY_ID, gm_sync_rcv, NULL,NULL);
        esp_event_handler_instance_unregister_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, NULL);
    }else{
        esp_event_handler_instance_register_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, sync_rcv, NULL,NULL);
        esp_event_handler_instance_unregister_with(dndv_event_h, GM_SYNC_BASE, ESP_EVENT_ANY_ID, NULL);
    }
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
        case EVENT_BROADCAST_NEW_GM:
            update_comms_sync_mode(true);
        default:
            ESP_LOGE(TAG, "Received bad send event ID, discarding\n");
    }
}



//This function should be run when the device wakes up to broadcast its prescence to any GM devices
esp_err_t dndv_send_onAwake(void){
    //const uint8_t broadcast_mac[] = BROADCAST_MAC;
    return dndv_send_blank(broadcast_mac,N_SYNC_BASE, EVENT_AWAKE_BROADCAST_RCV);

    //Could wait for callback here to call more times instead of returning immediately
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
    esp_event_handler_instance_register_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, sync_rcv, NULL,NULL);
}

//#endif