ENTRY(kmain)

SECTIONS
{


  /* Для GRUB */
  .multiboot :{
    *(.multiboot)
  }


  /* Специальная память | Special memory */
  . = 0x5000;
    .os_data : {
        *(.os_data)
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

  /* Один стек для программ */
.program_stack 0x60000 : {
    *(.program_stack)
    . = ALIGN(4);
    _program_stack_bottom = .;
    . = . + 0x20000;
    _program_stack_top = .;
}


  /*

  .rodata (Read-Only Data) - константы, строки и любые данные, которые НЕ ИЗМЕНЯЮТСЯ во время работы программы.
  .data (Initialized Data) - переменные, которым присвоено начальное значение.
  .bss (Uninitialized Data) - переменные без начального значение (не инициализированные или инициализированные нулём).

  */


}
