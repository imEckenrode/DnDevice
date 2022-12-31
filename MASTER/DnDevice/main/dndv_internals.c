#include "dndv_internals.h"

void device_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data);

//Initialize all global variables to the correct values
void globals_init(){
    current.isDM = false;
    //current.info = {"",""}      //TODO: Set name as MAC (through esp_read_mac()?)
                                   //TODO: Free this when the device joins the campaign
    current.contacts = (struct ContactAddressBook*) malloc(INITIAL_MAX_PLAYER_COUNT*sizeof(ContactAddress) + 2);    //Add 2 for the short at the start of contactAddress
    current.contacts->maxContacts=INITIAL_MAX_PLAYER_COUNT;

    esp_event_handler_instance_register_with(dndv_event_h, DEVICE_BASE, ESP_EVENT_ANY_ID, device_rcv, NULL,NULL);
}

/*     -- Local Functions (for use in this file, dndv_internals.c) --   */

// Broadcast data by sending to the event loop
static bool comms_broadcastData(void* event_data, size_t event_data_size){
    esp_event_post_to(dndv_event_h, COMMS_BASE, EVENT_SEND_BROADCAST, event_data, event_data_size, 0); 
    return true;
}





/*     --- CRUD Functions ---     */

bool isDM(){
    return current.isDM;
}

bool isPlayer(){
    return !isDM();
}

bool updateDMStatus(bool isDM){
    current.isDM = isDM;
    return true;
}

/*macAddr getDmMAC() {if(isDM()){printf("NO DM MAC FOR YOU!");return NULL;} return current.dmInfo.MAC;}*/

Key getMyKey(){return current.myKey;}
Player getMyPlayer(){return current.my->Player;}
PC getMyPC(){return current.my->PC;}

bool updateMyKey(Key newKey){current.myKey = newKey; return true;}
bool updateMyPlayer(Player player){current.my->Player = player; return true;}   //Change implementation as needed/updated
bool updateMyPC(PC pc){current.my->PC = pc; strcpy(current.my->PC.name, pc.name); return true;}                       //This gives a single area to do so

bool updateMyName(Name newName){strcpy(( (isDM()) ? current.dmInfo.dmName : current.my->Player.name),newName);   return true;}
bool updateMyCName(Name newName){strcpy(( (isDM()) ? current.dmInfo.campaignName : current.my->PC.name), newName); return true;}   //This does not allow for longNames, so if that is desired, check current string allocation sizes first or risk a data overflow

ContactInfo getMyContactInfo(){
    if(isDM()){
        ContactInfo myInfo = {current.myKey, current.dmInfo.dmName, current.dmInfo.campaignName};
        return myInfo;
    }
    ContactInfo myInfo = {current.myKey, current.my->Player.name, current.my->PC.name};
    return myInfo;
}

bool updateMyContactInfo(ContactInfo info){
    updateMyKey(info.key);
    updateMyName(info.p_name);
    updateMyCName(info.c_name);
}


/*  -- Contact Data System --    */

short sizeOfContactBook(){
    return (current.contacts->maxContacts)*sizeof(ContactAddress);
}


bool contactExistWithMAC(macAddr mac){
    for(short i=0;i < current.contacts->maxContacts;i++){
        if (strcmp(mac, current.contacts->contact[i].MAC) == 0){
            return true;            //No reason this shouldn't work according to testing in c
        }
    }
    return false;}

//-1 is returned if non-existent
short indexOfContactWithMAC(macAddr mac){
    for(short i=0;i < current.contacts->maxContacts;i++){
        if (strcmp(mac, current.contacts->contact[i].MAC) == 0){
            return i;            //No reason this shouldn't work according to testing in c
        }
    }
    return -1;
}

//Hidden method only used in dndv_internals to reduce redundant searching and easily assign values to the contacts book
bool updateContactAtIndex(ContactAddress cAddr, short index){
    current.contacts->contact[index] = cAddr;
    return true;
}

//Find the first spot without a MAC address and fill it in.
bool createContact(ContactAddress cAddr){
    short index = indexOfContactWithMAC("");
        if(index == -1){
            printf("NO ROOM FOR %d: %s.",cAddr.info.key, cAddr.info.p_name);
            return false;                               //TODO: Allocate if no more room!
        }
        return updateContactAtIndex(cAddr, index);
}

ContactAddress readContact(macAddr mac){
    return current.contacts->contact[indexOfContactWithMAC(mac)];
}


