# Внутренний API для компонентов ядра

## Детали

Чтобы использовать API нужно подключить заголовочный файл [src/api/kernel_functions.h](../../src/api/kernel_functions.h)

Обратите внимание: перед именами API-функций в коде всегда используется символ `_` (в документации он опущен)


## Таблица функций

|                                          Name                                          | Description                                 |
| :------------------------------------------------------------------------------------: | :------------------------------------------ |
| [print_text](internal_functions.md#print_text)                  | Вывод текста                                |
| [new_line](internal_functions.md#new_line)                    | Переход на следующую строку                 |
| [cursor_update](internal_functions.md#cursor_update)               | Обновить курсор                             |
| [clear_display](internal_functions.md#clear_display)               | Очистить дисплей                            |
| [get_current_symbol](internal_functions.md#get_current_symbol)          | Получить текущий символ                     |
| [delete_current_symbol](internal_functions.md#delete_current_symbol)       | Удалить текущий символ                      |
| [read_sector](internal_functions.md#read_sector)                | Читать определённый сектор диска            |
| [write_sector](internal_functions.md#write_sector)               | Записать в определённый сектор диска        |
| [execute_program](internal_functions.md#execute_program)            | Указать следующую программу для исполнения  |
| [get_execute_program](internal_functions.md#get_execute_program)        | Получить следующую программу для исполнения |
| [get_keyboard_buffer](internal_functions.md#get_keyboard_buffer)        | Получить адрес буфера клавиатуры            |
| [get_keyboard_buffer_ptr](internal_functions.md#get_keyboard_buffer_ptr)    | Получить текущий индекс буфера клавиатуры   |
| [get_keyboard_shift_pressed](internal_functions.md#get_keyboard_shift_pressed) | Флаг: нажата ли клавиша Shift               |
| [get_keyboard_ctrl_pressed](internal_functions.md#get_keyboard_ctrl_pressed)  | Флаг: нажата ли клавиша Ctrl                |
| [get_keyboard_alt_pressed](internal_functions.md#get_keyboard_alt_pressed)   | Флаг: нажата ли клавиша Alt                 |
| [get_display_cursor_pos_x](internal_functions.md#get_display_cursor_pos_x)   | Позиция курсора по X                        |
| [get_display_cursor_pos_y](internal_functions.md#get_display_cursor_pos_y)   | Позиция курсора по Y                        |
| [get_ticks](internal_functions.md#get_ticks)                  | Количество тиков с момента запуска          |
| [get_device_count](internal_functions.md#get_device_count)           | Количество устройств                        |
| [get_device_info](internal_functions.md#get_device_info)            | Адрес массива структур устройств            |
| [set_display_cursor_pos_x](internal_functions.md#set_display_cursor_pos_x)   | Задать положение X                          |
| [set_display_cursor_pos_y](internal_functions.md#set_display_cursor_pos_y)   | Задать положение Y                          |
| [int_reg_handler](internal_functions.md#int_reg_handler)   | Зарегестрировать обработчик для прерывания |
| [pic_update_mask](internal_functions.md#pic_update_mask)   | Обновить маску PCI |
| [intr_enable](internal_functions.md#intr_enable)   | Включить/разрешить прерывания |
| [intr_disable](internal_functions.md#intr_disable)   | Выключить/запретить прерывания |
