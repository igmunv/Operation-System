global api_asm_display_handler
extern api_display_handler

section .text

api_asm_display_handler:
    pusha
    call api_display_handler
    popa
    iretd
