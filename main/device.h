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


// This is the enumeration for the profile pictures
// Since the PFPs are a display issue, the pointers are stored in screen_control
#define DNDV_PFPS_COUNT 13
//and their related names
enum DNDV_PFPS{
    DNDV_PFP_ARTIFICER,
    DNDV_PFP_BARBARIAN,
    DNDV_PFP_BARD,
    DNDV_PFP_CLERIC,
    DNDV_PFP_DRUID,
    DNDV_PFP_FIGHTER,
    DNDV_PFP_MONK,
    DNDV_PFP_PALADIN,
    DNDV_PFP_RANGER,
    DNDV_PFP_ROGUE,
    DNDV_PFP_SORCERER,
    DNDV_PFP_WARLOCK,
    DNDV_PFP_WIZARD
};

// This is the enumeration for the conditions
// Tracking the locations on the screen is done in screen_control
#define DNDV_CONDITIONS_COUNT 20

enum DNDV_CONDITIONS{
    DNDV_COND_BLINDED,
    DNDV_COND_CHARMED,
    DNDV_COND_DEAFENED,
    DNDV_COND_DISARMED,
    DNDV_COND_EXHAUSTION,
    DNDV_COND_FRIGHTENED,
    DNDV_COND_GRAPPLED,
    DNDV_COND_HIDDEN,
    DNDV_COND_INCAPACITATED,
    DNDV_COND_INVISIBLE,
    DNDV_COND_OBSCURED,
    DNDV_COND_PARALYZED,
    DNDV_COND_PETRIFIED,
    DNDV_COND_POISONED,
    DNDV_COND_PRONE,
    DNDV_COND_RAGING,
    DNDV_COND_RESTRAINED,
    DNDV_COND_SURPRISED,
    DNDV_COND_STUNNED,
    DNDV_COND_UNCONSCIOUS
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

ESP_EVENT_DECLARE_BASE(UI_UPDATE_BASE);
enum UI_UPDATE_B_ID{
    UI_SCREEN_REFRESH
};