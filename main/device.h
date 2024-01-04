#pragma once


#include <stdbool.h>
#include <string.h> //for base comparison
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_err.h"
#include "esp_log.h"
//We need esp_event out here so we can have the global variable
/*

This contains all device variables and manipulations of said variables

This includes key data, player name, settings, etc.

*/

struct __attribute__((__packed__)) device {
    char name[8];
    char pc_name[20];
} my;


/*      -  NVS  - 
Initialize the non-volatile storage library to persist data 
    Required for: ESP-NOW   */
void nvs_init(void);

//Device event handler
esp_event_loop_handle_t dndv_event_h;

//Initialize the event loop library
void eventLoop_init(void);

/* Here are the different events possible: */

ESP_EVENT_DECLARE_BASE(DATA_CHANGED_BASE);
enum DATA_CHANGED_B_ID{
    PC_DATA_CHANGED
};