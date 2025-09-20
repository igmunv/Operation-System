
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
}

void itos(long i, unsigned char* ret){
    unsigned char result[21];
    char r_ptr = 0;

     if (i == 0){
         ret[0] = '0';
         ret[1] = '\0';
         return;
    }

    char string[20];
    char s_ptr = 0;

    if (i < 0){
        i = i * -1;
        result[0] = '-';
        r_ptr++;
    }

    while (i){
        int p = (long)(i % 10);
        i = (long)(i / 10);
        unsigned char s = itos_table(p);
        string[s_ptr] = s;
        s_ptr++;
    }

    unsigned char str_to[20];
    string_turn_over(&string, s_ptr+1, &str_to);

    for (char f = 0; f < 20; f++){
        result[f+1] = str_to[f];
    }
    ret = result;
    return;
}
