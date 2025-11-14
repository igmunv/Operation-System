global asm_tick_handler

; C-handlers
extern tick_handler

section .text

; PIT interrupt handler
asm_tick_handler:
    pusha
    call tick_handler ; C-handler
    popa
    iretd

