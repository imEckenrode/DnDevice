//#include "lvgl.h"
#include "lvgl/lvgl.h"
#include "lvgl_helpers.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: Not entirely sure how many of these I need...
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#include "ui/ui.h"
//#include "D:/ime/GitHub/DnDevice/DnDevice/MASTER/DnDevice/main/ui/ui.h"

#define TAG "ui"
#define LV_TICK_PERIOD_MS 1

static void lv_tick_task(void *arg);
static void guiTask(void *pvParameter);

/**********************
 *   APPLICATION MAIN
 **********************/

//# define LV_HOR_RES_MAX 320
//# define LV_VER_RES_MAX 240
//# define SPI_HOST_MAX 3
//#define DISP_BUF_SIZE (320 * 40)

void  ui_stuff_init() {

    xTaskCreatePinnedToCore(guiTask, "gui", 4096*2, NULL, 0, NULL, 1);
}

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;

static void guiTask(void *pvParameter) {

    (void) pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();
    lvgl_driver_init();

//TODO: Figure out where these are actually defined
//This is done for buf1, but should not be needed otherwise?
#define LV_HOR_RES LV_HOR_RES_MAX
#define LV_VER_RES LV_VER_RES_MAX

    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf1[LV_HOR_RES * 40];        //This is 40 in correspondence with the ili driver
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, LV_HOR_RES * 40);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LV_HOR_RES;
    disp_drv.ver_res = LV_VER_RES;
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);


    /* Register an input device when enabled on the menuconfig */
#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.read_cb = touch_driver_read;
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    lv_indev_drv_register(&indev_drv);
#endif

    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    /* Create the application */
    ui_init();

    while (1) {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));
        //vTaskDelay(10);    //TODO: CHANGE THIS TO THE CORRECT DELAY

        /* Try to take the semaphore, call lvgl related function on success */
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
            lv_task_handler();
            xSemaphoreGive(xGuiSemaphore);
       }
    }

    /* A task should NEVER return */
    //free(buf1);
    vTaskDelete(NULL);
}

static void lv_tick_task(void *arg) {
    (void) arg;
    lv_tick_inc(LV_TICK_PERIOD_MS);
}