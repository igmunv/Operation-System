global gdt_init

section .data
gdt:
    ; Нулевой дескриптор (не используется)
    dd 0x00000000
    dd 0x00000000
    ; Сегмент кода (для привилегий 0, 32-битный)
    dd 0x0000FFFF
    dd 0x00CF9A00
    ; Сегмент данных (для привилегий 0, 32-битный)
    dd 0x0000FFFF
    dd 0x00CF9200

gdt_info:
    dw gdt_info - gdt - 1   ; Размер GDT (должен быть на 1 меньше)
    dd gdt                  ; Адрес GDT (32-битный)

section .text
gdt_init:
    lgdt [gdt_info]         ; Загружаем GDT

    ; Перезагружаем сегментные регистры
    mov ax, 0x10            ; Селектор сегмента данных
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Делаем дальний прыжок для обновления CS
    jmp 0x08:.reload_cs     ; 0x08 - селектор кода
.reload_cs:
    ret
