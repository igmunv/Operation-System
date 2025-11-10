#ifndef INCL_API_FUNC
#define INCL_API_FUNC

void _print_text(unsigned char* text, unsigned int size, unsigned int x, unsigned int y, unsigned int font_color, unsigned int bckg_color);

void _new_line();

void _cursor_update();

void _clear_display();

unsigned char _get_current_symbol();

unsigned char _delete_current_symbol();

unsigned char _read_sector();

unsigned char _write_sector();

void _execute_program();

unsigned int _get_execute_program();

unsigned int _get_keyboard_buffer();

unsigned int _get_keyboard_buffer_ptr();

unsigned char _get_keyboard_shift_pressed();

unsigned char _get_keyboard_ctrl_pressed();

unsigned char _get_keyboard_alt_pressed();

unsigned int _get_display_cursor_pos_x();

unsigned int _get_display_cursor_pos_y();

unsigned int _get_ticks();

unsigned int _get_device_count();

unsigned int _get_device_info();

#endif
