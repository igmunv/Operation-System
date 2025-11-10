#include "func.h"
#include "syscall_func.h"

#include "../libs/device.h"

void _print_text(struct dev_info* device, unsigned char* text, unsigned int size, unsigned int x, unsigned int y, unsigned int font_color, unsigned int bckg_color){

    // Пока что будет только искать vga_text_mode

}

void _new_line(){

    // Пока что будет только искать vga_text_mode

}

void _cursor_update(){

    // Пока что будет только искать vga_text_mode

}

void _clear_display(){

    // Пока что будет только искать vga_text_mode

}

unsigned char _get_current_symbol(){

    // Пока что будет только искать vga_text_mode

}

unsigned char _delete_current_symbol(unsigned int offset){

    // Пока что будет только искать vga_text_mode

}

unsigned char _read_sector(){

}

unsigned char _write_sector(){

}

void _execute_program(){

}

unsigned int _get_execute_program(){

}

unsigned int _get_keyboard_buffer(){

}

unsigned int _get_keyboard_buffer_ptr(){

}

unsigned char _get_keyboard_shift_pressed(){

}

unsigned char _get_keyboard_ctrl_pressed(){

}

unsigned char _get_keyboard_alt_pressed(){

}

unsigned int _get_display_cursor_pos_x(){

}

unsigned int _get_display_cursor_pos_y(){

}

unsigned int _get_ticks(){

}

unsigned int _get_device_count(){

}

unsigned int _get_device_info(){

}
