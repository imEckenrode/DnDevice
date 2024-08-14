#pragma once

#include <stdbool.h>
#include "device.h"

/*     -  -  -     The UI      -  -  -      
    This is where the UI is initiated to its own core.
    This is also what refreshes the UI

    NOTE: This is very high-level, 
     since the UI itself uses lower libraries
*/

// This is the array with all the profile picture pointers
extern const lv_img_dsc_t *pfpArray[DNDV_PFPS_COUNT];
// This is the position to condition mapping
extern uint8_t pos2Cond[DNDV_CONDITIONS_COUNT];      //NOTE: This is a uint8_t to save memory on data transfer, but the real type is enum DNDV_CONDITIONS
// and this is the condition to image mapping
extern const lv_img_dsc_t *condImgArray[DNDV_CONDITIONS_COUNT];
#define DNDV_UI_CONDITIONS_PAGE_COUNT 4
extern uint8_t condPage;

void dndv_set_condPage(bool adjusting, int8_t pagesToTurn);
void ui_PP_update_conditions();
void ui_PPP_update_conditions();
void ui_stuff_init(void);

void ui_refresh(bool animating);