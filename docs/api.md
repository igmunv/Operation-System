

## `INT 0x22`: Display

##### Регистр `AH` используется для обозначения типа команды

### Command `0x0`: Print symbol

#### Description:
Выводит символ на экран

#### Input:
- `BL` - Symbol
- `BH` - X
- `CL` - Y
- `CH` - Font color
- `DL` - Background color

### Command `0x1`: New line

#### Description:
Переход на следующую строку

### Command `0x2`: Cursor update

#### Description:
Обновить курсор

### Command `0x3`: Clear display

#### Description:
Очистить весь экран

### Command `0x4`: Get current symbol

#### Description:
Получить текущий символ (можно задать смещение)

#### Input:
- `BX` - Offset

#### Output:
- `AL` - Symbol

### Command `0x5`: Delete current symbol

#### Description:
Удалить текущий символ (можно задать смещение)

#### Input:
- `BX` - Offset


## Планы:
- sleep
- get time

