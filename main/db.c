#include "db.h"
#include "data_pc.h"

#define localSpace "localSaveSpace"


//Requires NVS to be initialized first, then this sets up a test database
void db_test_initialize(void){
    //nvs_flash_erase();
    //nvs_flash_erase_partition();

    //nvs_flash_init_partition(playersHandle);  //Still gonna use default NVS partition; there's namespaces within.
    //nvs_flash_init_partition(pcsHandle);

    nvs_handle_t handle;
    ESP_ERROR_CHECK(nvs_open(localSpace, NVS_READWRITE, &handle) != ESP_OK);

    size_t size = 6;
    char* value = malloc(size);
    if(nvs_get_str(handle, 0, value, &size) != ESP_OK){
        return; //return NULL; //Failed to load key
    }

    printf("%s",value);
    //return value;

    //nvs_set_*;
    nvs_commit(handle); //To commit all pending changes

    nvs_close(handle);
}

/*esp_err_t dndv_db_write(Key key, char* data, char* dataSpace){
    nvs_handle_t handle;
    nvs_open(dataSpace, NVS_READWRITE, &handle);
    nvs_set_blob(handle, key, data, sizeof(Player));
    nvs_close(handle);
}*/

#define LOCAL_KEY "0"

esp_err_t db_save_local_pc(){
    struct fighter pc = readPC();
    size_t size = sizeof(struct fighter);
    nvs_handle_t handle;
    ESP_ERROR_CHECK(nvs_open(localSpace, NVS_READWRITE, &handle));
    ESP_ERROR_CHECK(nvs_set_blob(handle, LOCAL_KEY, &pc, size));
    nvs_commit(handle);
    nvs_close(handle);
    return ESP_OK;
}

esp_err_t db_load_local_pc(){
    struct fighter value;
    size_t size = sizeof(struct fighter);
    nvs_handle_t handle;
    esp_err_t err = nvs_open(localSpace, NVS_READONLY, &handle);
    if(err != ESP_OK) return err;       //If this doesn't work, we need to save_local_pc first.

    err = nvs_get_blob(handle, LOCAL_KEY, &value, &size);       // We can get size by putting value to NULL, otherwise we set it beforehand
    nvs_close(handle); //This may have to be later
    if(err == ESP_OK && size>0){            //If size is 0, then we haven't writen a PC yet
        writePC(value);    //Take all the values from here and write them to the PC
    }else if(size==0){
        ESP_LOGI("DB", "%d", err);
        return ESP_ERR_NOT_FOUND;
    }
    //free(value);
    return err;
}

