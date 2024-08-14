#include "screen_control.h"

#include "lvgl/lvgl.h"
#include "lvgl_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#include "esp_event.h"
#include "data_pc.h"

//And I need to include ui.h so we can initialize the uis
#include "ui/ui.h"

//#include "D:/ime/GitHub/DnDevice/DnDevice/MASTER/DnDevice/main/ui/ui.h"

#define TAG "UI"

#define LV_TICK_PERIOD_MS 1

static void lv_tick_task(void *arg);
static void guiTask(void *pvParameter);

//# define LV_HOR_RES_MAX 320
//# define LV_VER_RES_MAX 240
//# define SPI_HOST_MAX 3
//#define DISP_BUF_SIZE (320 * 40)

SemaphoreHandle_t xGuiSemaphore;

/*                      *
 *  IMAGE DATA ARRAYS   *
 *                      */

// This is the array with all the profile picture pointers
const lv_img_dsc_t *pfpArray[DNDV_PFPS_COUNT];

// This is the position to condition mapping
enum DNDV_CONDITIONS pos2Cond[DNDV_CONDITIONS_COUNT];   //NOTE: Making this a uint8_t may save memory
// and this is the condition to image mapping
const lv_img_dsc_t *condImgArray[DNDV_CONDITIONS_COUNT];
uint8_t condPage; // This is the condition "page" we are on (0-indexed)
//See dndv_set_condPage below

/*                      *
 *  REFRESHING THE UI   *
 *                      */

void dndv_update_pfp(lv_obj_t *image_holder, enum DNDV_PFPS selection){
    lv_img_set_src(image_holder, pfpArray[selection]);
}


void ui_PP_update_conditions(){    // This could also be done in a loop if we set up the objects themselves in a loop
    uint8_t pos = condPage*(DNDV_CONDITIONS_COUNT/DNDV_UI_CONDITIONS_PAGE_COUNT);
    //WARNING/TODO: This does not catch out of bounds (we could simply modulo by DNDV_CONDITIONS_COUNT) and instead assumes the constant above is 5 as designed

    _ui_state_modify(ui_PP_cond0, LV_STATE_CHECKED, 1&hasCondition(pos2Cond[pos])); //If condition is on, we remove the Checked state via state 1
    lv_img_set_src(ui_PP_cond0, condImgArray[pos2Cond[pos++]]);

    _ui_state_modify(ui_PP_cond1, LV_STATE_CHECKED, 1&hasCondition(pos2Cond[pos])); //If condition is off, we add the Checked state via state 0
    lv_img_set_src(ui_PP_cond1, condImgArray[pos2Cond[pos++]]);

    _ui_state_modify(ui_PP_cond2, LV_STATE_CHECKED, 1&hasCondition(pos2Cond[pos]));
    lv_img_set_src(ui_PP_cond2, condImgArray[pos2Cond[pos++]]);

    _ui_state_modify(ui_PP_cond3, LV_STATE_CHECKED, 1&hasCondition(pos2Cond[pos]));
    lv_img_set_src(ui_PP_cond3, condImgArray[pos2Cond[pos++]]);

    _ui_state_modify(ui_PP_cond4, LV_STATE_CHECKED, 1&hasCondition(pos2Cond[pos]));
    lv_img_set_src(ui_PP_cond4, condImgArray[pos2Cond[pos]]);

    //TODO: Show the appropriate Exhaustion number
}

void ui_PPP_update_conditions(){
    return;
}

//This is used to update the condPage variable and also update it visually
void dndv_set_condPage(bool adjusting, int8_t pagesToTurn){
    if(adjusting){
        pagesToTurn += condPage;
    }
    condPage = (pagesToTurn % DNDV_UI_CONDITIONS_PAGE_COUNT + DNDV_UI_CONDITIONS_PAGE_COUNT) % DNDV_UI_CONDITIONS_PAGE_COUNT; //This guarantees a positive modulus
    ui_PP_update_conditions();
}

