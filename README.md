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

ui_events.h is copied out and pasted into screen_actions.h. As such, ui.h includes that instead of ui_events.h