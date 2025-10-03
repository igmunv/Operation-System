#define TERMINAL_BUFFER_SIZE 1024

extern volatile unsigned char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
extern volatile unsigned char keyboard_buffer_ptr;
volatile unsigned char keyboard_buffer_tail;

extern volatile char keyboard_shift_pressed;

extern volatile unsigned short display_cursor_pos_x;
extern volatile unsigned short display_cursor_pos_y;

volatile unsigned char terminal_buffer[TERMINAL_BUFFER_SIZE+1];
volatile unsigned short terminal_ptr = 0;

char limit_y_top = 0;

char terminal_default_font_color = 7;
char terminal_default_bckd_color = 0;

void syscall_display(unsigned char command_type){
    clear_ah();
    in_ah(command_type);
    asm("int $34":::);
}

void terminal_buffer_clear(){
    terminal_buffer[TERMINAL_BUFFER_SIZE+1] = '\0';
    for(unsigned short i = 0; i < TERMINAL_BUFFER_SIZE; i++){
        terminal_buffer[i] = '\0';
    }
    terminal_ptr = 0;
}

void terminal_new_line(){
    syscall_display(1);
}

void terminal_clear(){
    syscall_display(3);
}

void terminal_delete_current_symbol(short offset){
    in_bx(offset);
    syscall_display(5);
}

void terminal_print_symbol(unsigned char symbol, short x, short y, unsigned char font_color, unsigned char background_color){
    in_bl(symbol);
    in_bh(x);
    in_cl(y);
    in_ch(font_color);
    in_dl(background_color);
    syscall_display(0);
}

void print(unsigned char* string, char x, char y, char font_color, char bkgr_color){
    for (unsigned char* i = string; *i != '\0'; i++){
        if (*i == '\n'){
            y++;
            x = 0;
            display_cursor_pos_x = x;
            display_cursor_pos_y = y;
        }
        else{
            terminal_print_symbol(*i, x, y, font_color, bkgr_color);
            x++;
        }
    }
}

short get_str_len(unsigned char* str){
    short n = 0;
    while(*str){
        str++;
        n++;
    }
    return n;
}


// in string.c
char is_str_equally(unsigned char* str1, short str1_len, unsigned char* str2){
    for (int n = 0; n <= (int)str1_len; n++){
        unsigned char str1_sym = str1[n];
        unsigned char str2_sym = str2[n];
        unsigned char xor = str1_sym ^ str2_sym;
        if (xor != 0 ) return 0;
    }
    return 1;
}

void terminal_command_handler(){

    unsigned char cmd_help[5] = "help";
    unsigned char cmd_clear[6] = "clear";
    unsigned char cmd_uptime[7] = "uptime";
    unsigned char cmd_poweroff[9] = "poweroff";

    unsigned char cmd_adr[4] = "adr";

    char* cmd_help_text = "Available commands:\n| help\n| clear\n| uptime\n| poweroff";

    if (is_str_equally(&cmd_clear, get_str_len(&cmd_clear), &terminal_buffer)){
        terminal_clear();
    }
    else{
         if (is_str_equally(&cmd_help, get_str_len(&cmd_help), &terminal_buffer)){
            //display_print(cmd_help_text, 0, display_cursor_pos_y, terminal_default_font_color, terminal_default_bckd_color);

        }

        else if (is_str_equally(&cmd_uptime, get_str_len(&cmd_uptime), &terminal_buffer)){
            long uptime_second = ticks / 1000;
            unsigned char uptime_second_str[50];
            itos(uptime_second, &uptime_second_str);
            print(uptime_second_str, 0, display_cursor_pos_y, terminal_default_font_color, terminal_default_bckd_color);
            print("second", 20, display_cursor_pos_y, terminal_default_font_color, terminal_default_bckd_color);
        }
        else if (is_str_equally(&cmd_poweroff, get_str_len(&cmd_poweroff), &terminal_buffer)){
            outw(0x604, 0x2000);
        }
        else {
            print("Command not found!", 0, display_cursor_pos_y, 4, terminal_default_bckd_color);
        }

        limit_y_top = display_cursor_pos_y;
        terminal_new_line();
    }
}

void terminal_enter_key_handler(){
    limit_y_top = display_cursor_pos_y;
    terminal_buffer[terminal_ptr] = '\0';
    terminal_ptr = (terminal_ptr+1) % TERMINAL_BUFFER_SIZE;
    display_new_line();
    if (terminal_ptr > 1) terminal_command_handler();
    terminal_buffer_clear();

}

void terminal_backspace_key_handler(){
    while (1){
        if (display_cursor_pos_x == 0 && display_cursor_pos_y - 1 == limit_y_top) break;
        else{
            terminal_delete_current_symbol(-1);
            terminal_ptr--;
            terminal_buffer[terminal_ptr] = '\0';
            unsigned char symbol = display_get_current_symbol(-1);
            if ((display_cursor_pos_y > 0 || (display_cursor_pos_y == 0 && display_cursor_pos_x > 0)) && symbol == '\0' && display_cursor_pos_x != 0) continue;
            else break;
        }
    }
}

void terminal_other_key_handler(unsigned char scancode){
    unsigned char symbol = keyboard_scancode_to_ascii(scancode, keyboard_shift_pressed);
    if (symbol != '\0'){
        terminal_buffer[terminal_ptr] = symbol;
        terminal_ptr = (terminal_ptr+1) % TERMINAL_BUFFER_SIZE;
        display_print_symbol(symbol, display_cursor_pos_x, display_cursor_pos_y, terminal_default_font_color, terminal_default_bckd_color);
        display_cursor_pos_x++;
        display_cursor_update();
    }
}

void terminal_state_line_print(){
    for(char i = 0; i < 80; i++){
        display_print_symbol('\0', i, 24, 0, 7);
    }
}

void test(short i){
    terminal_state_line_print();
    unsigned char str[50];
    unsigned char ticks_str[50];
    itos(terminal_ptr, &str);
    itos((long)i, &ticks_str);

    display_print(str, 0, 24, 0, 7);

    display_print(ticks_str, 40, 24, 0, 7);
}

void terminal_scancode_handler(unsigned char scancode){
    if (scancode == 28){ // Enter

        terminal_enter_key_handler();
    }
    else if (scancode == 14){ // BackSpace
        terminal_backspace_key_handler();
    }
    else{ // Other
        terminal_other_key_handler(scancode);
    }

}

void terminal_keyboard_listen(){
    keyboard_buffer_tail = keyboard_buffer_ptr;
    while (1){
        if (keyboard_buffer_tail != keyboard_buffer_ptr){
            unsigned char scancode;
            scancode = keyboard_buffer[keyboard_buffer_tail];
            terminal_scancode_handler(scancode);
            keyboard_buffer_tail = (keyboard_buffer_tail+1) % KEYBOARD_BUFFER_SIZE;
        }
        sleep(10);
    }
}

void terminal_init(){
    display_clear();
    terminal_buffer_clear();
    display_cursor_update();
    terminal_state_line_print();
    terminal_keyboard_listen();
}
