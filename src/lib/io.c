
// Special memory: display
volatile unsigned short* io_display_cursor_pos_x = (unsigned short*)0x5014;
volatile unsigned short* io_display_cursor_pos_y = (unsigned short*)0x5016;

volatile unsigned char io_default_font_color = 7;
volatile unsigned char io_default_bckd_color = 0;

// Системный вызов дисплея
unsigned char syscall_display(unsigned char command_type){
    clear_ah();
    in_ah(command_type);
    asm("int $34":::);
}


// Переход на новую строку
void io_new_line(){
    syscall_display(1);
}


// Обновить курсор
void io_cursor_update(){
    syscall_display(2);
}


// Очистить экран
void io_clear(){
    syscall_display(3);
}


// Получить текущий символ
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


// Удалить текущий символ
void io_delete_current_symbol(short offset){
    in_bx(offset);
    syscall_display(5);
}


// Вывести символ на экран
void io_printx_symbol(unsigned char symbol, unsigned short x, unsigned short y, unsigned char font_color, unsigned char background_color){
    in_bl(symbol);
    in_dx(x);
    in_si(y);
    in_bh(font_color);
    in_cl(background_color);
    syscall_display(0);
}


// Вывести строку на экран
void io_printx(unsigned char* string, char x, char y, char font_color, char bkgr_color){
    for (unsigned char* i = string; *i != '\0'; i++){
        if (*i == '\n'){
            y++;
            x = 0;
            *io_display_cursor_pos_x = x;
            *io_display_cursor_pos_y = y;
        }
        else{
            io_printx_symbol(*i, x, y, font_color, bkgr_color);
            x++;
        }
    }
}


// Упрощённый вывод символа в терминал
void print_symbol(unsigned char symbol){
    io_printx_symbol(symbol, *io_display_cursor_pos_x, *io_display_cursor_pos_y, io_default_font_color, io_default_bckd_color);
}


// Упрощённый вывод строки в терминал
void print(unsigned char* text){
    io_printx(text, *io_display_cursor_pos_x, *io_display_cursor_pos_y, io_default_font_color, io_default_bckd_color);
    io_new_line();
}

// Вывести в виде HEX
void print_hex(char byte){
    struct byte_split_struct result;
    btox(byte, &result);
    print_symbol(result.high);
    (*io_display_cursor_pos_x)++;
    print_symbol(result.low);
    (*io_display_cursor_pos_x)++;
    (*io_display_cursor_pos_x)++;
}

// Получить ввод пользователя
int input(unsigned char* buffer){

}
