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

    Each ID has its own function, which then call other functions (forward declared)


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

void rcv_cb(const uint8_t *mac_addr, const uint8_t *data, int len);
//Note: rcv, not recv








//#endif