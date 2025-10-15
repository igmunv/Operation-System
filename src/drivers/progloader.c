#define MAX_PROGRAM_COUNT 256
#define PROGRAM_ADDRESS 0x40000
#define DEFAULT_PROGRAM_ADDRESS 0x30000

#include "progloader.h"
#include "../libs/shared_memory.h"

unsigned char* default_program_load_address = (unsigned char*)DEFAULT_PROGRAM_ADDRESS;
unsigned char* program_load_address = (unsigned char*)PROGRAM_ADDRESS;

void progloader_get_programs() {

    char flag_start_header = 0;
    char flag_end_header = 1;

    unsigned char data[512];

    const int MAX_SECTOR_COUNT = 100;
    for (int sector = 0; sector < MAX_SECTOR_COUNT; sector++){

        // Read
        int read_status = ata_read_sector(sector, data);

        // Error
        if (read_status != 0) {
            print("ATA read failed");
            return -1;
        }

        // Search start and end headers
        for (int i = 0; i < (512-15); i++){

            // Start Header
            if (
                flag_start_header == 0 &&
                flag_end_header == 1 &&
                data[i+0] == '_' &&
                data[i+1] == '_' &&
                data[i+2] == '_' &&
                data[i+3] == 'I' &&
                data[i+4] == 'A' &&
                data[i+5] == 'M' &&
                data[i+6] == 'P' &&
                data[i+7] == 'R' &&
                data[i+8] == 'O' &&
                data[i+9] == 'G' &&
                data[i+10] == 'R' &&
                data[i+11] == 'A' &&
                data[i+12] == 'M' &&
                data[i+13] == '_' &&
                data[i+14] == '_' &&
                data[i+15] == '_')
            {
                // header
                PROGLOADER_PROGRAMS[PROGLOADER_PROGRAM_COUNT].shi.sector = sector;
                PROGLOADER_PROGRAMS[PROGLOADER_PROGRAM_COUNT].shi.byte_index = i;

                // name
                for (short symb_index = 0; symb_index < 20; symb_index++){
                    PROGLOADER_PROGRAMS[PROGLOADER_PROGRAM_COUNT].name[symb_index] = data[i+16+symb_index];
                }
                PROGLOADER_PROGRAMS[PROGLOADER_PROGRAM_COUNT].name[19] = 0;


                flag_start_header = 1;
                flag_end_header = 0;
                break;
            }

            // End Header
            else if (
                flag_start_header == 1 &&
                flag_end_header == 0 &&
                data[i+0] == '_' &&
                data[i+1] == '_' &&
                data[i+2] == '_' &&
                data[i+3] == 'E' &&
                data[i+4] == 'N' &&
                data[i+5] == 'D' &&
                data[i+6] == 'P' &&
                data[i+7] == 'R' &&
                data[i+8] == 'O' &&
                data[i+9] == 'G' &&
                data[i+10] == 'R' &&
                data[i+11] == 'A' &&
                data[i+12] == 'M' &&
                data[i+13] == '_' &&
                data[i+14] == '_' &&
                data[i+15] == '_')
            {
                // header
                PROGLOADER_PROGRAMS[PROGLOADER_PROGRAM_COUNT].ehi.sector = sector;
                PROGLOADER_PROGRAMS[PROGLOADER_PROGRAM_COUNT].ehi.byte_index = i;

                flag_start_header = 0;
                flag_end_header = 1;
                PROGLOADER_PROGRAM_COUNT++;
            }
        }
    }
}

void progloader_load_program(int program_index, int address){
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
int progloader_run(int program_index, int address, int default_){
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
        int ret = entry();
        return ret;

    }
    else{
        return -1; // Progloader Error: program index is not found
    }
}

// Запуск программы по умолчанию
int progloader_run_default(){
    // По умолчанию запускаем самую первую программу на диске
    char default_program_index = 0;
    int return_code = progloader_run(default_program_index, default_program_load_address, 1);
    if (return_code == -1){
        print("Default program is not found!");
    }
    return return_code;
}

// Запуск программы
int progloader_run_program(int program_index){
    int return_code = progloader_run(program_index, program_load_address, 0);
    if (return_code == -1){
        print("This program is not found!");
    }
    return return_code;
}

// Инициализация
void progloader_init(){
    progloader_get_programs();
}
