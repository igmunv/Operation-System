global api_asm_display_handler

; C-обработчик прерываний
extern api_display_handler


section .text


; Обработик API прерываний
api_asm_display_handler:
    pusha
    call api_display_handler ; C-handler
    popa
    iretd
