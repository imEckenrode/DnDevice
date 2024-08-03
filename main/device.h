#pragma once


#include <stdbool.h>
#include <string.h> //for base comparison
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl/lvgl.h"
//We need esp_event out here so we can have the global variable
/*

This contains all device variables and manipulations of said variables

This includes key data, player name, settings, etc.

*/

struct __attribute__((__packed__)) device {
    char name[8];
    char pc_name[20];
} my;


#define DNDV_PFP_COUNT 13
//And here's the array for profile pictures (initialized in screen_control.c)
extern lv_img_dsc_t *pfpArray[DNDV_PFP_COUNT]; //To leave all UI to 

//and their related names
enum DNDV_PFPS{
    DNDV_PFP_artificer,
    DNDV_PFP_barbarian,
    DNDV_PFP_bard,
    DNDV_PFP_cleric,
    DNDV_PFP_druid,
    DNDV_PFP_fighter,
    DNDV_PFP_monk,
    DNDV_PFP_paladin,
    DNDV_PFP_ranger,
    DNDV_PFP_rogue,
    DNDV_PFP_sorcerer,
    DNDV_PFP_warlock,
    DNDV_PFP_wizard
};

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