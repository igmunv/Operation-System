// Header: start
volatile unsigned char _start_header[16] __attribute__((section(".start_header"))) = {'_','_','_','I','A','M','P','R','O','G','R','A','M','_','_','_'};
// Header: info
volatile unsigned char _info_header[20] __attribute__((section(".info_header"))) = "term2";
// Header: end
volatile unsigned char _end_header[16] __attribute__((section(".end_header"))) = {'_','_','_','E','N','D','P','R','O','G','R','A','M','_','_','_'};

#define TERM_BUFFER_SIZE 1024
#define KEYBOARD_BUFFER_SIZE 16

#include "../../libs/asm.h"
#include "../../libs/shared_memory.h"
#include "../../libs/string.h"
#include "../../libs/io.h"
#include "../../libs/programs.h"


volatile unsigned char keyboard_buffer_tail = 0;
volatile unsigned char term_buffer[TERM_BUFFER_SIZE];
volatile unsigned char term_buffer_ptr = 0;

volatile char term_default_font_color = 7;
volatile char term_default_bckd_color = 0;

volatile char term_prompt_font_color = 2;
volatile char term_prompt_bckd_color = 0;

// Лимит для backspace: до лимита не подняться
volatile unsigned char term_pos_x_limit = 0;
volatile unsigned char term_pos_y_limit = 0;

// Commands
unsigned char cmd_help[5] = "help";
unsigned char cmd_progs[6] = "progs";
unsigned char cmd_progsload[10] = "progsload";
unsigned char cmd_clear[6] = "clear";
unsigned char cmd_poweroff[9] = "poweroff";

// Data for commands
unsigned char* cmd_help_text = "Available commands:\n| [PROGRAM NAME] - run program\n| progs - view programs\n| progsload - load programs from disk\n| clear - clear display\n| poweroff - shutdown system";


// Чистим буффер терминала
void term_buffer_clear(){
    term_buffer[TERM_BUFFER_SIZE] = '\0';
    for(int i = 0; i < TERM_BUFFER_SIZE; i++){
        term_buffer[i] = '\0';
    }
    term_buffer_ptr = 0;
}

// Prompt - приглашение командой строки
void term_prompt(){
    io_printx("> ", DISPLAY_CURSOR_POS_X, DISPLAY_CURSOR_POS_Y, term_prompt_font_color, term_prompt_bckd_color);
    term_pos_x_limit = DISPLAY_CURSOR_POS_X;
    term_pos_y_limit = DISPLAY_CURSOR_POS_Y;
}

// Обработчик команд
void term_command_handler(){
    // Clear
    if (is_str_equally(&cmd_clear, &term_buffer)){
        io_clear();
    }

    // Help
    else if (is_str_equally(&cmd_help, &term_buffer)){
        print(cmd_help_text);
    }

    // Progs
    else if (is_str_equally(&cmd_progs, &term_buffer)){
        print("All programs in disk:");
        for (int i = 1; i < PROGLOADER_PROGRAM_COUNT; i++){
            io_printx(" - ", DISPLAY_CURSOR_POS_X, DISPLAY_CURSOR_POS_Y, term_default_font_color, term_default_bckd_color);
            print(PROGLOADER_PROGRAMS[i].name);
        }
    }

    // ProgsLoad
    else if (is_str_equally(&cmd_progsload, &term_buffer)){
        print("Load programs from disk...");
        programs_load();
        print("Completed!");
    }

    // Poweroff
    else if (is_str_equally(&cmd_poweroff, &term_buffer)){

    }

    // Other
    else{

        // Chech name programs and run
        for (int i = 1; i < PROGLOADER_PROGRAM_COUNT; i++){
            if (is_str_equally(PROGLOADER_PROGRAMS[i].name, &term_buffer)){
                program_run(i);
                return;
            }
        }

        // Unknow command
        print("Command not found!");

    }
}

// Обработчик Enter
void term_enter_key_handler(){
    // Заканчиваем строку
    term_buffer[term_buffer_ptr] = '\0';
    term_buffer_ptr = (term_buffer_ptr+1) % TERM_BUFFER_SIZE;
    // Новая линия для вывода команды
    io_new_line();
    // Обрабатываем введенную команду
    if (term_buffer_ptr > 0) term_command_handler();
    // Сброс буфера
    term_buffer_clear();
    // Prompt
    if (EXECUTE_PROGRAM == 0){
        term_prompt();
    }
}

// Обработчик BackSpace
void term_backspace_key_handler(){
    if ((DISPLAY_CURSOR_POS_X > term_pos_x_limit && DISPLAY_CURSOR_POS_Y == term_pos_y_limit) || DISPLAY_CURSOR_POS_Y > term_pos_y_limit){
        io_delete_current_symbol(-1);
        term_buffer_ptr--;
        term_buffer[term_buffer_ptr] = '\0';
    }
}

// Обработчик символов
void term_symbol_key_handler(unsigned char scancode){
    unsigned char symbol = scancode_to_ascii(scancode, KEYBOARD_SHIFT_PRESSED);
    if (symbol != '\0'){

        term_buffer[term_buffer_ptr] = symbol;
        term_buffer_ptr = (term_buffer_ptr+1) % TERM_BUFFER_SIZE;

        io_printx_symbol(symbol, DISPLAY_CURSOR_POS_X, DISPLAY_CURSOR_POS_Y, term_default_font_color, term_default_bckd_color);

        io_cursor_update();

    }
}

// Общий обработчик всех сканкодов
void term_scancode_handler(unsigned char scancode){

    // Enter
    if (scancode == 28){
        term_enter_key_handler();
    }

    // Backspace
    else if (scancode == 14){
        term_backspace_key_handler();
    }

    // Symbols
    else if (is_symbol_scancode(scancode)){
        term_symbol_key_handler(scancode);
    }
}

// Слушаем клавиатуру (буффер клавиатуры)
void term_keyboard_listen(){

    // Обновляем хвост на текущий указатель на эллемент буфера клавиатуры
    keyboard_buffer_tail = KEYBOARD_BUFFER_PTR;

    while(1){

        // Если появилась программа на исполнение
        if (EXECUTE_PROGRAM > 0){
            return;
        }

        // Нажата клавиша
        if (keyboard_buffer_tail != KEYBOARD_BUFFER_PTR){
            unsigned char scancode = KEYBOARD_BUFFER[keyboard_buffer_tail]; // Получаем сканкод
            term_scancode_handler(scancode); // Обрабатываем сканкод
            keyboard_buffer_tail = (keyboard_buffer_tail+1) % KEYBOARD_BUFFER_SIZE; // Обновляем хвост, т.е делаем +1
        }

        // Спим чтобы не лагало
        sleep(10);
    }
}

// Инициализация терминала
void term_init(){
    term_buffer_clear();
    term_prompt();
    term_keyboard_listen();
}


// Entry point
void _start(void) __attribute__((section(".text.start")));
void _start(){
    term_init();
}
