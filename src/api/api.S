global api_asm_display_handler, api_asm_ata_handler, api_asm_execute_handler

; C-обработчик прерываний
extern api_display_handler, api_ata_handler, api_execute_handler


section .text


; Обработчик API прерываний дисплея
api_asm_display_handler:
    pusha
    call api_display_handler ; C-handler
    popa
    iretd

; Обработчик API прерываний ATA
api_asm_ata_handler:
    pusha
    call api_ata_handler ; C-handler
    popa
    iretd

; Обработчик API прерываний ATA
api_asm_execute_handler:
    pusha
    call api_execute_handler ; C-handler
    popa
    iretd
