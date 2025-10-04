
// Обработчики прерываний на ASM
extern void api_asm_display_handler();


// Обработчик API прерывания дисплея
void api_display_handler(){

    unsigned char command_type = 0;
    unsigned char symbol = 0;
    unsigned char x = 0;
    unsigned char y = 0;
    unsigned char font_color = 0;
    unsigned char background_color = 0;
    short offset = 0;

    command_type = get_ah();

    // Print symbol
    if (command_type == 0){
        symbol = get_bl();
        x = get_bh();
        y = get_cl();
        font_color = get_ch();
        background_color = get_dl();
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


// Регистрация API прерываний
void api_registration_functions(){
    IDT_reg_handler(34, 0x08, 0x80 | 0x0E, api_asm_display_handler);
}


// Инициализация API
void api_init(){
    api_registration_functions();
}
