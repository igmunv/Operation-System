

## INT 34: Display

Регистр `AH` используется для обозначения типа команды

### Command type 0: Print symbol

Description:


Input:
- `BL` - Symbol
- `BH` - X
- `CL` - Y
- `CH` - Font color
- `DL` - Background color

### Command type 1: New line

Description:


### Command type 2: Cursor update

Description:


### Command type 3: Clear display

Description:


### Command type 4: Get current symbol

Description:


Input:
- `BX` - Offset

Output:
- `AL` - Symbol

### Command type 5: Delete current symbol

Description:


Input:
- `BX` - Offset
