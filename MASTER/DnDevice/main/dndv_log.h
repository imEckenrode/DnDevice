#pragma once

/*      dndv_log

    This code registers to the dndv_comms event loop.

    When data is received over ESP-NOW, this code runs and prints out the received data in human-readable format
        This also serves as an example/test for the Event Loop Library (the library that implements the event loops)
*/



void log_init(void);
