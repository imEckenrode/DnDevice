#pragma once

#include <stdbool.h>
/*     -  -  -     The UI      -  -  -      
    This is where the UI is initiated to its own core.
    This is also what refreshes the UI

    NOTE: This is very high-level, 
     since the UI itself uses lower libraries
*/

void ui_stuff_init(void);

void ui_refresh(bool animating);