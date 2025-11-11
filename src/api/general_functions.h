// Общие функции API

#ifndef INCL_API_GENFUNC
#define INCL_API_GENFUNC

void _print_text(unsigned char* text, unsigned int size, unsigned char x, unsigned char y, unsigned int color, unsigned int device_index);

void _new_line(unsigned int device_index);

void _cursor_update(unsigned int device_index);

void _clear_display(unsigned int device_index);

unsigned char _get_current_symbol(unsigned int offset, unsigned int device_index);

unsigned char _delete_current_symbol(unsigned int offset, unsigned int device_index);

unsigned char _read_sector(unsigned int device_index, unsigned int lba, void* dst);

unsigned char _write_sector(unsigned int device_index, unsigned int lba, void* src);

void _execute_program(unsigned int program);

unsigned int _get_execute_program();

void* _get_keyboard_buffer();

unsigned int _get_keyboard_buffer_ptr();

unsigned char _get_keyboard_shift_pressed();

unsigned char _get_keyboard_ctrl_pressed();

unsigned char _get_keyboard_alt_pressed();

unsigned char _get_display_cursor_pos_x(unsigned int device_index);

unsigned char _get_display_cursor_pos_y(unsigned int device_index);

unsigned int _get_ticks();

unsigned int _get_device_count();

void* _get_device_info();

void _set_display_cursor_pos_x(unsigned char x, unsigned int device_index);

void _set_display_cursor_pos_y(unsigned char y, unsigned int device_index);

#endif
