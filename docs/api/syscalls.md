# Системные вызовы

## Детали

Системный вызов выполняется посредством генерации программного прерывания `0x22`

Следующие регистры используются для передачи аргументов:

| Register  | Description  |
| :-------------: | :------------- |
| `EAX`  | Номер системного вызова  |
| `EBX`  | 1-й аргумент  |
| `ECX`  | 2-й аргумент  |
| `EDX`  | 3-й аргумент  |
| `ESI`  | 4-й аргумент  |
| `EDI`  | 5-й аргумент  |
| `EAX`  | Возвращаемое значение  |

## Таблица системных вызовов

| Number  | Name  | Description  |
| :-------------: | :------------- | :------------- |
| `0x0`     |    [print_text](syscall_functions.md#print_text)  |                                    Вывод текста |
| `0x1`     |    [new_line](syscall_functions.md#new_line)  |                                        Переход на следующую строку |
| `0x2`     |    [cursor_update](syscall_functions.md#cursor_update)  |                              Обновить курсор |
| `0x3`     |    [clear_display](syscall_functions.md#clear_display)  |                              Очистить дисплей |
| `0x4`     |    [get_current_symbol](syscall_functions.md#get_current_symbol)  |                    Получить текущий символ |
| `0x5`     |    [delete_current_symbol](syscall_functions.md#delete_current_symbol)  |              Удалить текущий символ |
| `0x10`    |    [read_sector](syscall_functions.md#read_sector)  |                                  Читать определённый сектор диска |
| `0x11`    |    [write_sector](syscall_functions.md#write_sector)  |                                Записать в определённый сектор диска |
| `0x50`    |    [execute_program](syscall_functions.md#execute_program)  |                          Указать следующую программу для исполнения |
| `0x100`   |    [get_execute_program](syscall_functions.md#get_execute_program)  |                  Получить следующую программу для исполнения |
| `0x101`   |    [get_keyboard_buffer](syscall_functions.md#get_keyboard_buffer)  |                  Получить адрес буффера клавиатуры |
| `0x102`   |    [get_keyboard_buffer_ptr](syscall_functions.md#get_keyboard_buffer_ptr)  |          Получить текущий индекс (текущее положение) буфера клавиатуры |
| `0x103`   |    [get_keyboard_shift_pressed](syscall_functions.md#get_keyboard_shift_pressed)  |    Получить флаг: нажата ли клавиша Shift |
| `0x104`   |    [get_keyboard_ctrl_pressed](syscall_functions.md#get_keyboard_ctrl_pressed)  |      Получить флаг: нажата ли клавиша Ctrl |
| `0x105`   |    [get_keyboard_alt_pressed](syscall_functions.md#get_keyboard_alt_pressed)  |        Получить флаг: нажата ли клавиша Alt |
| `0x106`   |    [get_display_cursor_pos_x](syscall_functions.md#get_display_cursor_pos_x)  |        Получить позицию курсора по координате X |
| `0x107`   |    [get_display_cursor_pos_y](syscall_functions.md#get_display_cursor_pos_y)  |        Получить позицию курсора по координате Y |
| `0x108`   |    [get_ticks](syscall_functions.md#get_ticks)  |                                      Получить количество тиков с момента запуска системы |
| `0x109`   |    [get_device_count](syscall_functions.md#get_device_count)  |                        Получить количество устройств |
| `0x10A`   |    [get_device_info](syscall_functions.md#get_device_info)  |                          Получить адрес массива структур устройств |
| `0x200`   |    [set_display_cursor_pos_x](syscall_functions.md#set_display_cursor_pos_x)  |        Задать положение координаты X |
| `0x201`   |    [set_display_cursor_pos_y](syscall_functions.md#set_display_cursor_pos_y)  |        Задать положение координаты Y |

