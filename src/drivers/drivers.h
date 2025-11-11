#ifndef INCL_DRIVER_DRIVERS
#define INCL_DRIVER_DRIVERS

#define DRIVER_FUNC_COUNT 16


struct driver_info {
    unsigned char name[16];
    unsigned char filename[16];
    void* init_ptr;

    unsigned char subclass;
    unsigned char classcode;

    void* funcs[DRIVER_FUNC_COUNT];

};

void drivers_init();
void drivers_init_late();


enum dfunctype_virt_display_vgatext{
    PRINT_TEXT,
    NEW_LINE,
    CURSOR_UPDATE,
    CLEAR_DISPLAY,
    GET_CURRENT_SYMBOL,
    DELETE_CURRENT_SYMBOL,
    GET_CURSOR_POS_X,
    GET_CURSOR_POS_Y,
    SET_CURSOR_POS_X,
    SET_CURSOR_POS_Y
};


#endif
