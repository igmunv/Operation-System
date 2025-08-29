#define KEYBOARD_BUFFER_SIZE 16

#define KEYBOARD_SHIFT_SCANCODE 42
#define KEYBOARD_CTRL_SCANCODE 29
#define KEYBOARD_ALT_SCANCODE 56

volatile char keyboard_shift_pressed = 0;
volatile char keyboard_ctrl_pressed = 0;
volatile char keyboard_alt_pressed = 0;

volatile unsigned char keyboard_buffer[KEYBOARD_BUFFER_SIZE]; __attribute__((section(".os_data")));
volatile unsigned char keyboard_buffer_ptr = 0; __attribute__((section(".os_data")));

void keyboard_scancode_add_in_buffer(unsigned char scancode){
    keyboard_buffer[keyboard_buffer_ptr] = scancode;
    keyboard_buffer_ptr = (keyboard_buffer_ptr+1) % KEYBOARD_BUFFER_SIZE;
}

unsigned char keyboard_get_scancode(){ // возвращает скан код нажатой клавиши
    unsigned char keyboard_state = inb(0x64);
    if ((keyboard_state & 0b00000001) == 0b00000001) return inb(0x60);
    else return 0;
}

char keyboard_is_special_key(unsigned char scancode){
    switch (scancode){
        case KEYBOARD_SHIFT_SCANCODE: return 1;
        case KEYBOARD_CTRL_SCANCODE: return 1;
        case KEYBOARD_ALT_SCANCODE: return 1;
        default: return 0;
    }
}

char keyboard_special_key_handler(unsigned char scancode, char state){
    if ((scancode) == KEYBOARD_SHIFT_SCANCODE){
        keyboard_shift_pressed = state;
    }
    else if ((scancode) == KEYBOARD_CTRL_SCANCODE){
        keyboard_ctrl_pressed = state;
    }
    else if ((scancode) == KEYBOARD_ALT_SCANCODE){
        keyboard_alt_pressed = state;
    }
}

void keyboard_handler(){
    unsigned char scancode = keyboard_get_scancode();

    if ((scancode & 0b10000000) == 0b10000000){
        // released
        char is_special_key = keyboard_is_special_key(scancode & 0b01111111);
        if (is_special_key) keyboard_special_key_handler(scancode & 0b01111111, 0);

    }
    else{
        //unsigned char ascii = keyboard_scancode_to_ascii(scancode);
        char is_special_key = keyboard_is_special_key(scancode & 0b01111111);
        if (is_special_key) keyboard_special_key_handler(scancode & 0b01111111, 1);
        else keyboard_scancode_add_in_buffer(scancode);
    }
    outb(PIC1_PORT, 0x20);
}

char keyboard_scancode_to_ascii(unsigned char scancode, unsigned char shift_state){ // возвращает символ ASCII по таблице

    if (shift_state){

        // - - SHIFT - -

        switch (scancode){

            // numbers
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

            // bukvi
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

            // special symbols
            case 12: return '_';
            case 13: return '+';
            case 26: return '{';
            case 27: return '}';
            case 39: return ':';
            case 40: return '"';
            case 51: return '<';
            case 52: return '>';
            case 53: return '?';

            // special keys
            case 57: return ' '; // space

            default: return '\0';
        }

    }
    else{

        // - - ALONE - -

        switch (scancode){

            // numbers
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

            // bukvi
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

            // special symbols
            case 12: return '-';
            case 13: return '=';
            case 26: return '[';
            case 27: return ']';
            case 39: return ';';
            case 40: return '\'';
            case 51: return ',';
            case 52: return '.';
            case 53: return '/';

            // special keys
            case 57: return ' '; // space

            default: return '\0';
        }
    }
}
