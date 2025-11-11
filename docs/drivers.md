
## Virt: VGA Text Mode


функции:
funcs[0] - void print_text(unsigned char*, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char)
funcs[1] - void new_line(void)
funcs[2] - void cursor_update(void)
funcs[3] - void clear_display(void)
funcs[4] - unsigned char get_current_symbol(unsigned int)
funcs[5] - unsigned char delete_current_symbol(unsigned int)

funcs[6] - unsigned char get_display_cursor_pos_x(void)
funcs[7] - unsigned char get_display_cursor_pos_y(void)

funcs[8] - void set_display_cursor_pos_x(unsigned char)
funcs[9] - void set_display_cursor_pos_y(unsigned char)

должны иметь поля:

x
y


клавиатура

поля:
buffer
buffer_ptr
shift_pressed
ctrl_pressed
alt_pressed



