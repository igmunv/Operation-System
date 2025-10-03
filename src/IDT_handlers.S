global asm_tick_handler, asm_keyboard_handler
extern tick_handler, keyboard_handler

section .text

asm_tick_handler:
    pusha
    call tick_handler
    popa
    iretd

asm_keyboard_handler:
    pusha
    call keyboard_handler
    popa
    iretd
