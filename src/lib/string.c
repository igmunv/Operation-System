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

void string_turn_over(unsigned char* string, short size, unsigned char* result){
    for (int i = 0; i < size; i++){
        result[i] = string[size-i-1];
    }
    result[size] = '\0';
}

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

char is_digit(char* string){
    for (char i = 0; i < 100; i++){
        char symbol = string[i];
        if (symbol == '\0') break;
        switch (symbol){
            case '0': continue;
            case '1': continue;
            case '2': continue;
            case '3': continue;
            case '4': continue;
            case '5': continue;
            case '6': continue;
            case '7': continue;
            case '8': continue;
            case '9': continue;
            default: return 0;
        }
    }
    return 1;
}

short strlen(char* string){
    short len = 0;
     for (char i = 0; i < 100; i++){
        char symbol = string[i];
        if (symbol == '\0') break;
        len++;
    }
    return len;
}

char is_str_equally(unsigned char* str1, short str1_len, unsigned char* str2){
    for (short n = 0; n <= str1_len; n++){
        unsigned char str1_sym = str1[n];
        unsigned char str2_sym = str2[n];
        unsigned char xor = str1_sym ^ str2_sym;
        if (xor != 0 ) return 0;
    }
    return 1;
}

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

char stoi(char* string, int* result){
    if (!is_digit(string)){
        return 0;
    }
    int i_result = 0;
    int umn = 1;
    short len = strlen(string);
    for (char i = len-1; i >= 0; i--){
        char symbol = string[i];
        char digit = smtoi(symbol);
        i_result = (digit * umn) + i_result;
        umn *= 10;
    }
}

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

struct byte_split_struct{
    char low;
    char high;
};

// byte to hex (string) format
void btox(char byte, struct byte_split_struct* result){
    char low = byte & 0b00001111;
    char high = (byte >> 4) & 0b00001111;
    result->low = btox_table(low);
    result->high = btox_table(high);
}

// pointer to hex (string) format
// size = 8 (32 bit system)
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
