ENTRY(kmain)

SECTIONS
{

  /* Для GRUB */
  .multiboot :{
    *(.multiboot)
  }

  /* Основной код и данные ОС */
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


  /*

  .rodata (Read-Only Data) - константы, строки и любые данные, которые НЕ ИЗМЕНЯЮТСЯ во время работы программы.
  .data (Initialized Data) - переменные, которым присвоено начальное значение.
  .bss (Uninitialized Data) - переменные без начального значение (не инициализированные или инициализированные нулём).

  */


}
