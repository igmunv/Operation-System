#ifndef INCL_API
#define INCL_API

// Обработчики прерываний на ASM
extern void api_asm_display_handler();
extern void api_asm_ata_handler();
extern void api_asm_execute_handler();

// Обработчики прерываний на C
void api_display_handler();
void api_ata_handler();
void api_execute_handler();

void api_init();


#endif
