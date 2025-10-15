#ifndef INCL_LIB_PROGRAMS
#define INCL_LIB_PROGRAMS


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

// Выход в loop
void exit();

// Запуск программы
int program_run(int program_index);


#endif
