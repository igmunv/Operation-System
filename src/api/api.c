// userspace API handler

#include "api.h"
#include "userspace_if.h"
#include "kernel_functions.h"


void api_handler(){

    struct syscall_result args;

    asm volatile(
        "movl %%eax, %0\n"
        "movl %%ebx, %1\n"
        "movl %%ecx, %2\n"
        "movl %%edx, %3\n"
        "movl %%esi, %4\n"
        "movl %%edi, %5\n"
        : "=a"(args.eax),
        "=b"(args.ebx),
        "=c"(args.ecx),
        "=d"(args.edx),
        "=S"(args.esi),
        "=D"(args.edi)
        :
        : "memory"
    );

    unsigned int syscall_number = args.eax;

    struct syscall_result result;

    switch(syscall_number){

        case 0x0:
            sys_print_text(&args, &result);
            break;

        case 0x1:
            sys_new_line(&args, &result);
            break;

        case 0x2:
            sys_cursor_update(&args, &result);
            break;

        case 0x3:
            sys_clear_display(&args, &result);
            break;

        case 0x4:
            sys_get_current_symbol(&args, &result);
            break;

        case 0x5:
            sys_delete_current_symbol(&args, &result);
            break;

        case 0x10:
            sys_read_sector(&args, &result);
            break;

        case 0x11:
            sys_write_sector(&args, &result);
            break;

        case 0x50:
            sys_execute_program(&args, &result);
            break;

        case 0x100:
            sys_get_execute_program(&args, &result);
            break;

        case 0x101:
            sys_get_keyboard_buffer(&args, &result);
            break;

        case 0x102:
            sys_get_keyboard_buffer_ptr(&args, &result);
            break;

        case 0x103:
            sys_get_keyboard_shift_pressed(&args, &result);
            break;

        case 0x104:
            sys_get_keyboard_ctrl_pressed(&args, &result);
            break;

        case 0x105:
            sys_get_keyboard_alt_pressed(&args, &result);
            break;

        case 0x106:
            sys_get_display_cursor_pos_x(&args, &result);
            break;

        case 0x107:
            sys_get_display_cursor_pos_y(&args, &result);
            break;

        case 0x108:
            sys_get_ticks(&args, &result);
            break;

        case 0x109:
            sys_get_device_count(&args, &result);
            break;

        case 0x10A:
            sys_get_device_info(&args, &result);
            break;

    }

    outb(0x20, 0x20);

    asm volatile(
        "movl %0, %%eax\n"
        "movl %1, %%ebx\n"
        "movl %2, %%ecx\n"
        "movl %3, %%edx\n"
        "movl %4, %%esi\n"
        "movl %5, %%edi\n"
        :
        : "a"(result.eax),
        "b"(result.ebx),
        "c"(result.ecx),
        "d"(result.edx),
        "S"(result.esi),
        "D"(result.edi)
        : "memory"
    );

}

// Регистрация API прерываний
void api_registration_functions(){
    // Не забывай: IRQ всегда делает только маленькую и быструю работу
    _int_reg_handler(0x22, 0x08, 0x80 | 0x0E, api_asm_handler);
}


// Инициализация API
void api_init(){
    api_registration_functions();
}
