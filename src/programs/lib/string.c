

// Возвращает символ (цифру), соответствующий цифре
unsigned char itos_table(char i){
    switch (i){
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        default: return '\0';
    }
}


// Перевернуть строку
void string_turn_over(unsigned char* string, short size, unsigned char* result){
    for (int i = 0; i < size; i++){
        result[i] = string[size-i-1];
    }
    result[size] = '\0';
}


// Int to string. Число в строку
void itos(long i, unsigned char* ret){
    long j = i;
    unsigned char result[21];
    char r_ptr = 0;

     if (i == 0){
         ret[0] = '0';
         ret[1] = '\0';
         return;
    }

    char string[20];
    char s_ptr = 0;

    if (i < 0) i = i * -1;

    while (i){
        int p = (long)(i % 10);
        i = (long)(i / 10);
        unsigned char s = itos_table(p);

        string[s_ptr] = s;
        s_ptr++;
    }

    string_turn_over(&string, s_ptr, &result);

    if (j < 0){
        ret[0] = '-';

        for (int f = 0; f < 21; f++){
            ret[f+1] = result[f];
        }
    }
    else{
         for (int f = 0; f < 21; f++){
            ret[f] = result[f];
        }
    }
    return;
}


// Проверка строки на то, является ли она числом
char is_digit(char* string){
    // пустая строка
    if(string[0] == '\0') return 0;
    // бегаем пока не конец строки
    for (int i = 0; string[i] != '\0'; i++){
        char symbol = string[i];
        // если вдруг отрицательное, то корректная проверка
        if (i == 0 && symbol == '-' && string[i+1] != '\0') continue;
        // проверка на то, входит ли символ в диапазон цифр
        if (symbol < '0' || symbol > '9'){
            return 0; // not digit
        }
    }
    return 1; // is digit
}


// Получить размер строки
int strlen(char* string){
    int len = 0;
     for (int i = 0; string[i] != '\0'; i++){
        len++;
    }
    return len;
}


// Сравнение строк. Если одинаковые то 1, если разные то 0
char is_str_equally(unsigned char* str1, short str1_len, unsigned char* str2){
    for (short n = 0; n <= str1_len; n++){
        unsigned char str1_sym = str1[n];
        unsigned char str2_sym = str2[n];
        unsigned char xor = str1_sym ^ str2_sym;
        if (xor != 0 ) return 0;
    }
    return 1;
}


// Возвращает число, соответствующее символу (цифре)
char smtoi(char symbol){
    switch (symbol){
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default: return 0;
    }
}


// String to int. Строку в число
int stoi(char* string, int* result){
    if (!is_digit(string)){
        return 0;
    }

    char minus = 0;
    if (string[0] == '-') minus = 1;

    int i_result = 0;
    int umn = 1;
    short len = strlen(string);
    for (int i = len-1; i >= minus; i--){
        char symbol = string[i];
        char digit = smtoi(symbol);
        i_result = (digit * umn) + i_result;
        umn *= 10;
    }
    if (minus) i_result *= -1;
    *result = i_result;
    return 1;
}


// Возвращает HEX строку, соответствующее числу
char btox_table(char byte){
    switch(byte){
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default: return 0;
    }
}


// Разделенный байт на: Младшие 4 бита и Старшие 4 бита
struct byte_split_struct{
    char low;
    char high;
};


// Byte to hex. Байт в HEX строку (16-чный вид, строка)
void btox(char byte, struct byte_split_struct* result){
    char low = byte & 0b00001111;
    char high = (byte >> 4) & 0b00001111;
    result->low = btox_table(low);
    result->high = btox_table(high);
}


// Pointer to hex. Адрес в HEX строку (16-чный вид, строка)
void ptox(void* ptr, unsigned char* result){
    char hp_num = 7;
    for (char i = 0; i < 4; i++){

        struct byte_split_struct btox_result;
        long p = ptr;
        btox(p >> (i*8), &btox_result);

        result[hp_num] = btox_result.low;
        hp_num--;
        result[hp_num] = btox_result.high;
        hp_num--;

    }
}


// Возвращает символ ASCII по таблице исходя из скан-кода клавиши
char scancode_to_ascii(unsigned char scancode, unsigned char shift_state){

    if (shift_state){

        // - - SHIFT - -

        switch (scancode){

            // Numbers
            case 2: return '!';
            case 3: return '@';
            case 4: return '#';
            case 5: return '$';
            case 6: return '%';
            case 7: return '^';
            case 8: return '&';
            case 9: return '*';
            case 10: return '(';
            case 11: return ')';

            // Letters
            case 16: return 'Q';
            case 17: return 'W';
            case 18: return 'E';
            case 19: return 'R';
            case 20: return 'T';
            case 21: return 'Y';
            case 22: return 'U';
            case 23: return 'I';
            case 24: return 'O';
            case 25: return 'P';

            case 30: return 'A';
            case 31: return 'S';
            case 32: return 'D';
            case 33: return 'F';
            case 34: return 'G';
            case 35: return 'H';
            case 36: return 'J';
            case 37: return 'K';
            case 38: return 'L';

            case 44: return 'Z';
            case 45: return 'X';
            case 46: return 'C';
            case 47: return 'V';
            case 48: return 'B';
            case 49: return 'N';
            case 50: return 'M';

            // Special symbols
            case 12: return '_';
            case 13: return '+';
            case 26: return '{';
            case 27: return '}';
            case 39: return ':';
            case 40: return '"';
            case 51: return '<';
            case 52: return '>';
            case 53: return '?';

            // Special keys
            case 57: return ' '; // Space

            default: return '\0'; // If different, then 0
        }

    }
    else{

        // - - WITHOUT SHIFT - -

        switch (scancode){

            // Numbers
            case 2: return '1';
            case 3: return '2';
            case 4: return '3';
            case 5: return '4';
            case 6: return '5';
            case 7: return '6';
            case 8: return '7';
            case 9: return '8';
            case 10: return '9';
            case 11: return '0';

            // Letters
            case 16: return 'q';
            case 17: return 'w';
            case 18: return 'e';
            case 19: return 'r';
            case 20: return 't';
            case 21: return 'y';
            case 22: return 'u';
            case 23: return 'i';
            case 24: return 'o';
            case 25: return 'p';

            case 30: return 'a';
            case 31: return 's';
            case 32: return 'd';
            case 33: return 'f';
            case 34: return 'g';
            case 35: return 'h';
            case 36: return 'j';
            case 37: return 'k';
            case 38: return 'l';

            case 44: return 'z';
            case 45: return 'x';
            case 46: return 'c';
            case 47: return 'v';
            case 48: return 'b';
            case 49: return 'n';
            case 50: return 'm';

            // Special symbols
            case 12: return '-';
            case 13: return '=';
            case 26: return '[';
            case 27: return ']';
            case 39: return ';';
            case 40: return '\'';
            case 51: return ',';
            case 52: return '.';
            case 53: return '/';

            // Special keys
            case 57: return ' '; // Space

            default: return '\0'; // If different, then 0
        }
    }
}
