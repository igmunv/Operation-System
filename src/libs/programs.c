#include "programs.h"
#include "shared_memory.h"
#include "ata.h"

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
    // exit();
}

void programs_load() {

    char flag_start_header = 0;
    char flag_end_header = 1;

    unsigned char data[512];

    PROGLOADER_PROGRAM_COUNT =0;

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
