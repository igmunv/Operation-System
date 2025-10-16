#define MAX_PROGRAM_COUNT 256
#define PROGRAM_ADDRESS 0x30000

#include "progloader.h"
#include "../libs/shared_memory.h"
#include "../libs/programs.h"


void progloader_load_program(unsigned int program_index, int address){
    unsigned char* l_prog_load_addr = (unsigned char*)address;
    if (program_index < PROGLOADER_PROGRAM_COUNT && program_index >= 0){
        struct program_info program = PROGLOADER_PROGRAMS[program_index];
        int start_sector = program.shi.sector;
        int end_sector = program.ehi.sector;
        int start_byte_index = program.shi.byte_index;
        int end_byte_index = program.ehi.byte_index;

        for (int sector = start_sector; sector <= end_sector; sector++){
            unsigned char data[512];
            int read_status = ata_read_sector(sector, data);
            // Error
            if (read_status != 0) {
                print("ATA read failed");
                return -1;
            }

            // Если программа в одном секторе
            if (start_sector == end_sector){
                for (int index = start_byte_index; index <= end_byte_index; index++){
                    unsigned char byte = data[index];
                    *l_prog_load_addr = byte;
                    l_prog_load_addr++;
                }
            }

            else {
                // Первый сектор но не последний
                if (sector != end_sector && sector == start_sector){
                    for (int index = start_byte_index; index < 512; index++){
                        unsigned char byte = data[index];
                        *l_prog_load_addr = byte;
                        l_prog_load_addr++;
                    }
                }
                // Не последний и не первый
                else if (sector != end_sector && sector != start_sector){
                    for (int index = 0; index < 512; index++){
                        unsigned char byte = data[index];
                        *l_prog_load_addr = byte;
                        l_prog_load_addr++;
                    }
                }
                // Последний сектор
                else if (sector == end_sector && sector != start_sector){
                    for (int index = 0; index <= end_byte_index; index++){
                        unsigned char byte = data[index];
                        *l_prog_load_addr = byte;
                        l_prog_load_addr++;
                    }
                }
            }

        }

    }

}

// Запуск программы
int progloader_run(unsigned int program_index, int address){
    if (program_index < PROGLOADER_PROGRAM_COUNT && program_index >= 0){

        // Print program name
        // volatile unsigned short* io_display_cursor_pos_x = (unsigned short*)0x5014;
        // volatile unsigned short* io_display_cursor_pos_y = (unsigned short*)0x5016;
        //
        // io_printx("Load: ", *io_display_cursor_pos_x, *io_display_cursor_pos_y, 7, 0);
        // (*io_display_cursor_pos_x)+=6;
        // io_printx(programs[program_index].name, *io_display_cursor_pos_x, *io_display_cursor_pos_y, 7, 0);
        // (*io_display_cursor_pos_y)++;
        // (*io_display_cursor_pos_x)=0;

        // Load program from disk in memory

        progloader_load_program(program_index,address);

        // Run program
        int (*entry)() = (int(*)())(address+30);
        entry();
        return 0;

    }
    else{
        return -1; // Progloader Error: program index is not found
    }
}

// Запуск программы
int progloader_run_program(unsigned int program_index){
    int return_code = progloader_run(program_index, PROGRAM_ADDRESS);
    if (return_code == -1){
        print("This program is not found!");
    }
    return return_code;
}

// Инициализация
void progloader_init(){
    programs_load();
}
