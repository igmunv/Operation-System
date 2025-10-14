#define MAX_PROGRAM_COUNT 256

// Structs
struct header_info{
    int sector; // номер сектора
    int byte_index; // индекс байта начала заголовка
};

struct program_info{
    unsigned char name[20];
    struct header_info shi; // start header info
    struct header_info ehi; // end header info
};

// Special memory: display
volatile struct program_info* programs = (struct program_info*)0x5020;
volatile int* program_count = (int*)0x7420;

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
