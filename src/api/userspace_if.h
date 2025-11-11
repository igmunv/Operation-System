// Интерфейс API функций для userspace

#ifndef INCL_API_USIF
#define INCL_API_USIF

void sys_print_text(struct syscall_result* args, struct syscall_result* result);

void sys_new_line(struct syscall_result* args, struct syscall_result* result);

void sys_cursor_update(struct syscall_result* args, struct syscall_result* result);

void sys_clear_display(struct syscall_result* args, struct syscall_result* result);

void sys_get_current_symbol(struct syscall_result* args, struct syscall_result* result);

void sys_delete_current_symbol(struct syscall_result* args, struct syscall_result* result);

void sys_read_sector(struct syscall_result* args, struct syscall_result* result);

void sys_write_sector(struct syscall_result* args, struct syscall_result* result);

void sys_execute_program(struct syscall_result* args, struct syscall_result* result);

void sys_get_execute_program(struct syscall_result* args, struct syscall_result* result);

void sys_get_keyboard_buffer(struct syscall_result* args, struct syscall_result* result);

void sys_get_keyboard_buffer_ptr(struct syscall_result* args, struct syscall_result* result);

void sys_get_keyboard_shift_pressed(struct syscall_result* args, struct syscall_result* result);

void sys_get_keyboard_ctrl_pressed(struct syscall_result* args, struct syscall_result* result);

void sys_get_keyboard_alt_pressed(struct syscall_result* args, struct syscall_result* result);

void sys_get_display_cursor_pos_x(struct syscall_result* args, struct syscall_result* result);

void sys_get_display_cursor_pos_y(struct syscall_result* args, struct syscall_result* result);

void sys_get_ticks(struct syscall_result* args, struct syscall_result* result);

void sys_get_device_count(struct syscall_result* args, struct syscall_result* result);

void sys_get_device_info(struct syscall_result* args, struct syscall_result* result);

#endif
