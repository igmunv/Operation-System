

// Системный вызов запуска программы
unsigned char syscall_program(){
    asm("int $36":::);
}

// Запуск программы
int program_run(int program_index){
    in_ebx(program_index);
    syscall_program();
}
