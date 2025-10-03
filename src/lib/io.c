

unsigned char syscall_display(unsigned char command_type){
    clear_ah();
    in_ah(command_type);
    asm("int $34":::);
}

void io_new_line(){
    syscall_display(1);
}

void io_cursor_update(){
    syscall_display(2);
}

void io_clear(){
    syscall_display(3);
}

unsigned char io_get_current_symbol(short offset){
    // создаем буфер
    // передаем адрес буфера
    // в API он используется и по адресу записывается символ

    in_cx(offset);
    unsigned char result = 0;
    in_ebx(&result);
    syscall_display(4);
    return result;
}

void io_delete_current_symbol(short offset){
    in_bx(offset);
    syscall_display(5);
}

void io_print_symbol(unsigned char symbol, short x, short y, unsigned char font_color, unsigned char background_color){
    in_bl(symbol);
    in_bh(x);
    in_cl(y);
    in_ch(font_color);
    in_dl(background_color);
    syscall_display(0);
}

void io_print(unsigned char* string, char x, char y, char font_color, char bkgr_color){
    for (unsigned char* i = string; *i != '\0'; i++){
        if (*i == '\n'){
            y++;
            x = 0;
            display_cursor_pos_x = x;
            display_cursor_pos_y = y;
        }
        else{
            io_print_symbol(*i, x, y, font_color, bkgr_color);
            x++;
        }
    }
}
