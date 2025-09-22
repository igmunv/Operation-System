use16
org 0x7c00

start:
	mov ax, cs ; вся адресация идет через сегменты
	mov ds, ax ; выставляем их одинаковыми
	mov ss, ax ; чтобы не путаться

	mov sp, start ; устанавливаем стек

	jmp read_disk

gdt:
	db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ; нулевой дескриптор (по стандарту)
	db 0xff, 0xff, 0x00, 0x00, 0x00, 0x9A, 0xCF, 0x00 ; сегмент кода (0x9A - код доступен, выполняемый)
	db 0xff, 0xff, 0x00, 0x00, 0x00, 0x92, 0xCF, 0x00 ; сегмент данных (0x92 - данные доступны, для чтения/записи)
gdt_info:
	dw gdt_info - gdt
	dw gdt, 0 ; создаётся два слова: адрес gdt и 0

read_disk:
	; читаем 20 секторов с диска в память по адресу 0x1000:0x0000
	mov ax, 0x1000
	mov es, ax
	mov bx, 0x00
	mov ah, 0x02
	mov dl, 0x01
	mov dh, 0x00
	mov ch, 0x00
	mov al, 20
	mov cl, 0x01
	int 0x13

	jmp kernel

kernel:

	cli ; запрет прерываний
	lgdt [gdt_info] ; загружаем таблицу прерываний

	; включаем A20 линию (чтобы видеть память выше 1МБ)
	in al, 0x92 ; читаем из 0x92
	or al, 2 ; логическое ИЛИ (результат в al)
	out 0x92, al ; отправляем на 0x92 al

	; включаем Protected Mode
	mov eax, cr0
	or al, 1
	mov cr0, eax

	jmp 0x8:protected_mode ; 'far jump' в защищенный режим

use32
protected_mode:
	mov ax, 0x10 ; это сегмент данных (gdt entry)
	mov es, ax
	mov ds, ax
	mov ss, ax
	call 0x10000 ; вызов ядра



times (512 - ($ - start) - 2) db 0
db 0x55, 0xAA
