
global asm_progloader_run

section .data

oldesp: dd 0
oldebp: dd 0
oldflags: dd 0

section .text

asm_progloader_run:

    ; asm_progloader_run(void* newesp, void* address)

    mov ebx, [esp+4] ; new esp
    mov ecx, [esp+8] ; _start address

    pushfd
    pop eax
    mov [oldflags], eax

    mov [oldesp], esp
    mov [oldebp], ebp

    and ebx, 0xFFFFFFF0
    sub ebx, 16

    mov esp, ebx
    mov ebp, ebx

    sti

    call ecx

    cli

    mov esp, [oldesp]
    mov ebp, [oldebp]

    mov eax, [oldflags]
    push eax
    popfd

    ret
