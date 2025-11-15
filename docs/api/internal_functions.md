# Функции внутреннего API ядра

## Display

### print_text

**Описание:** Вывод текста

**Сигнатура**:
```
void _print_text(unsigned char* text, unsigned int size, unsigned char x, unsigned char y, unsigned int color, unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `text`  | Адрес строки |
| `size`  | Количество байт |
| `x`  | X |
| `y`  | Y |
| `color`  | Цвета символов: младший байт — цвет текста, старший байт — цвет фона |
| `device_index`  | Индекс устройства |

**Возвращает:** None

---

### new_line

**Описание:** Переход на следующую строку

**Сигнатура**:
```
void _new_line(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** None

---

### cursor_update

**Описание:** Обновить курсор. Перемещает курсор на текущие координаты x и y

**Сигнатура**:
```
void _cursor_update(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** None

---

### clear_display

**Описание:** Очистить дисплей

**Сигнатура**:
```
void _clear_display(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** None

---

### get_current_symbol

**Описание:** Получить текущий символ на экране. Получает символ, на который указывают координаты x и y. Можно задать смещение

**Сигнатура**:
```
unsigned char _get_current_symbol(unsigned int offset, unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `offset`  | Смещение относительно текущей позиции |
| `device_index`  | Индекс устройства |

**Возвращает:** Символ

---

### delete_current_symbol

**Описание:** Удалить текущий символ на экране. Удаляет символ, на который указывают координаты x и y. Можно задать смещение

**Сигнатура**:
```
unsigned char _delete_current_symbol(unsigned int offset, unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `offset`  | Смещение относительно текущей позиции |
| `device_index`  | Индекс устройства |

**Возвращает:** Удалённый символ

---

### get_display_cursor_pos_x

**Описание:** Получить позицию курсора по координате X

**Сигнатура**:
```
unsigned char _get_display_cursor_pos_x(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** Позиция курсора по X

---

### get_display_cursor_pos_y

**Описание:** Получить позицию курсора по координате Y

**Сигнатура**:
```
unsigned char _get_display_cursor_pos_y(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** Позиция курсора по Y

---

### set_display_cursor_pos_x

**Описание:** Установить позицию курсора по координате X

**Сигнатура**:
```
void _set_display_cursor_pos_x(unsigned char x, unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `x`  | Позиция курсора по X |
| `device_index`  | Индекс устройства |

**Возвращает:** None

---

### set_display_cursor_pos_y

**Описание:** Установить позицию курсора по координате Y

**Сигнатура**:
```
void _set_display_cursor_pos_y(unsigned char y, unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `y`  | Позиция курсора по Y |
| `device_index`  | Индекс устройства |

**Возвращает:** None

---

## Keyboard

### get_keyboard_buffer

**Описание:** Получить адрес буффера клавиатуры

**Сигнатура**:
```
void* _get_keyboard_buffer(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** Адрес буффера клавиатуры

---

### get_keyboard_buffer_ptr

**Описание:** Получить текущий индекс (текущее положение) буфера клавиатуры

**Сигнатура**:
```
unsigned int _get_keyboard_buffer_ptr(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** Текущий индекс буфера клавиатуры

---

### get_keyboard_shift_pressed

**Описание:** Получить флаг: нажата ли клавиша Shift

**Сигнатура**:
```
unsigned char _get_keyboard_shift_pressed(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** 0 - не нажата, 1 - нажата

---

### get_keyboard_ctrl_pressed

**Описание:** Получить флаг: нажата ли клавиша Ctrl

**Сигнатура**:
```
unsigned char _get_keyboard_ctrl_pressed(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** 0 - не нажата, 1 - нажата

---

### get_keyboard_alt_pressed

**Описание:** Получить флаг: нажата ли клавиша Alt

**Сигнатура**:
```
unsigned char _get_keyboard_alt_pressed(unsigned int device_index);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |

**Возвращает:** 0 - не нажата, 1 - нажата

---

## Storage

### read_sector

**Описание:** Читать определённый сектор с диска

**Сигнатура**:
```
unsigned char _read_sector(unsigned int device_index, unsigned int lba, void* dst);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |
| `lba`  | Номер сектора |
| `dst`  | Адрес куда читать (размер 512 байт) |

**Возвращает:** 0 - не нажата, 1 - нажата

---

### write_sector

**Описание:** Записать в определённый сектор диска

**Сигнатура**:
```
unsigned char _write_sector(unsigned int device_index, unsigned int lba, void* src);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `device_index`  | Индекс устройства |
| `lba`  | Номер сектора |
| `src`  | Адрес откуда читать (размер 512 байт) |

**Возвращает:** 0 - не нажата, 1 - нажата

---

## Scheduler

### execute_program

**Описание:** Указать номер следующей программы для исполнения

**Сигнатура**:
```
void _execute_program(unsigned int program);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `program`  | Номер программы |

**Возвращает:** None

---

### get_execute_program

**Описание:** Получить номер следующей программы для исполнения

**Сигнатура**:
```
unsigned int _get_execute_program();
```

**Аргументы:** None

**Возвращает:** Номер программы

---

## Interrupts

### int_reg_handler

**Описание:** Зарегестрировать обработчик для прерывания

**Сигнатура**:
```
void _int_reg_handler(int number, unsigned short segm_sel, unsigned short flags, intr_handler handler);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `number`  | Номер прерывания |
| `segm_sel`  | Сегмент |
| `flags`  | Флаги |
| `handler`  | Функция-обработчик |

**Возвращает:** None

---

### pic_update_mask

**Описание:** Обновить маску PCI

**Сигнатура**:
```
void _pic_update_mask(unsigned char mst_sl, unsigned char bit, unsigned char value);
```

**Аргументы:**
| Name  | Description  |
| :-------------: | :------------- |
| `mst_sl`  | 0 - Master, 1 - Slave |
| `bit`  | Номер бита |
| `value`  | Значение: 0 или 1 |

**Возвращает:** None

---

### intr_enable

**Описание:** Включить/разрешить прерывания

**Сигнатура**:
```
void _intr_enable();
```

**Аргументы:** None

**Возвращает:** None

---

### intr_disable

**Описание:** Выключить/запретить прерывания

**Сигнатура**:
```
void _intr_disable();
```

**Аргументы:** None

**Возвращает:** None

---

## Other

### get_ticks

**Описание:** Получить количество тиков с момента запуска системы

**Сигнатура**:
```
unsigned int _get_ticks();
```

**Аргументы:** None

**Возвращает:** Количество тиков

---

### get_device_count

**Описание:** Получить количество устройств

**Сигнатура**:
```
unsigned int _get_device_count();
```

**Аргументы:** None

**Возвращает:** Количество устройств

---

### get_device_info

**Описание:** Получить адрес массива с устройствами

**Сигнатура**:
```
unsigned int _get_device_info();
```

**Аргументы:** None

**Возвращает:** Адрес массива

---
