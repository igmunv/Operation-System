#define INCL_DRIVER_PROGLOADER
#ifndef INCL_DRIVER_PROGLOADER

struct header_info{
    int sector; // номер сектора
    int byte_index; // индекс байта начала заголовка
};

struct program_info{
    unsigned char name[20];
    struct header_info shi; // start header info
    struct header_info ehi; // end header info
};

void progloader_init();
int progloader_run_default();
int progloader_run_program(int program_index);

#endif
