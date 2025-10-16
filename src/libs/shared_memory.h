#ifndef INCL_LIB_SHARED_MEMORY
#define INCL_LIB_SHARED_MEMORY

#include "programs.h"

//
// Address
//

// Kernel
#define ADR_EXECUTE_PROGRAM 0x5000

// Keyboard
#define ADR_KEYBOARD_BUFFER 0x5004
#define ADR_KEYBOARD_BUFFER_PTR 0x5014
#define ADR_KEYBOARD_SHIFT_PRESSED 0x5015
#define ADR_KEYBOARD_CTRL_PRESSED 0x5016
#define ADR_KEYBOARD_ALT_PRESSED 0x5017

// Display
#define ADR_DISPLAY_CURSOR_POS_X 0x5018
#define ADR_DISPLAY_CURSOR_POS_Y 0x501a

// Ticks
#define ADR_TICKS 0x501c

// ProgLoader
#define ADR_PROGLOADER_PROGRAMS 0x5020
#define ADR_PROGLOADER_PROGRAM_COUNT 0x7420

//
// Variables
//

// Kernel
#define EXECUTE_PROGRAM (*((int*)ADR_EXECUTE_PROGRAM))

// Keyboard
#define KEYBOARD_BUFFER (((unsigned char*)ADR_KEYBOARD_BUFFER))
#define KEYBOARD_BUFFER_PTR (*((unsigned char*)ADR_KEYBOARD_BUFFER_PTR))
#define KEYBOARD_SHIFT_PRESSED (*((char*)ADR_KEYBOARD_SHIFT_PRESSED))
#define KEYBOARD_CTRL_PRESSED (*((char*)ADR_KEYBOARD_CTRL_PRESSED))
#define KEYBOARD_ALT_PRESSED (*((char*)ADR_KEYBOARD_ALT_PRESSED))

// Display
#define DISPLAY_CURSOR_POS_X (*((unsigned short*)ADR_DISPLAY_CURSOR_POS_X))
#define DISPLAY_CURSOR_POS_Y (*((unsigned short*)ADR_DISPLAY_CURSOR_POS_Y))

// Ticks
#define TICKS (*((unsigned long*)ADR_TICKS))

// ProgLoader
#define PROGLOADER_PROGRAMS (((struct program_info*)ADR_PROGLOADER_PROGRAMS)) // (struct program_info*)
#define PROGLOADER_PROGRAM_COUNT (*((int*)ADR_PROGLOADER_PROGRAM_COUNT))

#endif
