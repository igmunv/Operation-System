// Интерфейс API функций для userspace

#include "api.h"
#include "userspace_if.h"
#include "general_functions.h"


void sys_print_text(struct syscall_result* args, struct syscall_result* result){
    _print_text(args->ebx, args->ecx, ((args->edx) & 0xFF),((args->edx >> 8) & 0xFF), args->esi, args->edi);
}

void sys_new_line(struct syscall_result* args, struct syscall_result* result){
    _new_line(args->ebx);
}

void sys_cursor_update(struct syscall_result* args, struct syscall_result* result){
    _cursor_update(args->ebx);
}

void sys_clear_display(struct syscall_result* args, struct syscall_result* result){
    _clear_display(args->ebx);
}

void sys_get_current_symbol(struct syscall_result* args, struct syscall_result* result){
    unsigned char symbol = _get_current_symbol(args->ebx, args->edx);
    result->eax = (unsigned int)symbol;
}

void sys_delete_current_symbol(struct syscall_result* args, struct syscall_result* result){
    unsigned char symbol = _delete_current_symbol(args->ebx, args->edx);
    result->eax = (unsigned int)symbol;
}

void sys_read_sector(struct syscall_result* args, struct syscall_result* result){
    unsigned char state = _read_sector(args->ebx, args->ecx, args->edx);
    result->eax = (unsigned int)state;
}

void sys_write_sector(struct syscall_result* args, struct syscall_result* result){
    unsigned char state = _write_sector(args->ebx, args->ecx, args->edx);
    result->eax = (unsigned int)state;
}

void sys_execute_program(struct syscall_result* args, struct syscall_result* result){
    _execute_program(args->ebx);
}

void sys_get_execute_program(struct syscall_result* args, struct syscall_result* result){
    unsigned int program = _get_execute_program();
    result->eax = (unsigned int)program;
}

void sys_get_keyboard_buffer(struct syscall_result* args, struct syscall_result* result){
    void* buffer = _get_keyboard_buffer(args->ebx);
    result->eax = (unsigned int)buffer;
}

void sys_get_keyboard_buffer_ptr(struct syscall_result* args, struct syscall_result* result){
    unsigned int buffer_ptr = _get_keyboard_buffer_ptr(args->ebx);
    result->eax = buffer_ptr;
}

void sys_get_keyboard_shift_pressed(struct syscall_result* args, struct syscall_result* result){
    unsigned char flag = _get_keyboard_shift_pressed(args->ebx);
    result->eax = (unsigned int)flag;
}

void sys_get_keyboard_ctrl_pressed(struct syscall_result* args, struct syscall_result* result){
    unsigned char flag = _get_keyboard_ctrl_pressed(args->ebx);
    result->eax = (unsigned int)flag;
}

void sys_get_keyboard_alt_pressed(struct syscall_result* args, struct syscall_result* result){
    unsigned char flag = _get_keyboard_alt_pressed(args->ebx);
    result->eax = (unsigned int)flag;
}

void sys_get_display_cursor_pos_x(struct syscall_result* args, struct syscall_result* result){
    unsigned int x = _get_display_cursor_pos_x(result->ebx);
    result->eax = x;
}

void sys_get_display_cursor_pos_y(struct syscall_result* args, struct syscall_result* result){
    unsigned int y = _get_display_cursor_pos_y(result->ebx);
    result->eax = y;
}

void sys_get_ticks(struct syscall_result* args, struct syscall_result* result){
    unsigned int ticks = _get_ticks();
    result->eax = ticks;
}

void sys_get_device_count(struct syscall_result* args, struct syscall_result* result){
    unsigned int count = _get_device_count();
    result->eax = count;
}

void sys_get_device_info(struct syscall_result* args, struct syscall_result* result){
    void* devices = _get_device_info();
    result->eax = (unsigned int)devices;
}

void sys_set_display_cursor_pos_x(struct syscall_result* args, struct syscall_result* result){
    _set_display_cursor_pos_x(result->ebx, result->ecx);
}

void sys_set_display_cursor_pos_y(struct syscall_result* args, struct syscall_result* result){
    _set_display_cursor_pos_x(result->ebx, result->ecx);
}
