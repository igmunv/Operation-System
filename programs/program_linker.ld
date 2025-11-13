ENTRY(_start)

SECTIONS
{

    /* Заголовок начала программы */
    . = 0x30000;
    .start_header : {
        *(.start_header)
    }
    .info_header : ALIGN(1) {
        *(.info_header)
    }

    .text : {
        *(.text.start)
        *(.text)
    }
    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
        *(COMMON)
    }

    /* Заголовок конца программы */
    .end_header : {
        *(.end_header)
    }

}
