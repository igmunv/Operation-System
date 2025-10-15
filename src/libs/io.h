#ifndef INCL_LIB_IO
#define INCL_LIB_IO

// Переход на новую строку
void io_new_line();

// Обновить курсор
void io_cursor_update();

// Очистить экран
void io_clear();

// Получить текущий символ
unsigned char io_get_current_symbol(short offset);

// Удалить текущий символ
void io_delete_current_symbol(short offset);

// Вывести символ на экран
void io_printx_symbol(unsigned char symbol, unsigned short x, unsigned short y, unsigned char font_color, unsigned char background_color);

// Вывести строку на экран
void io_printx(unsigned char* string, unsigned short x, unsigned short y, char font_color, char bkgr_color);

// Упрощённый вывод символа в терминал
void print_symbol(unsigned char symbol);

// Упрощённый вывод строки в терминал
void print(unsigned char* text);

// Вывести в виде HEX
void print_hex(char byte);

// Получить ввод пользователя
int input(unsigned char* buffer);

#endif
