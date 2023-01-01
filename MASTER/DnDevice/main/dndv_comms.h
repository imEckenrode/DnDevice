#pragma once
/*# ifndef dndv_comms.h
# define dndv_comms.h */
//#include "dndv_data.h" //Automatically included through dndv_internals, but if dndv_internals isn't used, use this comment
#include "dndv_internals.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_err.h"

//Can use this in place of any calls for the GM MAC
#define GM_MAC current.gmInfo.MAC

/*    All communcation (over ESP-NOW) can be found in here, dndv_comms

  SENDING

    Call dndv_send() to send the data to the specified player (decoded into the proper MAC address)

  RECEIVING

    To receive data, register to the event loop by calling esp_event_handler_register_with() in your desired file.
    
    Then use the structures in this file to decipher the type of data received based on the first byte received
  

 The same format remains:
    Title
    Struct
    Comment about what the function will do
    Function
*/


/* --- Definitions of Sync Events ---

  As described by dndv_data, the sync events are here in dndv_comms.
  For all communication events in any file, see CreatingEvents.txt for compatibility with the dndv Events

  For example, see dndv_sync */


// - Event Base Array Creation and Definition -
//Declare the Event Base Array (done in dndv_comms)
#define DNDV_EBA_DECLARE() extern esp_event_base_t* EVENT_BASE_ARRAY[]; extern Num EVENT_BASE_ARRAY_SIZE //The second semicolon is added by the instance(see below)    

//Define the Event Base Array (done in init.c)
//Add all the Event Bases to be used with dndv_comms here
#define DNDV_EBA_DEFINE(...)esp_event_base_t* EVENT_BASE_ARRAY[] = {__VA_ARGS__}; Num EVENT_BASE_ARRAY_SIZE = sizeof(EVENT_BASE_ARRAY)/sizeof(esp_event_base_t*)

DNDV_EBA_DECLARE(); //see init.c for the definition


/* BASE CONVERSION
    ESP-NOW defines bases as a character array. These methods convert back and forth to our custom numbering */
//To convert from the ELL Base to our dndv_comms one-byte number
Num EventBaseP2Num(esp_event_base_t *baseAddress);
//To convert back to the ELL Base from our dndv_comms one-byte number
esp_event_base_t Num2EventBase(Num num);


/*  -- Initialize ESP-NOW communications -- */
void comms_init(void);


/*     - Data Structures -    TODO: Update this
    Define whatever set you want for your data to send, then cast it back to that on data receive based on the ID
      This ID can be found by casting to the sending_data structure below

    The ID should only be assigned through this library.

    It is recommended to use __attribute__((__packed__)) to send as much data as possible, as this guarantees that no padding bytes are added.
      This is also REQUIRED to maintain alignment if a communication structure is used in multiple places.
*/


/*     - Sending Functions -     */


// Send the data, events included!
esp_err_t dndv_send_raw(macAddr mac, void* data, size_t size);

// Send the data! This is the preferred method
esp_err_t dndv_send(macAddr mac, Num eventBaseNum, Num eventIdNum, void* data, size_t size);

//This calls dndv_send with 0 for data and size
esp_err_t dndv_send_blank(macAddr mac, Num eventBaseNum, Num eventIdNum);



//  For testing, broadcast a ping
void dndv_send_ping(void);


//  When a device wakes up, broadcast as such
esp_err_t dndv_send_onAwake(void);

/*    -- ESP-NOW Sending Functions --     */

/* Callback to when ESP-NOW sends successfully
    
    FOR BROADCAST:
      status is 0 (success) if the broadcast sends [does NOT tell if received]
      status is 1 if an internal error occurs

    For everything else:
      status is 0 if the target device receives the data successfully
      status is 1 on an error
    
    ESP-NOW resends multiple times by default to maximize successful sends, but a callback TODO should be implemented
     */
void sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);




/*     - Receiving Functions -    */

/*  Callback to receiving ESP-NOW data
    Simply pushes received data to the dndv_event_h loop  */
void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len);
//Note: rcv, not recv





//#endif