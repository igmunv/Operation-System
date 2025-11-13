#include "device.h"
#include "../libs/memory.h"
#include "../libs/shared_memory.h"

int device_reg(unsigned int dev_type, unsigned char* name, unsigned int name_size, unsigned int option1, unsigned int option2, unsigned int option3){

    struct dev_info devinfo;
    devinfo.id = DEVICE_COUNT;
    devinfo.dev_type = dev_type;
    memcpy(&(devinfo.name), name, name_size);
    devinfo.option1 = option1;
    devinfo.option2 = option2;
    devinfo.option3 = option3;

    DEVICES_INFO[DEVICE_COUNT] = devinfo;
    DEVICE_COUNT++;

}


// Получить информацию о устройстве по id, в dst
int device_get(unsigned int dev_id, struct dev_info* dst){
    for(int i = 0; i < DEVICE_COUNT; i++){
        if (DEVICES_INFO[i].id == dev_id){
            dst->id = DEVICES_INFO[i].id;
            dst->dev_type = DEVICES_INFO[i].dev_type;
            dst->id = DEVICES_INFO[i].name;
            memcpy(dst->name, DEVICES_INFO[i].name, 41);
            dst->option1 = DEVICES_INFO[i].option1;
            dst->option2 = DEVICES_INFO[i].option2;
            dst->option3 = DEVICES_INFO[i].option3;
            return 0; // Found
        }
    }
    return -1; // Not found
}
