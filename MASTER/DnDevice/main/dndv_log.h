#pragma once

#include "dndv_internals.h"
#include "dndv_comms.h"
#include "esp_event.h"
#include "esp_log.h"
/*      dndv_log

    This code registers to the dndv_comms event loop.

    When data is received over ESP-NOW, this code runs and prints out the received data in human-readable format
        This also serves as an example/test for the Event Loop Library (the library that implements the event loops)
*/


/*  Initialize Logs */
void log_init(void);
