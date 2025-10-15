#define MAX_PROGRAM_COUNT 256

#include "programs.h"

// Системный вызов запуска программы
unsigned char syscall_program(){
    asm("int $36":::);
}

void exit(){
    asm volatile (
        "movl $0x10000, %eax\n\t"
        "jmp *%eax\n\t"
    );
}

// Запуск программы
int program_run(int program_index){
    in_ebx(program_index);
    syscall_program();
    exit();
}
