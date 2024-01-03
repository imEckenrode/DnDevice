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


/*      -  NVS  - 
Initialize the non-volatile storage library to persist data 
    Required for: ESP-NOW   */
void nvs_init(void);

//Device event handler
esp_event_loop_handle_t dndv_event_h;

//Initialize the event loop library
void eventLoop_init(void);