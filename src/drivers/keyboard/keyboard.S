global asm_keyboard_handler

; C-handlers
extern keyboard_handler

section .text

; Keyboard interrupt handler
asm_keyboard_handler:
    pusha
    call keyboard_handler ; C-handler
    popa
    iretd
