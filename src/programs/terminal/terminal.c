#define TERMINAL_BUFFER_SIZE 1024
#define KEYBOARD_BUFFER_SIZE 16

#include "../libs/shared_memory.h"
#include "../libs/asm.c"
#include "../libs/string.c"
#include "../libs/io.c"
#include "../libs/time.c"
#include "../libs/programs.c"

// Header: start
volatile unsigned char _start_header[16] __attribute__((section(".start_header"))) = {'_','_','_','I','A','M','P','R','O','G','R','A','M','_','_','_'};
// Header: info
volatile unsigned char _info_header[20] __attribute__((section(".info_header"))) = "terminal";
// Header: end
volatile unsigned char _end_header[16] __attribute__((section(".end_header"))) = {'_','_','_','E','N','D','P','R','O','G','R','A','M','_','_','_'};

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





void terminal_command_handler(){

    // Commands
    unsigned char cmd_help[5] = "help";
    unsigned char cmd_list[5] = "list";
    unsigned char cmd_clear[6] = "clear";
    unsigned char cmd_uptime[7] = "uptime";
    unsigned char cmd_poweroff[9] = "poweroff";

    // Data for commands
    char* cmd_help_text = "Available commands:\n| [NUMBER] - run program\n| list - view programs\n| clear - clear display\n| poweroff - shutdown system";

    // Clear
    if (is_str_equally(&cmd_clear, strlen(&cmd_clear), &terminal_buffer)){
        io_clear();
    }

    // Number - Run program
    else if (is_digit(&terminal_buffer)){
        int prog_num;
        stoi(&terminal_buffer, &prog_num);
        program_run(prog_num);
    }

    // Other commands
    else{

        // Help
        if (is_str_equally(&cmd_help, strlen(&cmd_help), &terminal_buffer)){
            print(cmd_help_text);
        }

        // List
        else if (is_str_equally(&cmd_list, strlen(&cmd_list), &terminal_buffer)){
            print("All programs in disk:");
            for (int i = 1; i < PROGLOADER_PROGRAM_COUNT; i++){

                char num[3] = {0,0,0};
                itos(i, &num);
                print(num);
                DISPLAY_CURSOR_POS_Y--;
                DISPLAY_CURSOR_POS_X++;
                DISPLAY_CURSOR_POS_X++;
                DISPLAY_CURSOR_POS_X++;
                DISPLAY_CURSOR_POS_X++;
                print(((struct program_info*)PROGLOADER_PROGRAMS)[i].name);
            }
        }

        // Poweroff
        else if (is_str_equally(&cmd_poweroff, strlen(&cmd_poweroff), &terminal_buffer)){
            outw(0x604, 0x2000);
        }

        else {

            // Chech name programs and run
            for (int i = 1; i < PROGLOADER_PROGRAM_COUNT; i++){
                if (is_str_equally(((struct program_info*)PROGLOADER_PROGRAMS)[i].name, strlen(((struct program_info*)PROGLOADER_PROGRAMS)[i].name), &terminal_buffer)){
                    program_run(i);
                }
            }

            // Unknow command
            print("Command not found!");
        }

        limit_y_top = DISPLAY_CURSOR_POS_Y;

    }
}

void terminal_enter_key_handler(){
    limit_y_top = DISPLAY_CURSOR_POS_Y;
    terminal_buffer[terminal_ptr] = '\0';
    terminal_ptr = (terminal_ptr+1) % TERMINAL_BUFFER_SIZE;
    io_new_line();
    if (terminal_ptr > 1) terminal_command_handler();
    terminal_buffer_clear();
}

void terminal_backspace_key_handler(){
    while (1){
        if (DISPLAY_CURSOR_POS_X == 0 && DISPLAY_CURSOR_POS_Y - 1 == limit_y_top) break;
        else{
            io_delete_current_symbol(-1);
            terminal_ptr--;
            terminal_buffer[terminal_ptr] = '\0';
            unsigned char symbol = io_get_current_symbol(-1);
            if ((DISPLAY_CURSOR_POS_Y > 0 || (DISPLAY_CURSOR_POS_Y == 0 && DISPLAY_CURSOR_POS_X > 0)) && symbol == '\0' && DISPLAY_CURSOR_POS_X != 0) continue;
            else break;
        }
    }
}

void terminal_other_key_handler(unsigned char scancode){
    unsigned char symbol = scancode_to_ascii(scancode, KEYBOARD_SHIFT_PRESSED);
    if (symbol != '\0'){
        terminal_buffer[terminal_ptr] = symbol;
        terminal_ptr = (terminal_ptr+1) % TERMINAL_BUFFER_SIZE;
        io_printx_symbol(symbol, DISPLAY_CURSOR_POS_X, DISPLAY_CURSOR_POS_Y, terminal_default_font_color, terminal_default_bckd_color);
        io_cursor_update();
    }
}

void cursor(){
    io_printx_symbol('>', DISPLAY_CURSOR_POS_X, DISPLAY_CURSOR_POS_Y, terminal_default_font_color, terminal_default_bckd_color);
    io_printx_symbol(' ', DISPLAY_CURSOR_POS_X, DISPLAY_CURSOR_POS_Y, terminal_default_font_color, terminal_default_bckd_color);
    io_cursor_update();
}

void terminal_scancode_handler(unsigned char scancode){

    // Enter
    if (scancode == 28){
        terminal_enter_key_handler();
        cursor();
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
    keyboard_buffer_tail = KEYBOARD_BUFFER_PTR;
    while (1){
        if (keyboard_buffer_tail != KEYBOARD_BUFFER_PTR){
            unsigned char scancode;
            scancode = KEYBOARD_BUFFER[keyboard_buffer_tail];
            terminal_scancode_handler(scancode);
            keyboard_buffer_tail = (keyboard_buffer_tail+1) % KEYBOARD_BUFFER_SIZE;
        }
        sleep(10);
    }
}

void terminal_init(){
    // io_clear();
    terminal_buffer_clear();
    cursor();
    io_cursor_update();
    terminal_keyboard_listen();
}

void _start(void) __attribute__((section(".text.start")));
void _start(){
    terminal_init();
}
