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

void terminal_buffer_clear(){
    terminal_buffer[TERMINAL_BUFFER_SIZE+1] = '\0';
    for(unsigned short i = 0; i < TERMINAL_BUFFER_SIZE; i++){
        terminal_buffer[i] = '\0';
    }
    terminal_ptr = 0;
}

short get_str_len(unsigned char* str){
    short n = 0;
    while(*str){
        str++;
        n++;
    }
    return n;
}

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

    char* cmd_help_text = "Available commands:\n| help\n| clear";

    if (is_str_equally(&cmd_clear, get_str_len(&cmd_clear), &terminal_buffer)){
        display_clear();
        terminal_state_line_print();
    }
    else{
         if (is_str_equally(&cmd_help, get_str_len(&cmd_help), &terminal_buffer)){

            display_print(cmd_help_text, 0, display_cursor_pos_y, terminal_default_font_color, terminal_default_bckd_color);
        }
        limit_y_top = display_cursor_pos_y;
        display_new_line();
    }
}

void terminal_enter_key_handler(){
    limit_y_top = display_cursor_pos_y;
    terminal_buffer[terminal_ptr] = '\0';
    terminal_ptr = (terminal_ptr+1) % TERMINAL_BUFFER_SIZE;
    display_new_line();
    terminal_command_handler();
    terminal_buffer_clear();

}

void terminal_backspace_key_handler(){
    while (1){
        if (display_cursor_pos_x == 0 && display_cursor_pos_y - 1 == limit_y_top) break;
        else{
            display_delete_current_symbol(-1);
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


void test(){
    unsigned char str[50];

    itos(terminal_ptr, &str);

    display_print(str, 0, 24, 0, 7);
}


void terminal_scancode_handler(unsigned char scancode){
    if (scancode == 28){ // Enter
        test();
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

void terminal_state_line_print(){
    for(char i = 0; i < 80; i++){
        display_print_symbol('\0', i, 24, 0, 7);
    }
}

void terminal_init(){
    display_clear();
    terminal_buffer_clear();
    display_cursor_update();
    terminal_state_line_print();
    terminal_keyboard_listen();
}
