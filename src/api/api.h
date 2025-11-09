#ifndef INCL_API
#define INCL_API

// Обработчик прерываний на ASM
extern void api_asm_handler(void);

// Обработчик прерываний на C
unsigned int api_handler();

void api_init();


#endif
