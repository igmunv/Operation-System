#include "api.h"
#include "../drivers/ata.h"
#include "../libs/shared_memory.h"
#include "syscall_func.h"

#include "../kernel.h"
#include "../PIT.h"

// Обработчик API прерывания дисплея
void api_display_handler(){

    unsigned char command_type = 0;
    unsigned char symbol = 0;
    unsigned short x = 0;
    unsigned short y = 0;
    unsigned char font_color = 0;
    unsigned char background_color = 0;
    short offset = 0;

    command_type = get_ah();

    // Print symbol
    if (command_type == 0){
        symbol = get_bl();
        x = get_dx();
        y = get_si();
        font_color = get_bh();
        background_color = get_cl();
        display_print_symbol(symbol, x, y, font_color, background_color);
    }

    // New line
    else if (command_type == 1){
        display_new_line();
    }

    // Cursor update
    else if (command_type == 2){
        display_cursor_update();
    }

    // Display clear
    else if (command_type == 3){
        display_clear();
    }

    // Get current symbol
    else if (command_type == 4){
        offset = get_cx();
        unsigned char* result = get_ebx();
        *result = display_get_current_symbol(offset);
    }

    // Delete current symbol
    else if (command_type == 5){
        offset = get_bx();
        display_delete_current_symbol(offset);
    }

    outb(0x20, 0x20);
}

// Обработчик API прерывания ATA диска
void api_ata_handler(){
    unsigned char command_type = 0;
    command_type = get_ah();

    if (command_type == 0){
        unsigned int lba = get_ebx();
        unsigned char* result = get_edx();
        ata_driver_read_sector(lba, result);
    }

    outb(0x20, 0x20);
}

// Обработчик API прерывания запуска программы
void api_execute_handler(){
    EXECUTE_PROGRAM = get_ebx();
    outb(0x20, 0x20);
}


struct syscall_result {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int esi;
    unsigned int edi;
    unsigned int ebp;
};




void api_handler(){

    struct syscall_result args;

    __asm__ volatile(
        "movl %%eax, %0\n"
        "movl %%ebx, %1\n"
        "movl %%ecx, %2\n"
        "movl %%edx, %3\n"
        "movl %%esi, %4\n"
        "movl %%edi, %5\n"
        "movl %%ebp, %6\n"
        : "=r"(args.eax),
        "=r"(args.ebx),
        "=r"(args.ecx),
        "=r"(args.edx),
        "=r"(args.esi),
        "=r"(args.edi),
        "=r"(args.ebp)
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

    __asm__ volatile(
        "movl %0, %%eax\n"
        "movl %1, %%ebx\n"
        "movl %2, %%ecx\n"
        "movl %3, %%edx\n"
        "movl %4, %%esi\n"
        "movl %5, %%edi\n"
        "movl %6, %%ebp\n"
        :
        : "r"(result.eax),
        "r"(result.ebx),
        "r"(result.ecx),
        "r"(result.edx),
        "r"(result.esi),
        "r"(result.edi),
        "r"(result.ebp)
        : "eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "memory"
    );

}

// Регистрация API прерываний
void api_registration_functions(){
    // Не забывай: IRQ всегда делает только маленькую и быструю работу
    IDT_reg_handler(0x22, 0x08, 0x80 | 0x0E, api_asm_handler);
}


// Инициализация API
void api_init(){
    api_registration_functions();
}
