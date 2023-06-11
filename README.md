# DnDevice
 For all things involving the DnDevice project

NOTE: A manual patch is needed for lvgl_esp32_drivers:

Add the 3 following lines under "DEFINES":

\# define LV_HOR_RES_MAX 320

\# define LV_VER_RES_MAX 240

\# define SPI_HOST_MAX 3


May need idf.py menuconfig to set up local project, will look into defaulting through lv_conf.h
