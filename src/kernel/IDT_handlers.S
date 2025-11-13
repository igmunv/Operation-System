global asm_tick_handler, asm_keyboard_handler

; C-handlers
extern tick_handler, keyboard_handler

section .text

; PIT interrupt handler
asm_tick_handler:
    pusha
    call tick_handler ; C-handler
    popa
    iretd

; Keyboard interrupt handler
asm_keyboard_handler:
    pusha
    call keyboard_handler ; C-handler
    popa
    iretd
