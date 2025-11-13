global outb, outw, outl, inb, inw, inl, in_out_wait

global in_ah, in_al, in_bh, in_bl, in_ch, in_cl, in_dh, in_dl
global in_ax, in_bx, in_cx, in_dx, in_si
global in_ebx, in_edx, in_esi

global get_ah, get_al, get_bh, get_bl, get_ch, get_cl, get_dh, get_dl
global get_ax, get_bx, get_cx, get_dx, get_si
global get_ebx, get_edx, get_esi

global clear_ah, clear_al, clear_bh, clear_bl, clear_ch, clear_cl, clear_dh, clear_dl
global clear_ax, clear_bx, clear_cx, clear_dx

section .text


outb:
    push    ebp
    mov     ebp, esp
    ; [ebp+8] = port (16-bit)
    ; [ebp+12] = byte (8-bit)
    mov     dx, WORD [ebp+8]
    mov     al,  BYTE [ebp+12]
    out     dx, al
    pop     ebp
    ret

outw:
    push    ebp
    mov     ebp, esp
    mov     dx, WORD [ebp+8]
    mov     ax, WORD [ebp+12]
    out     dx, ax
    pop     ebp
    ret

outl:
    push    ebp
    mov     ebp, esp
    ; [ebp+8] = port (16-bit)
    ; [ebp+12] = byte (8-bit)
    mov     dx, WORD [ebp+8]
    mov     eax,  DWORD [ebp+12]
    out     dx, eax
    pop     ebp
    ret

inb:
    push    ebp
    mov     ebp, esp
    mov     dx, WORD [ebp+8]
    xor     eax, eax
    in      al, dx
    pop     ebp
    ret

inw:
    push    ebp
    mov     ebp, esp
    mov     dx, WORD [ebp+8]
    xor     eax, eax
    in      ax, dx
    pop     ebp
    ret

inl:
    push    ebp
    mov     ebp, esp
    mov     dx, WORD [ebp+8]
    xor     eax, eax
    in      eax, dx
    pop     ebp
    ret

in_out_wait:
    mov dx, 0x80
    mov ax, 0
    out dx, ax



; Write 8-bit registers

in_ah:
    mov ah, [esp+4]
    ret

in_al:
    mov al, [esp+4]
    ret

in_bh:
    mov bh, [esp+4]
    ret

in_bl:
    mov bl, [esp+4]
    ret

in_ch:
    mov ch, [esp+4]
    ret

in_cl:
    mov cl, [esp+4]
    ret

in_dh:
    mov dh, [esp+4]
    ret

in_dl:
    mov dl, [esp+4]
    ret

; Write 16-bit registers

in_ax:
    mov ax, [esp+4]
    ret

in_bx:
    mov bx, [esp+4]
    ret

in_cx:
    mov cx, [esp+4]
    ret

in_dx:
    mov dx, [esp+4]
    ret

in_si:
    mov si, [esp+4]
    ret

; Write 32-bit registers

in_ebx:
    mov ebx, [esp+4]
    ret

in_edx:
    mov edx, [esp+4]
    ret

in_esi:
    mov esi, [esp+4]
    ret

; Read 8-bit registers

get_ah:
    movzx eax, ah
    ret

get_al:
    movzx eax, al
    ret

get_bh:
    movzx eax, bh
    ret

get_bl:
    movzx eax, bl
    ret

get_ch:
    movzx eax, ch
    ret

get_cl:
    movzx eax, cl
    ret

get_dh:
    movzx eax, dh
    ret

get_dl:
    movzx eax, dl
    ret

; Read 16-bit registers

get_ax:
    movzx eax, ax
    ret

get_bx:
    movzx eax, bx
    ret

get_cx:
    movzx eax, cx
    ret

get_dx:
    movzx eax, dx
    ret

get_si:
    movzx eax, si
    ret

; Read 32-bit registers

get_ebx:
    mov eax, ebx
    ret

get_edx:
    mov eax, edx
    ret

get_esi:
    mov eax, esi
    ret

; Clear 8-bit registers

clear_ah:
    xor ah, ah
    ret

clear_al:
    xor al, al
    ret

clear_bh:
    xor bh, bh
    ret

clear_bl:
    xor bl, bl
    ret

clear_ch:
    xor ch, ch
    ret

clear_cl:
    xor cl, cl
    ret

clear_dh:
    xor dh, dh
    ret

clear_dl:
    xor dl, dl
    ret

; Clear 16-bit registers

clear_ax:
    xor ax, ax
    ret

clear_bx:
    xor bx, bx
    ret

clear_cx:
    xor cx, cx
    ret

clear_dx:
    xor dx, dx
    ret
