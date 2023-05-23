#include "dndv_db.h"
#include "nvs_flash.h"
#include "dndv_internals.h"

//  IDs: 1xxxxxxxxxxxxxxx, where each x is a bit
//   Ten digits for a person (actual key), then the last 5 bytes are for the player's character
//          The last 5 bit word must be >0, since 1xxxxxxxxxx00000 is understood as the player him/herself
// 0xx... keys are reserved for NPCs

//If someone has more than 31 players, enter them as a new Player

//The database has two namespaces:
char* playerSpace = "People";      //Keys to People and List Of Character Names/IDs
char* pcSpace = "PCs";            //Keys to Character Data, based off the Player (bitshifted by 6) and Character IDs


//Requires NVS to be initialized first, then this sets up a test database
void db_test_initialize(void){
    //nvs_flash_erase();
    //nvs_flash_erase_partition();

    //nvs_flash_init_partition(playersHandle);  //Still gonna use default NVS partition; there's namespaces within.
    //nvs_flash_init_partition(pcsHandle);

    nvs_handle_t handle;
    ESP_ERROR_CHECK(nvs_open(playerSpace, NVS_READWRITE, &handle) != ESP_OK);

    size_t size = 6;
    char* value = malloc(size);
    if(nvs_get_string(handle, 0, value, &size) != ESP_OK){
        return NULL; //Failed to load key
    }
    return value;

    //nvs_set_*;
    nvs_commit(handle); //To commit all pending chanes

    nvs_close(handle);

}

/*esp_err_t dndv_db_write(Key key, char* data, char* dataSpace){
    nvs_handle_t handle;
    nvs_open(dataSpace, NVS_READWRITE, &handle);
    nvs_set_blob(handle, key, data, sizeof(Player));
    nvs_close(handle);
}*/

//Make a struct: PlayerFile (and PCFile)
esp_err_t db_write_player(Key key, Player player){      //Keys are ASCII strings, technically
    nvs_handle_t handle;
    nvs_open(playerSpace, NVS_READWRITE, &handle);
    nvs_set_blob(handle, key, &player, sizeof(Player));
    nvs_close(handle);
}

esp_err_t db_write_pc(Key key, PC pc){
    nvs_handle_t handle;
    nvs_open(pcSpace, NVS_READWRITE, &handle);
    nvs_set_blob(handle, key, &pc, sizeof(PC));
    nvs_close(handle);
}

Player db_read_player(Key key){
    nvs_handle_t handle;
    nvs_open(playerSpace, NVS_READONLY, &handle);
    Player* value;
    esp_err_t err = nvs_get_blob(handle, key, value, sizeof(Player));
    nvs_close(handle);
    return *value;
}

PC db_read_pc(Key key){
    nvs_handle_t handle;
    nvs_open(playerSpace, NVS_READONLY, &handle);
    PC* value;
    esp_err_t err = nvs_get_blob(handle, key, value, sizeof(PC));
    nvs_close(handle);
    return *value;
}

