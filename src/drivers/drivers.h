#ifndef INCL_DRIVER_DRIVERS
#define INCL_DRIVER_DRIVERS


struct driver_info {
    unsigned char name[16];
    unsigned char filename[16];
    void* init_ptr;

    unsigned char subclass;
    unsigned char classcode;

}

void drivers_init();
void drivers_init_late();

#endif
