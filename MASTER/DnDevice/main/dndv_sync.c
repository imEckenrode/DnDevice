#include "dndv_sync.h"
#include "dndv_data.h"
#include "dndv_internals.h"
#include "esp_log.h"
#include "esp_err.h"
#include "dndv_comms.h"

#define TAG "Sync"  //TODO: This should be dynamic and label the PC or GM Name

/*  --- BASE DEFINITIONS --- */
ESP_EVENT_DEFINE_BASE(SYNC_BASE);
ESP_EVENT_DEFINE_BASE(GM_SYNC_BASE);


/* SYNC TEST FUNCTIONS:

    Currently, the tests are run automatically when a DM activates.
    When a DM is detected, the player asks that DM
*/

//          TODO: define a method for getting the DM MAC

bool addAsDM_test(ContactAddress* mad){ //TODO: Instead I need this as a method across
    //current.gmInfo.gmName = "Test";
    //current.gmInfo.campaignName = "AwesomeName";
    maccpy(current.gmInfo.MAC, mad->MAC);
    //current.gmInfo.MAC = *mad.MAC;
    //printf("New GM: %s, %s",*mad->info.p_name,*mad->info.c_name);

    addIfNewPeer(mad->MAC);
    return true;
} 

void requestPlayer1_test(){
    Key key = 1;
    dndv_send(current.gmInfo.MAC, EventBaseP2Num(&GM_SYNC_BASE), 2, &key, sizeof(Key));
}

void requestPC1_test(){
    short selection = 1;
    dndv_send(current.gmInfo.MAC, EventBaseP2Num(&GM_SYNC_BASE), 3, &selection, sizeof(short));
}

//and on the GM side

Player retrieveAndSendKey_test(macAndData_s* da){
    addIfNewPeer(da->mac);
    Player retrieved = {"B","Bill",false,false};  //Legal because nickname and name are predefined sizes
    dndv_send(da->mac, EventBaseP2Num(&SYNC_BASE), 2, &retrieved, sizeof(Player));
    return retrieved;
}

PC retrieveAndSendPC_test(macAndData_s* da){
    PC retrieved = {"J","Full Name",75,158,16};
    dndv_send(da->mac, EventBaseP2Num(&SYNC_BASE), 3, &retrieved, sizeof(PC));
    return retrieved;
}

//  END OF SYNC TEST FUNCTIONS

            /*    -- Sync - PlayerSide --
                For syncing at startup   */
// First, any manual functions (should be exposed in dndv_sync.h)


/*  -- Automatic PC Sync Actions (in order) --  */
bool addPotentialGM(ContactAddress* mad){
    createOrUpdateContact(*mad);
    printf("New GM: %s, %s",mad->info.p_name,mad->info.c_name);
    return true;
} 

/*  Finally, the event receiver to answer the requests (that the player receives) */
void sync_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    macAndData_s* da = (macAndData_s*) event_data;
    switch(id){
        case EVENT_GM_INFO:
            addPotentialGM((ContactAddress*) da);
            addAsDM_test((ContactAddress*) da);
            requestPlayer1_test();  //TODO: Remove this and add it to the GUI
            break;
        case EVENT_KEYDATA_RCV:     //TODO: Add a device event KEYDATA_UPDATE for when the updating here finishes?
            updateMyPlayer(*(Player*) da->data);    //Cast to Player pointer, then dereference. Creates a copy on the stack.
            requestPC1_test();
            break;
        case EVENT_PCDATA_RCV:
            updateMyPC(*(PC*) da->data);
            printf("Got the data!");
            break;
        case EVENT_AWAKE_BROADCAST_RCV:
            break;
        default:
            printf("Someone's syncing out there\n");
    }
}



/*              =- GM Sync Actions -=           */

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
    Player retrieved = db_read_player((Key) *(da->data));
        //TODO: SEND IF RETRIEVED CORRECTLY, OTHERWISE (TODO) RETURN SOMETHING ELSE
    dndv_send(da->mac, EventBaseP2Num(&SYNC_BASE), EVENT_KEYDATA_RCV, &retrieved, sizeof(Player));
    return retrieved;
}

PC retrieveAndSendPC(macAndData_s* da){
    PC retrieved = db_read_pc((Key) *(da->data));
        //TODO: SEND IF RETRIEVED CORRECTLY, OTHERWISE (TODO) RETURN SOMETHING ELSE
    dndv_send(da->mac, EventBaseP2Num(&SYNC_BASE), EVENT_KEYDATA_RCV, &retrieved, sizeof(PC));
    return retrieved;
}



void gm_sync_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    macAndData_s* da = (macAndData_s*) event_data;
    printf("Heard Syncing...\n");
    switch(id){
        case EVENT_AWAKE_BROADCAST_RCV:
            ;   //This is required because C doesn't allow for a symbol like "bool" right after the case statement
            bool newlyAdded = addIfNewPeer(da->mac);
            if(!newlyAdded){ESP_LOGI(TAG, "I know this device, replying.\n");}
            GM_DM_Data(da->mac);
            break;

        //case EVENT_SYNC_REQ:         //When a player selects the GM's campaign, let the GM know so the player isn't left behind? Not implemented yet (nor needed, likely)

        case EVENT_KEYDATA_REQ:
            //Remove "_test" for the actual function
            retrieveAndSendKey_test(da);
            //TODO: Check to see if this device is already in the list. If so, delete that old copy!
            break;

        case EVENT_PC_REQ:
            //Remove "_test" for the actual function
            retrieveAndSendPC_test(da);
            //TODO: Check to see if this device is already in the list. If so, delete that old copy!
            break;

        case EVENT_PC_JOINED:
            //TODO: I doubt this works, so test
            //ContactAddress ca = {da->mac, da->data};
            //createContact(ca);

            //Just like for the player side, we can do the following cast
            createContact(*(ContactAddress*) da);
        
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
    const uint8_t broadcast_mac[] = BROADCAST_MAC;
    return dndv_send_blank(broadcast_mac, N_SYNC_BASE, EVENT_AWAKE_BROADCAST_RCV);

    //Could wait for callback here to call more times instead of returning immediately
}

void sync_init(void){
        esp_event_handler_instance_register_with(dndv_event_h, SYNC_BASE, ESP_EVENT_ANY_ID, sync_rcv, NULL,NULL);
}