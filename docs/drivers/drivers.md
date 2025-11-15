
драйвера должны иметь функцию init

int init(struct dev_info*);

## Display


#### 0 - вывод текста

```
void print_text(unsigned char*, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char)
```

#### 1 - новая строка

```
void new_line(void)
```

#### 2 - обновить курсор

```
void cursor_update(void)
```

#### 3 - очистить дисплей

```
void clear_display(void)
```

#### 4 - получить текущий символ (можно со смещением)

```
unsigned char get_current_symbol(unsigned int)
```

#### 5 - удалить текущий символ (можно со смещением)

```
unsigned char delete_current_symbol(unsigned int)
```

#### 6 - получить значение координаты X

```
unsigned char get_display_cursor_pos_x(void)
```

#### 7 - получить значение координаты Y

```
unsigned char get_display_cursor_pos_y(void)
```

#### 8 - установить значение координаты X

```
void set_display_cursor_pos_x(unsigned char)
```

#### 9 - установить значение координаты Y

```
void set_display_cursor_pos_y(unsigned char)
```



## Keyboard


#### 0 - получить адрес буфера клавиатуры

```
void* get_keyboard_buffer(void)
```

#### 1 - получить индекс (текущее положение) буфера клавиатуры

```
unsigned int get_keyboard_buffer_ptr(void)
```

#### 2 - получить флаг: нажата ли клавиша shift

```
unsigned char get_keyboard_shift_pressed(void)
```

#### 3 - получить флаг: нажата ли клавиша ctrl

```
unsigned char get_keyboard_ctrl_pressed(void)
```

#### 4 - получить флаг: нажата ли клавиша alt

```
unsigned char get_keyboard_alt_pressed(void)
```



