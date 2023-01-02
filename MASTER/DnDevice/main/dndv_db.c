#include "dndv_db.h"
#include "nvs_flash.h"

//  IDs: 1xxxxxxxxxxxxxxx, where each x is a bit
//   Ten digits for a person (actual key), then the last 5 bytes are for the player's character
//          The last 5 bytes must be >0, since 1xxxxxxxxxx00000 is understood as the player him/herself
// 0xx... keys are reserved for NPCs

//      This could be programatically expanded to four bytes if someone has over 31 characters for some reason (or have them make a new Player)

//The database has two namespaces:
char* playerHandle = "People";      //Keys to People and List Of Character Names/IDs
char* pcsHandle = "PCs";            //Keys to Character Data, based off the Player (bitshifted by 6) and Character IDs


void db_write_player();

void db_write_pc();

void db_read_player();

void db_read_pc();


//Requires NVS to be initialized first, then this sets up a test database
void db_test_initialize(void){
    //nvs_flash_erase();
    //nvs_flash_erase_partition();

    nvs_flash_init_partition(playersHandle);
    nvs_flash_init_partition(pcsHandle);

    nvs_handle_t handle;
    ESP_ERROR_CHECK(nvs_open_from_partition(playersHandle, NVS_READWRITE, &handle) != ESP_OK);

    size_t size = 6;
    char* value = malloc(size);
    if(nvs_get_string(handle, 0, value, &size) != ESP_OK){
        return NULL; //Failed to load key
    }
    return value;

    nvs_set_*
    nvs_commit(handle); //To commit all pending chanes

    nvs_close_from_p(handle);

}