#define KEYBOARD_BUFFER_SIZE 16

#define KEYBOARD_SHIFT_SCANCODE 42
#define KEYBOARD_CTRL_SCANCODE 29
#define KEYBOARD_ALT_SCANCODE 56

// Буфер клавиатуры и указатель-счётчик буфера
volatile unsigned char keyboard_buffer[KEYBOARD_BUFFER_SIZE] __attribute__((section(".os_data")));
volatile unsigned char keyboard_buffer_ptr __attribute__((section(".os_data"))) = 0;

// Флаги специальных клавиш
volatile char keyboard_shift_pressed __attribute__((section(".os_data"))) = 0;
volatile char keyboard_ctrl_pressed __attribute__((section(".os_data"))) = 0;
volatile char keyboard_alt_pressed __attribute__((section(".os_data"))) = 0;

// Добавление сканн-кода в буфер клавиатуры (для последующего использования программами)
void keyboard_scancode_add_in_buffer(unsigned char scancode){
    keyboard_buffer[keyboard_buffer_ptr] = scancode;
    keyboard_buffer_ptr = (keyboard_buffer_ptr+1) % KEYBOARD_BUFFER_SIZE;
}


// Возвращает скан-код нажатой клавиши
unsigned char keyboard_get_scancode(){
    unsigned char keyboard_state = inb(0x64);
    if ((keyboard_state & 0b00000001) == 0b00000001) return inb(0x60);
    else return 0;
}


// Проверка на то, специальный ли символ (SHIFT, CTRL, ALT - спец. символы)
char keyboard_is_special_key(unsigned char scancode){
    switch (scancode){
        case KEYBOARD_SHIFT_SCANCODE: return 1;
        case KEYBOARD_CTRL_SCANCODE: return 1;
        case KEYBOARD_ALT_SCANCODE: return 1;
        default: return 0;
    }
}


// Обработчик специальных клавиш (выставляет флаги)
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


// Обрабатывает нажатие клавиши (прерывание)
void keyboard_handler(){

    unsigned char scancode = keyboard_get_scancode();

    if ((scancode & 0b10000000) == 0b10000000){
        // released
        char is_special_key = keyboard_is_special_key(scancode & 0b01111111);
        if (is_special_key) keyboard_special_key_handler(scancode & 0b01111111, 0);

    }
    else{
        // pressed
        char is_special_key = keyboard_is_special_key(scancode & 0b01111111);
        if (is_special_key) keyboard_special_key_handler(scancode & 0b01111111, 1);
        else keyboard_scancode_add_in_buffer(scancode);
    }
    outb(0x20, 0x20);
}
