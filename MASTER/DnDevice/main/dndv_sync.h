#pragma once // Is this needed? Is anything including this beside init.c?
#include "dndv_comms.h"
#include "dndv_db.h"

/*
    Before the game can start, the devices need to sync up.

    There are two sides to this: the GM syncing, and the players syncing.

    This includes the following:
    
    Upon wakeup, broadcast so GMs can send you the data
    Upon becoming a GM, let everyone know so they can join your game
    Players asking for player/PC data
    
    And finally, starting the game is contained in here.

    Since this is a very self-contained file, there's not much exposed out here
*/

//      EVENT BASE DECLARATION
ESP_EVENT_DECLARE_BASE(SYNC_BASE);
ESP_EVENT_DECLARE_BASE(GM_SYNC_BASE);

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
    struct __attribute__((__packed__)) pcList{
        Key key;
        Name name;
    } pcList[8];           //Currently 8 since Key+Player < 40
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
    EVENT_PC_REQ       //Return the date for the requested player character

    //EVENT_PC_JOINED,            //A PC has joined the adventure!
    //EVENT_PC_READY
};

//KeyData returns player info if the key is for a player       //TODO: Return NPC data as well
struct __attribute__((__packed__)) keydata_req_s{
    Key key;
};



//  When a device wakes up, broadcast as such
esp_err_t dndv_send_onAwake(void);

//TODO: do this automatically
void update_comms_sync_mode(bool isGM);

void sync_init();