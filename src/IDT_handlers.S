global tick_handler, asm_keyboard_handler
extern tick, keyboard_handler

section .text

tick_handler:
    pusha
    call tick
    popa
    iretd

asm_keyboard_handler:
    pusha
    call keyboard_handler
    popa
    iretd
