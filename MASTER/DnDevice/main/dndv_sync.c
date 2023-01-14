#include "dndv_sync.h"
#include "dndv_data.h"
#include "dndv_internals.h"
#include "esp_log.h"
#include "esp_err.h"

#define TAG "Sync"  //TODO: This should be dynamic and label the PC or GM Name

/* SYNC TEST FUNCTIONS:

    Currently, the tests are run automatically when a DM activates.
    When a DM is detected, the player asks that DM
*/

//          TODO: define a method for getting the DM MAC

bool addAsDM_test(ContactAddress* mad){ //TODO: Instead I need this as a method across
    //current.gmInfo.gmName = "Test";
    //current.gmInfo.campaignName = "AwesomeName";
    memcpy(current.gmInfo.MAC, mad->MAC, 6);
    //current.gmInfo.MAC = *mad.MAC;
    //printf("New GM: %s, %s",*mad->info.p_name,*mad->info.c_name);
    return true;
} 

void requestPlayer1_test(){
    struct keydata_req_s keyData = {1};
    dndv_send(current.gmInfo.MAC, EventBaseP2Num(GM_SYNC_BASE), EVENT_KEYDATA_REQ, &keyData, sizeof(struct keydata_req_s));
}

void requestPC1_test(){
    short selection = 1;
    dndv_send(current.gmInfo.MAC, EventBaseP2Num(GM_SYNC_BASE), EVENT_PC_REQ, &selection, sizeof(short));
}

//and on the DM side

Player retrieveAndSendKey_test(macAndData_s* da){
    Player retrieved = {"B","Bill",false,false};  //Legal because nickname and name are predefined sizes
    dndv_send(da->mac, EventBaseP2Num(SYNC_BASE), EVENT_KEYDATA_RCV, &retrieved, sizeof(Player));
    return retrieved;
}

PC retrieveAndSendPC_test(macAndData_s* da){
    PC retrieved = {"J","Full Name",75,158,16};
    dndv_send(da->mac, EventBaseP2Num(SYNC_BASE), EVENT_KEYDATA_RCV, &retrieved, sizeof(PC));
    return retrieved;
}

//  END OF SYNC TEST FUNCTIONS

/*          --  SYNC_BASE: For syncing data and Player devices  --
    See GM_SYNC_BASE for the GM side

        Used primarily by dndv_comms
    Contains all data for syncing. Players should stop listening to these events once in the campaign
*/
enum SYNC_B_ID{
    EVENT_AWAKE_BROADCAST_RCV,      //Broadcasted on awake, mostly so active GMs can send directly to this new device   (TODO: make sure it's safe, then remove it from here)
    EVENT_GM_INFO,          //[Uses gm_info_s]. Broadcasted when a device becomes a GM. Transmits the GM name and campaign name

    EVENT_KEYDATA_RCV,       //The Key Data         requested through the key was received
    EVENT_PCDATA_RCV,        //The Character Data   requested through the key was received
    EVENT_KEYANDPC_RCV     //The Key and Character Data
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


            /*    -- Sync - PlayerSide --
                For syncing at startup   */
// First, any manual functions (should be exposed in dndv_sync.h)


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
            addAsDM_test(da);
            requestPlayer1_test();
            break;
        case EVENT_KEYDATA_RCV:     //TODO: Add a device event KEYDATA_UPDATE for when the updating here finishes
            updateMyPlayer((Player*) da->data);
            requestPC1_test();
            break;
        case EVENT_PCDATA_RCV:
            updateMyPC((PC*) da->data);  
            break;

        case EVENT_AWAKE_BROADCAST_RCV:
            break;
        default:
            printf("Someone's syncing out there\n");
    }
}





/*              =- GM Sync Actions -=           */


/*          --  GM_SYNC_BASE: For all events targeted to the GM from other devices  --
    These are GM exclusive actions that should only heard by GM_ACTIVATE (and whatever logs want it)*/
enum GM_RCV_B_ID{
    EVENT_AWAKE_BROADCAST_GM_RCV,      //Broadcasted on awake, so active GMs can send directly to this new device
    EVENT_SYNC_REQ,         //When a player device asks for the GM info
    EVENT_KEYDATA_REQ,      //Return the data requested for a specified key.
    EVENT_PC_REQ       //Return the date for the requested player character

    //EVENT_PC_JOINED,            //A PC has joined the adventure!
    //EVENT_PC_READY
};

//KeyData returns player info if the key is for a player       //TODO: Return NPC data as well
struct __attribute__((__packed__)) keydata_req_s{
    Key key;
};


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


Player retrieveAndSendKey(macAndData_s* da){
    Player retrieved = db_read_player((Key) da->data);
    dndv_send(da->mac, EventBaseP2Num(SYNC_BASE), EVENT_KEYDATA_RCV, &retrieved, sizeof(Player));
    return retrieved;
}

PC retrieveAndSendPC(macAndData_s* da){
    PC retrieved = db_read_pc((Key) da->data);
    dndv_send(da->mac, EventBaseP2Num(SYNC_BASE), EVENT_KEYDATA_RCV, &retrieved, sizeof(PC));
    return retrieved;
}



void gm_sync_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    macAndData_s* da = (macAndData_s*) event_data;
    printf("Heard Syncing...\n");
    switch(id){ //If GM and you receive stuff, call functions here
        case EVENT_AWAKE_BROADCAST_RCV:
            ;   //This is required because C doesn't allow for a symbol like "bool" right after the case statement
            bool newlyAdded = addIfNewPeer(da->mac);
            if(!newlyAdded){ESP_LOGI(TAG, "I already know this device. Sending.\n");}
            GM_DM_Data(da->mac);
            break;
        case EVENT_SYNC_REQ:         //When a player selects the GM's campaign, let the GM know so the player isn't left behind?        Not implemented yet (nor needed, likely)
            if(contactExistWithMAC(da->mac)){
                ContactAddress ca = {da->mac, {0,da->mac,""}};
                createContact(ca);
            }else{print("%d rejoined", da->mac);}
            break;
        case EVENT_KEYDATA_REQ:
            retrieveAndSendKey_test(da);          // Player selected = 
            //ContactAddress 
            //createOrUpdateContact();      //TODO: Either update as retrieved or update when the adventure starts
            break;
        case EVENT_PC_REQ:
            retrieveAndSendPC_test(da);
            //createOrUpdateContact();
            break;
        default:
            printf("Sync not known\n");
    }
}

//Update the event handler if the device is/isn't a GM:         TODO, DO THIS
void update_comms_sync_mode(bool isGM){
    if(isGM){
        esp_event_handler_instance_register_with(dndv_event_h, GM_SYNC_BASE, ESP_EVENT_ANY_ID, gm_sync_rcv, NULL,NULL);
        esp_event_handler_instance_unregister_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, NULL);
    }else{
        esp_event_handler_instance_register_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, sync_rcv, NULL,NULL);
        esp_event_handler_instance_unregister_with(dndv_event_h, GM_SYNC_BASE, ESP_EVENT_ANY_ID, NULL);
    }
}

//This function should be run when the device wakes up to broadcast its prescence to any GM devices
esp_err_t dndv_send_onAwake(void){
    //const uint8_t broadcast_mac[] = BROADCAST_MAC;
    return dndv_send_blank(broadcast_mac, N_SYNC_BASE, EVENT_AWAKE_BROADCAST_RCV);

    //Could wait for callback here to call more times instead of returning immediately
}

void sync_init(void){
        esp_event_handler_instance_register_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, sync_rcv, NULL,NULL);
}