// userspace API handler

#ifndef INCL_API
#define INCL_API


struct syscall_result {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int esi;
    unsigned int edi;
};


// Обработчик прерываний на ASM
extern void api_asm_handler(void);

// Обработчик прерываний на C
void api_handler();

// Инициализация: обработчик прерывания
void api_init();


#endif
