#pragma once
/*# ifndef dndv_comms.h
# define dndv_comms.h*/

#include "dndv_internals.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_err.h"
/*    All communcation (over ESP-NOW) can be found in here, dndv_comms

  SENDING

    Simply call dndv_send() to send the data to the specified player (decoded into the proper MAC address)

  RECEIVING

    To receive data, register to the event loop by calling esp_event_handler_register_with() in your desired file.
    
    Then use the structures in this file to decipher the type of data received based on the first byte received
  

 The same format remains:
    Title
    Struct
    Comment about what the function will do
    Function
*/


/*  Initialize ESP-NOW communications (This is located last) */
void comms_init(void);


/*     - Data Structures - 
    Define whatever set you want for your data to send, then cast it back to that on data receive based on the ID
      This ID can be found by casting to the sending_data structure below

    The ID should only be assigned through this library.

    It is recommended to use __attribute__((__packed__)) to send as much data as possible, as this guarantees that no padding bytes are added.
      This is also REQUIRED to maintain alignment if a communication structure is used in multiple places.
*/


/*     - Sending Functions -     */


// Send the data!
esp_err_t dndv_send(macAddr mac, raw_data data);


//  When a device wakes up, broadcast as such
esp_err_t dndv_send_onAwake(void);




/* Callback to when ESP-NOW sends successfully
    
    FOR BROADCAST:
      status is 0 (success) if the broadcast sends [does NOT tell if received]
      status is 1 if an internal error occurs

    For everything else:
      status is 0 if the target device receives the data successfully
      status is 1 on an error
    
    ESP-NOW resends multiple times by default to maximize successful sends, but a callback TODO needs implemented
     */
void sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);






/*     - Receiving Functions -    */

/*  Callback to receiving ESP-NOW data
    Simply pushes received data to the dndv_event_h loop  */
void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len);
//Note: rcv, not recv








//#endif