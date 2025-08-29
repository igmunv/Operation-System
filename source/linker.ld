ENTRY(kmain)

SECTIONS
{
  . = 0x5000;
    .os_data : {
        *(.os_data)
    }

  . = 0x10000;

  .text : {
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
}
