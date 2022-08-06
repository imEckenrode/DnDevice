#pragma once
/*# ifndef dndv_comms.h
# define dndv_comms.h*/

//#include "dndv_internals.h"
#include "esp_now.h"

/*
 All communcation (over ESP-NOW) can be found in here.

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

/*  Initialize ESP-NOW communications */
void comms_init(void);

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

/*  Test Data Structure (TODO: Replace) */
typedef struct{     //Change inside away from uint8_t and pack the struct
    uint8_t ID;
    uint8_t data[2]; //Change to a pointer
} sending_data;

/*      Sending Functions      */

//  Current Test Data
esp_err_t send_exampleAwake(void);













/*      Receiving Functions     */

/*  
    This is the handle that runs when ESP-NOW receives data

    To receive data, call esp_event_handler_instance_register_with(rcv_event_handle, ESP_EVENT_ANY_BASE, ESP_EVENT_ANY_ID,rcvToLog,NULL,NULL);
*/
esp_event_loop_handle_t rcv_event_handle;

/*  Callback to receiving ESP-NOW data
    Simply pushes received data to the rcv_event_handle loop  */
void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len);
//Note: rcv, not recv








//#endif