//Refresh the UI. Set animating to true if data was received and we want to animate the heart, but false if just navigating
void ui_refresh(bool animating){
    ESP_LOGI(TAG, "Reaching for Semaphore");
    //First we lock the screen
    xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);

    ESP_LOGI(TAG, "Refreshing screen");

    //We retrieve the active screen, then check which it is
    lv_obj_t *screen = lv_scr_act();

    //TODO: Add this as a switch (Below is one example)

    if(screen == ui_HealthProfile){
        struct fighter pc = readPC();
        // Update the side labels
        lv_label_set_text_fmt(ui_HP_hpMoreCurrent, "%d", pc.HP);
        lv_label_set_text_fmt(ui_HP_hpMoreTemp, "%d", pc.tempHP);
        lv_label_set_text_fmt(ui_HP_hpMoreMax, "%d", pc.maxHP);

        //Update the heart
        lv_bar_set_range(ui_HP_hpMaxFill, 0, pc.trueMaxHP);
        lv_bar_set_range(ui_HP_hpFill, 0, pc.trueMaxHP);
        lv_bar_set_range(ui_HP_hpTempFill, 0, pc.trueMaxHP);
        lv_bar_set_value(ui_HP_hpMaxFill, pc.maxHP, LV_ANIM_ON);
        lv_bar_set_value(ui_HP_hpFill,pc.HP, LV_ANIM_ON);
        lv_bar_set_value(ui_HP_hpTempFill, pc.tempHP, LV_ANIM_ON); //TODO turn off anim?
        
        //If animating, animate. Otherwise, set heart text normally
        lv_label_set_text_fmt(ui_HP_hpTotal, "%d", pc.HP + pc.tempHP);

        dndv_update_pfp(ui_HP_profPic, pc.pfp);
    }
    else if(screen == ui_PlayerProfile){
        if(lv_obj_has_flag(ui_PPP_condMoreBck,LV_OBJ_FLAG_HIDDEN)){
            struct fighter pc = readPC();
            lv_bar_set_range(ui_PP_hpMaxFill, 0, pc.trueMaxHP);
            lv_bar_set_range(ui_PP_hpFill, 0, pc.trueMaxHP);
            lv_bar_set_range(ui_PP_hpTempFill, 0, pc.trueMaxHP);
            lv_bar_set_value(ui_PP_hpMaxFill, pc.maxHP, LV_ANIM_OFF);
            lv_bar_set_value(ui_PP_hpFill,pc.HP, LV_ANIM_OFF);
            lv_bar_set_value(ui_PP_hpTempFill, pc.tempHP, LV_ANIM_OFF);
            lv_label_set_text_fmt(ui_PP_hpTotal, "%d", pc.HP + pc.tempHP);

            lv_label_set_text_fmt(ui_PP_name, "%s", pc.nickname);

            lv_label_set_text_fmt(ui_PP_acTotal, "%d", pc.AC + pc.statusAC);
            lv_label_set_text_fmt(ui_PP_acMath, "%d+%d", pc.AC, pc.statusAC);

            ui_PP_update_conditions(pc.allConditions);
            dndv_update_pfp(ui_PP_profPic, pc.pfp);
            ESP_LOGI(TAG, "Updated the rest");
        }else{
            ui_PPP_update_conditions();
            ESP_LOGI(TAG, "Did not update the rest");
        }
    }else if(screen == ui_PlayerCreation){
        struct fighter pc = readPC();
        lv_label_set_text_fmt(ui_PC_nameTxt, "%s", pc.nickname);
        lv_label_set_text_fmt(ui_PC_hpTxt, "%d", pc.trueMaxHP);
        lv_label_set_text_fmt(ui_PC_acTxt, "%d", pc.AC);

        dndv_update_pfp(ui_PC_profPic, pc.pfp);
    }
    
    //Finally, we unlock the screen
    xSemaphoreGive(xGuiSemaphore);
    ESP_LOGI(TAG, "Done Refreshing");

}


static void ui_refresh_on_data_change(void* handler_arg, esp_event_base_t base, int32_t id, void* event_data){
    ui_refresh(true);
}

