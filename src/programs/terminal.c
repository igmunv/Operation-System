#define TERMINAL_BUFFER_SIZE 1024

// Special memory: keyboard
extern volatile unsigned char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
extern volatile unsigned char keyboard_buffer_ptr;

extern volatile char keyboard_shift_pressed;

// Special memory: display
extern volatile unsigned short display_cursor_pos_x;
extern volatile unsigned short display_cursor_pos_y;

// Local memory
volatile unsigned char keyboard_buffer_tail;
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

void print_symbol(unsigned char symbol){
    io_print_symbol(symbol, display_cursor_pos_x, display_cursor_pos_y, terminal_default_font_color, terminal_default_bckd_color);
}

void print(unsigned char* text){
    io_print(text, display_cursor_pos_x, display_cursor_pos_y, terminal_default_font_color, terminal_default_bckd_color);
}

void terminal_command_handler(){

    unsigned char cmd_help[5] = "help";
    unsigned char cmd_clear[6] = "clear";
    unsigned char cmd_uptime[7] = "uptime";
    unsigned char cmd_poweroff[9] = "poweroff";

    unsigned char cmd_adr[4] = "adr";

    char* cmd_help_text = "Available commands:\n| help\n| clear\n| uptime\n| poweroff";

    if (is_str_equally(&cmd_clear, strlen(&cmd_clear), &terminal_buffer)){
        io_clear();
    }
    else{
         if (is_str_equally(&cmd_help, strlen(&cmd_help), &terminal_buffer)){
            //display_print(cmd_help_text, 0, display_cursor_pos_y, terminal_default_font_color, terminal_default_bckd_color);

        }

        else if (is_str_equally(&cmd_uptime, strlen(&cmd_uptime), &terminal_buffer)){
            long uptime_second = ticks / 1000;
            unsigned char uptime_second_str[50];
            itos(uptime_second, &uptime_second_str);
            print(uptime_second_str);
        }
        else if (is_str_equally(&cmd_poweroff, strlen(&cmd_poweroff), &terminal_buffer)){
            outw(0x604, 0x2000);
        }
        else {
            print("Command not found!");
        }

        limit_y_top = display_cursor_pos_y;
        io_new_line();
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
            io_delete_current_symbol(-1);
            terminal_ptr--;
            terminal_buffer[terminal_ptr] = '\0';
            unsigned char symbol = io_get_current_symbol(-1);
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
        io_cursor_update();
    }
}

void terminal_scancode_handler(unsigned char scancode){

    // Enter
    if (scancode == 28){
        terminal_enter_key_handler();
    }

    // BackSpace
    else if (scancode == 14){
        terminal_backspace_key_handler();
    }

    // Other
    else{
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
    io_clear();
    terminal_buffer_clear();
    io_cursor_update();
    terminal_keyboard_listen();
}
