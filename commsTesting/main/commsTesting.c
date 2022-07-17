#include <stdio.h>
#include <stdlib.h>
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"


/*
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
*/


static const char *TAG = "MyDevice";


static void recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len){
    ESP_LOGI(TAG, "I heard something! It was %d long",len);
}


static void packet_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (mac_addr == NULL) {
        ESP_LOGE(TAG, "Send cb arg error");
        return;
    }
    printf("Send Status: %d (0 is Success)",status);
    //xEventGroupSetBits(s_evt_group, BIT(status));
}


static void fullInit(){
    const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_netif_init());
    ESP_ERROR_CHECK( esp_event_loop_create_default() );
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );      //default is Flash
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_AP) );     //Should this be APSTA?
    ESP_ERROR_CHECK( esp_wifi_start() );

    ESP_ERROR_CHECK( esp_now_init() );
    ESP_ERROR_CHECK( esp_now_register_recv_cb(recv_cb) );
    ESP_ERROR_CHECK( esp_now_register_send_cb(packet_sent_cb) );
    //ESP_ERROR_CHECK( esp_now_set_pmk((const uint8_t *)MY_ESPNOW_PMK) );
}

#define BROADCAST_MAC {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    fullInit();
    const uint8_t broadcast[] =  BROADCAST_MAC;
    static int first = 1;

    esp_err_t err = esp_now_send(broadcast, (uint8_t*) &first, sizeof(first));
    if(err != ESP_OK){
        ESP_LOGE(TAG, "Send Error (%x)",err);
        return;
    }
    
    ESP_LOGI(TAG, "Now it sent data");
}
