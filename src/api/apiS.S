global api_asm_handler

; C-обработчик прерываний
extern api_handler

section .text

; Обработчик API прерываний
api_asm_handler:
    pusha
    call api_handler ; C-handler
    mov [esp + 0],  eax    ; ret EAX
    mov [esp + 12], ebx    ; ret EBX
    mov [esp + 4],  ecx    ; ret ECX
    mov [esp + 8],  edx    ; ret EDX
    popa
    iretd