void pfp_init(){
    for(uint8_t i=0; i<DNDV_PFPS_COUNT; ++i){
        pfpArray[i] = NULL;
    }

    pfpArray[0] = &ui_img_playericons_icon_artificer_png;
    pfpArray[1] = &ui_img_playericons_icon_barbarian_png;
    pfpArray[2] = &ui_img_playericons_icon_bard_png;
    pfpArray[3] = &ui_img_playericons_icon_cleric_png;
    //pfpArray[4] = &ui_img_playericons_icon_druid_png;
    //pfpArray[5] = &ui_img_playericons_icon_fighter_png;
    //pfpArray[6] = &ui_img_playericons_icon_monk_png;
    //pfpArray[7] = &ui_img_playericons_icon_paladin_png;
    //pfpArray[8] = &ui_img_playericons_icon_ranger_png;
    //pfpArray[9] = &ui_img_playericons_icon_rogue_png;
    //pfpArray[10] = &ui_img_playericons_icon_sorcerer_png;
    pfpArray[11] = &ui_img_playericons_icon_warlock_png;
    //pfpArray[12] = &ui_img_playericons_icon_wizard_png;
}

void cond_init(){
    condPage = 0;
    
    for(uint8_t i=0; i<DNDV_CONDITIONS_COUNT; ++i){
        pos2Cond[i] = i;
    }

    condImgArray[DNDV_COND_BLINDED] = &ui_img_conditions_new_blinded_png;
    condImgArray[1] = &ui_img_conditions_new_charmed_png;
    condImgArray[2] = &ui_img_conditions_new_deafened_png;
    condImgArray[3] = &ui_img_conditionextra_new_disarmed_png;
    condImgArray[4] = &ui_img_conditions_new_exhausion_png;  //TODO: fix the misspelling
    condImgArray[5] = &ui_img_conditions_new_frightened_png;
    condImgArray[6] = &ui_img_conditions_new_grappled_png;
    condImgArray[7] = &ui_img_conditionextra_new_hidden_png;
    condImgArray[8] = &ui_img_conditions_new_incapacitated_png;
    condImgArray[9] = &ui_img_conditions_new_invisible_png;
    condImgArray[10] = &ui_img_conditionextra_new_obscured_png;
    condImgArray[11] = &ui_img_conditions_new_paralyzed_png;
    condImgArray[12] = &ui_img_conditions_new_petrified_png;
    condImgArray[13] = &ui_img_conditions_new_poisoned_png;
    condImgArray[14] = &ui_img_conditions_new_prone_png;
    condImgArray[15] = &ui_img_conditionextra_new_raging_png;
    condImgArray[16] = &ui_img_conditions_new_restrained_png;
    condImgArray[17] = &ui_img_conditionextra_new_surprised_png;
    condImgArray[18] = &ui_img_conditions_new_stunned_png;
    condImgArray[19] = &ui_img_conditions_new_unconcious_png;  //TODO: fix the misspelling
}

void  ui_stuff_init() {

    xTaskCreatePinnedToCore(guiTask, "gui", 4096*2, NULL, 0, NULL, 1);

    esp_event_handler_instance_register_with(dndv_event_h, DATA_CHANGED_BASE, PC_DATA_CHANGED, ui_refresh_on_data_change, NULL, NULL);

    pfp_init();
    cond_init();

    //TODO: Refresh every time the screen changes, which should be possible like this
    //lv_display_add_event_cb(, ui_refresh, LV_EVENT_CLICKED, NULL);   /*Assign an event callback (NULL is also 0, but TODO refactor)*/
}

static void guiTask(void *pvParameter) {

    (void) pvParameter;
    xGuiSemaphore = xSemaphoreCreateMutex();

    lv_init();
    lvgl_driver_init();

//LV_HOR_RES & VER are defined as a function, so they can't be used for initialization. Added an O
//This is done for buf1, but should not be needed otherwise?
#define LV_HOR_RESO LV_HOR_RES_MAX
#define LV_VER_RESO LV_VER_RES_MAX

    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf1[LV_HOR_RESO * 40];        //This is 40 in correspondence with the ili driver
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, LV_HOR_RESO * 40);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LV_HOR_RESO;
    disp_drv.ver_res = LV_VER_RESO;
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

