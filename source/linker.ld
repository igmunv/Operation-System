ENTRY(_start)

SECTIONS {
  . = 1M;

  .text : {
    *(.multiboot)
    *(.text*)
  }

  .data : {
    *(.data*)
  }

  .bss : {
    *(.bss*)
  }
}