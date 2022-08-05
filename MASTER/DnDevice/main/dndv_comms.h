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

void comms_init(void);

void sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);

typedef struct{     //Change inside away from uint8_t and pack the struct
    uint8_t ID;
    uint8_t data[2]; //Change to a pointer
} sending_data;

/*      Sending Functions      */


esp_err_t send_exampleAwake(void);













/*      Receiving Functions     */

esp_event_loop_handle_t rcv_event_handle;

void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len);
//Note: rcv, not recv








//#endif