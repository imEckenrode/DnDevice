## STAGE 1: Personal DnDevice (Offline Mode)

This device verson will allow a player to track his/her own HP, AC, and status conditions.

Unlike the full DnDevice, this does not interface with other DnDevices at all.
Player data is stored locally on an SD card available to this personal DnDevice.

### DnDevice General Tips:

NOTE: A manual patch is needed for lvgl_esp32_drivers:

Add the 3 following lines directly under "DEFINES" in lvgl_helpers.h:

\# define LV_HOR_RES_MAX 320

\# define LV_VER_RES_MAX 240

\# define SPI_HOST_MAX 3

(get rid of the slashes if copying from markdown text)

May need idf.py menuconfig to set up local project, will look into defaulting through lv_conf.h


### For the ui Folder

ui_events.h is copied out and pasted into screen_actions.h (then update the related screen_actions.c). As such, ui.h includes screen_actions.h instead of ui_events.h. 

Can safely delete ui_events.c because those show all exported functions of which we should have none.

ui.c is modified with custom functions (at least for now), so make sure to comment those with "custom" and pull those over when updating the UI