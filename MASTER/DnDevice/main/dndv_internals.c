#include "dndv_internals.h"


#define EMPTY_MAC {0x0,0x0,0x0,0x0,0x0,0x0}
macAddr empty_mac = EMPTY_MAC;


void device_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data);

//Initialize all global variables to the correct values
void globals_init(){
    current.isGM = false;
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

bool isGM(){
    return current.isGM;
}

bool isPlayer(){
    return !isGM();
}

bool updateGMStatus(bool isGM){
    current.isGM = isGM;
    return true;
}

/*macAddr getGmMAC() {if(isGM()){printf("NO GM MAC FOR YOU!");return NULL;} return current.gmInfo.MAC;}*/

Key getMyKey(){return current.myKey;}
Player getMyPlayer(){return current.my->Player;}
PC getMyPC(){return current.my->PC;}

bool updateMyKey(Key newKey){current.myKey = newKey; return true;}
bool updateMyPlayer(Player* player){current.my->Player = *player; return true;}   //Change implementation as needed/updated
bool updateMyPC(PC* pc){current.my->PC = *pc; strcpy(current.my->PC.name, pc->name); return true;}                       //This gives a single area to do so

bool updateMyName(Name newName){strcpy(( (isGM()) ? current.gmInfo.gmName : current.my->Player.name),newName);   return true;}
bool updateMyCName(Name newName){strcpy(( (isGM()) ? current.gmInfo.campaignName : current.my->PC.name), newName); return true;}   //This does not allow for longNames, so if that is desired, check current string allocation sizes first or risk a data overflow

//Here's a helper to create a new ContactInfo
ContactInfo joinContactInfoTogether(Key key, Name p_name, Name c_name){
    ContactInfo toReturn;
    toReturn.key = key;
    strcpy(toReturn.p_name, p_name);
    strcpy(toReturn.c_name, c_name);
    return toReturn;
}
ContactInfo getMyContactInfo(){
    if(isGM()){
        return joinContactInfoTogether(current.myKey, current.gmInfo.gmName, current.gmInfo.campaignName);
    }
    return joinContactInfoTogether(current.myKey, current.my->Player.name, current.my->PC.name);
}

bool updateMyContactInfo(ContactInfo info){
    updateMyKey(info.key);
    updateMyName(info.p_name);
    updateMyCName(info.c_name);
    return true;
}


/*  -- Contact Data System --    */

short sizeOfContactBook(){
    return (current.contacts->maxContacts)*sizeof(ContactAddress);
}


bool contactExistWithMAC(macAddr mac){
    for(short i=0;i < current.contacts->maxContacts;i++){
        if (memcmp(mac, current.contacts->contact[i].MAC, MAC_ADDR_SIZE) == 0){
            return true;            //No reason this shouldn't work according to testing in c
        }
    }
    return false;}

//-1 is returned if non-existent
short indexOfContactWithMAC(macAddr mac){
    for(short i=0;i < current.contacts->maxContacts;i++){
        if (memcmp(mac, current.contacts->contact[i].MAC, MAC_ADDR_SIZE) == 0){
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
    short index = indexOfContactWithMAC(empty_mac);          //TODO: Intialize the entire thing to 0s first for this to work
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
        Here is the system for retrieving character data    (This is for the GMs)
        TODO: Move this to the SD card while still having this option
*/








/*  --- HOME OF DEVICE_BASE HANDLING :
This function receives all DEVICE_BASEd events and processes them accordingly, possibly redirecting them to other functions.
*/
void device_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        case EVENT_GM_KEYIN:
            testGMInit();       //Temporary (TODO)
            break;

        case EVENT_CAMPAIGN_SELECT:
            break;
        default:
            ESP_LOGE("DnDevice Internal", "Did not recognize the internal event.");
    }

}


/*      - GM EXCLUSIVE FUNCTIONS -
    Here are the functions exclusive to the GM.

    To keep this exclusivity, GM_Activate activates the handle for GM only events
*/



//The handler for any GM exclusive data (GM_DEVICE_BASE)
void GM_rcv(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    switch(id){
        case EVENT_GM_ACTIVATE:
            //Do I update the GM Info here???
            esp_event_post_to(dndv_event_h, COMMS_BASE, EVENT_SEND_BROADCAST, &current.gmInfo, 0, 0);
            break;
            /*;
            struct gm_info_s to_send = {
                .event = {N_SYNC_BASE,EVENT_GM_INFO},
                .info =  getMyContactInfo()}; //current.info};

            comms_broadcastData((void*)&to_send, sizeof(to_send));
                    //esp_event_post_to(dndv_event_h, COMMS_BASE, EVENT_SEND_BROADCAST, (void*)&to_send, sizeof(to_send), 0); 
            printf("Sent, right?\n%s\n",to_send.info.c_name);

            */
        default:
            ESP_LOGE("GM Internal", "Did not recognize the internal event.");
    }
}



/* --------TODO: Below this point should be refactored above. This should no longer be needed soon. */


//  Initialize all the GM functions, handles, and variables.
//      p_name = GM Name
//      c_name = Campaign Name
void GM_Activate(void){
    //int size = 22;
    //arr to_send = {22, malloc()
    esp_event_handler_instance_register_with(dndv_event_h, GM_DEVICE_BASE, ESP_EVENT_ANY_ID, GM_rcv, NULL,NULL);
    //esp_event_handler_instance_unregister_with(dndv_event_h, DEVICE_BASE, ESP_EVENT_ANY_ID, device_rcv);      
                //TODO: UNREGISTERING this means that you cannot deactivate GM mode without a reset (which is fine)
                    //(If this is entirely separate from the GM_rcv, the unregister comment can work)
            //Syncing is done by dndv_comms
    //Player List
    //PlayerToMAC List
    //NPC List  (Same layout as players, plus attack bonus?)

    esp_event_post_to(dndv_event_h, GM_DEVICE_BASE, EVENT_GM_ACTIVATE, NULL, 0, 0);     //Post to the newly-GM device and handle there
     //No need to divide size of a uint8 array, because sizeof(uint8) = 1
}



//And finally, tests

void testPCInit(void){
    current.isGM = false;
    updateMyKey(1);
    Player examplePlayer = {"Bob","Bob Billy Joe",false,false};
    updateMyPlayer(&examplePlayer);
    PC examplePC = {"Wizz","PowerWizard",3,16,13};
    updateMyPC(&examplePC);

    printf("Test Player Initialized\n");
}

void testGMInit(void){
    current.isGM = true;      //TODO: Could have a semaphore something or other on the global level
    updateMyKey(1);
    updateMyName("MeGM");
    updateMyCName("AwesomeTitleHere");

    GM_Activate();
    printf("GM Mode Activated (Test GM Initialized)\n");
}