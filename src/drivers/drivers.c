
extern void asm_tick_handler();
extern void asm_keyboard_handler();

void drivers_init(){
    IDT_reg_handler(32, 0x08, 0x80 | 0x0E, asm_tick_handler);
    IDT_reg_handler(33, 0x08, 0x80 | 0x0E, asm_keyboard_handler);

    PIT_init(1000);
}
