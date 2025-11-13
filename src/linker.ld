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

    . = 0x10000;
    .kernel_loop : {
        *(.kernel_loop)
    }


  /* Основной код и данные ОС */
  . = 0x15000;
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

  . = 0x30000;
    .file_system : {
        *(.file_system)
    }


  /*

  .rodata (Read-Only Data) - константы, строки и любые данные, которые НЕ ИЗМЕНЯЮТСЯ во время работы программы.
  .data (Initialized Data) - переменные, которым присвоено начальное значение.
  .bss (Uninitialized Data) - переменные без начального значение (не инициализированные или инициализированные нулём).

  */


}
