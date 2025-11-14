// Общие функции API

#include "general_functions.h"

#include "../libs/device.h"
#include "../libs/driver.h"

#include "../kernel/kernel.h"
#include "../kernel/PIT.h"
#include "../drivers/devices.h"
#include "../drivers/drivers.h"

void _print_text(unsigned char* text, unsigned int size, unsigned char x, unsigned char y, unsigned int color, unsigned int device_index){

    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    void (*driver_print_text)(unsigned char*, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char) = (void (*)(unsigned char*, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char))(device->driver->funcs[PRINT_TEXT]);

    driver_print_text(text, size, x, y, (color & 0xFF), ((color >> 8) & 0xFF));

}

void _new_line(unsigned int device_index){

    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    void (*driver_new_line)(void) = (void (*)(void))(device->driver->funcs[NEW_LINE]);

    driver_new_line();

}

void _cursor_update(unsigned int device_index){

    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    void (*driver_cursor_update)(void) = (void (*)(void))(device->driver->funcs[CURSOR_UPDATE]);

    driver_cursor_update();

}

void _clear_display(unsigned int device_index){

    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    void (*driver_clear_display)(void) = (void (*)(void))(device->driver->funcs[CLEAR_DISPLAY]);

    driver_clear_display();

}

unsigned char _get_current_symbol(unsigned int offset, unsigned int device_index){

    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    unsigned char (*driver_get_current_symbol)(unsigned int) = (unsigned char (*)(unsigned int))(device->driver->funcs[GET_CURRENT_SYMBOL]);

    unsigned char symbol = driver_get_current_symbol(offset);
    return symbol;

}

unsigned char _delete_current_symbol(unsigned int offset, unsigned int device_index){

    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    unsigned char (*driver_delete_current_symbol)(unsigned int) = (unsigned char (*)(unsigned int))(device->driver->funcs[DELETE_CURRENT_SYMBOL]);

    unsigned char symbol = driver_delete_current_symbol(offset);
    return symbol;

}

unsigned char _read_sector(unsigned int device_index, unsigned int lba, void* dst){

}

unsigned char _write_sector(unsigned int device_index, unsigned int lba, void* src){

}

void _execute_program(unsigned int program){
    EXECUTE_PROGRAM = program;
}

unsigned int _get_execute_program(){
    return EXECUTE_PROGRAM;
}

void* _get_keyboard_buffer(){

}

unsigned int _get_keyboard_buffer_ptr(){

}

unsigned char _get_keyboard_shift_pressed(){

}

unsigned char _get_keyboard_ctrl_pressed(){

}

unsigned char _get_keyboard_alt_pressed(){

}

unsigned char _get_display_cursor_pos_x(unsigned int device_index){
    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    unsigned char (*driver_get_display_cursor_pos_x)(void) = (unsigned char (*)(void))(device->driver->funcs[GET_CURSOR_POS_X]);

    unsigned char symbol = driver_get_display_cursor_pos_x();
    return symbol;
}

unsigned char _get_display_cursor_pos_y(unsigned int device_index){
    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    unsigned char (*driver_get_display_cursor_pos_y)(void) = (unsigned char (*)(void))(device->driver->funcs[GET_CURSOR_POS_Y]);

    unsigned char symbol = driver_get_display_cursor_pos_y();
    return symbol;
}

unsigned int _get_ticks(){
    return TICKS;
}

unsigned int _get_device_count(){
    return DEVICE_COUNT;
}

void _set_display_cursor_pos_x(unsigned char x, unsigned int device_index){
    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    unsigned char (*driver_set_display_cursor_pos_x)(unsigned char) = (unsigned char (*)(unsigned char))(device->driver->funcs[SET_CURSOR_POS_X]);

    driver_set_display_cursor_pos_x(x);
}

void _set_display_cursor_pos_y(unsigned char y, unsigned int device_index){
    struct dev_info* devices = _get_device_info();
    struct dev_info* device = &devices[device_index];

    unsigned char (*driver_set_display_cursor_pos_y)(unsigned char) = (unsigned char (*)(unsigned char))(device->driver->funcs[SET_CURSOR_POS_Y]);

    driver_set_display_cursor_pos_y(y);
}

void* _get_device_info(){
    return &DEVICES_INFO;
}