bool createOrUpdateContact(ContactAddress cAddr){
    short index = indexOfContactWithMAC(cAddr.MAC);
    if(index == -1){
        return createContact(cAddr);
    }
    return updateContactAtIndex(cAddr, index);
}

bool updateContact(ContactAddress cAddr){
    return updateContactAtIndex(cAddr, indexOfContactWithMAC(cAddr.MAC));
}

ContactAddress emptyContactAddress(){
    ContactAddress empty = {"",{0,"",""}};
    return empty;
}

bool deleteContact(macAddr mac){
    short index = indexOfContactWithMAC(mac);
    if(index == -1){
        return false;
    }
    updateContactAtIndex(emptyContactAddress(), index);
    return true;
}

ContactAddress readContactByKey(Key key){
    for(short i=0;i < current.contacts->maxContacts;i++){
        if (key == current.contacts->contact[i].info.key){
            return current.contacts->contact[i];
        }
    }
    return emptyContactAddress();
}



/*          --- Runtime Data System ---
        This is the system that tracks all players/NPCs

        TODO: Expand this
*/



/*          --- Data Retrieval System ---
        Here is the system for retrieving character data    (This is for the DMs)
        TODO: Move this to the SD card while still having this option
*/








/*  --- HOME OF DEVICE_BASE HANDLING :
This function receives all DEVICE_BASEd events and processes them accordingly, possibly redirecting them to other functions.
*/
void device_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        case EVENT_DM_KEYIN:
            testDMInit();       //Temporary (TODO)
            break;

        case EVENT_CAMPAIGN_SELECT:
            break;
        default:
            ESP_LOGE("DnDevice Internal", "Did not recognize the internal event.");
    }

}


/*      - DM EXCLUSIVE FUNCTIONS -
    Here are the functions exclusive to the DM.

    To keep this exclusivity, DM_Activate activates the handle for DM only events
*/



//The handler for any DM exclusive data (DM_DEVICE_BASE)
void DM_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        case EVENT_DM_ACTIVATE:
            esp_event_post_to(dndv_event_h, COMMS_BASE, EVENT_DM_ACTIVATE, NULL, 0, 0);
            break;
            /*;
            struct dm_info_s to_send = {
                .event = {N_SYNC_BASE,EVENT_DM_INFO},
                .info =  getMyContactInfo()}; //current.info};

            comms_broadcastData((void*)&to_send, sizeof(to_send));
                    //esp_event_post_to(dndv_event_h, COMMS_BASE, EVENT_SEND_BROADCAST, (void*)&to_send, sizeof(to_send), 0); 
            printf("Sent, right?\n%s\n",to_send.info.c_name);

            */
        default:
            ESP_LOGE("DM Internal", "Did not recognize the internal event.");
    }
}



/* --------TODO: Below this point should be refactored above. This should no longer be needed soon. */


//  Initialize all the DM functions, handles, and variables.
//      p_name = DM Name
//      c_name = Campaign Name
void DM_Activate(void){
    //int size = 22;
    //arr to_send = {22, malloc()
    esp_event_handler_instance_register_with(dndv_event_h, DM_DEVICE_BASE, ESP_EVENT_ANY_ID, DM_rcv, NULL,NULL);
    //esp_event_handler_instance_unregister_with(dndv_event_h, DEVICE_BASE, ESP_EVENT_ANY_ID, device_rcv);      
                //TODO: UNREGISTERING this means that you cannot deactivate DM mode without a reset (which is fine)
                    //(If this is entirely separate from the DM_rcv, the unregister comment can work)
            //Syncing is done by dndv_comms
    //Player List
    //PlayerToMAC List
    //NPC List  (Same layout as players, plus attack bonus?)

    esp_event_post_to(dndv_event_h, DM_DEVICE_BASE, EVENT_DM_ACTIVATE, NULL, 0, 0);
     //No need to divide size of a uint8 array, because sizeof(uint8) = 1
}



//And finally, tests

void testPCInit(void){
    current.isDM = false;
    updateMyKey(1);
    Player examplePlayer = {"Bob","Bob Billy Joe",false,false};
    updateMyPlayer(examplePlayer);
    PC examplePC = {"Wizz","PowerWizard",3,16,13};
    updateMyPC(examplePC);

    printf("Test Player Initialized\n");
}

void testDMInit(void){
    current.isDM = true;      //TODO: Could have a semaphore something or other on the global level
    updateMyKey(1);
    updateMyPlayerName("MeDM");
    updateMyPCName("AwesomeTitleHere");

    DM_Activate();
    printf("DM Mode Activated (Test DM Initialized)\n");
}