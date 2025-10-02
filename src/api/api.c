
extern void api_asm_display_handler();

void api_display_handler(){

    unsigned char command_type = 0;
    unsigned char symbol = 0;
    unsigned char x = 0;
    unsigned char y = 0;
    unsigned char font_color = 0;
    unsigned char background_color = 0;
    char offset = 0;

    asm("movb %%ah, %0" : "=r"(command_type) : :);

    // Print symbol
    if (command_type == 0){
        symbol = get_al();
        x = get_bh();
        y = get_bl();
        font_color = get_ch();
        background_color = get_cl();

        display_print_symbol(symbol, x, y, font_color, background_color);

    }

    else if (command_type == 1){
        display_new_line();
    }

    else if (command_type == 2){
        display_cursor_update();
    }

    else if (command_type == 3){
        display_clear();
    }

    else if (command_type == 4){
        offset = get_dh();
        display_get_current_symbol(offset);
    }

    else if (command_type == 5){
        offset = get_dh();
        display_delete_current_symbol(offset);
    }
    outb(0x20, 0x20);
}

void api_registration_functions(){

    //
    // Display API - 34
    //
    // AH - command type:
    //      0 - print symbol
    //      1 - new line
    //      2 - cursor update
    //      3 - clear display
    //      4 - get current symbol (result in AL)
    //      5 - delete current symbol
    // AL - symbol
    // BH - x
    // BL - y
    // CH - font color
    // CL - background color
    // DH - offset
    //

    IDT_reg_handler(34, 0x08, 0x80 | 0x0E, api_asm_display_handler);


}

void syscall_display(){
    asm("int $34":::);
}

void api_init(){
    api_registration_functions();
}
