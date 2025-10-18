#include "device.h"
#include "../memcpy.h"

int device_reg(unsigned int dev_type, unsigned char* name, unsigned int name_size, unsigned int option1, unsigned int option2, unsigned int option3){

    struct dev_info devinfo;
    dev_info.id = DEVICE_COUNT;
    dev_info.dev_type = dev_type;
    memcpy(&(dev_info.name), name, name_size);
    dev_info.option1 = option1;
    dev_info.option2 = option2;
    dev_info.option3 = option3;

    DEVICE_COUNT++;

}
