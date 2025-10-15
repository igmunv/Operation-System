#ifndef INCL_LIB_STRING
#define INCL_LIB_STRING


// Разделенный байт на: Младшие 4 бита и Старшие 4 бита
struct byte_split_struct{
    char low;
    char high;
};


// Перевернуть строку
void string_turn_over(unsigned char* string, short size, unsigned char* result);

// Int to string. Число в строку
void itos(long i, unsigned char* ret);

// Проверка строки на то, является ли она числом
char is_digit(char* string);

// Получить размер строки
int strlen(char* string);

// Сравнение строк. Если одинаковые то 1, если разные то 0
char is_str_equally(unsigned char* str1, short str1_len, unsigned char* str2);

// String to int. Строку в число
int stoi(char* string, int* result);

// Byte to hex. Байт в HEX строку (16-чный вид, строка)
void btox(char byte, struct byte_split_struct* result);

// Pointer to hex. Адрес в HEX строку (16-чный вид, строка)
void ptox(void* ptr, unsigned char* result);

// Возвращает символ ASCII по таблице исходя из скан-кода клавиши
char scancode_to_ascii(unsigned char scancode, unsigned char shift_state);


#endif
