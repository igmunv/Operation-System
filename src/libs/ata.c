#include "ata.h"

// Системный вызов ATA
unsigned char syscall_ata(unsigned char command_type){
    clear_ah();
    in_ah(command_type);
    asm("int $35":::);
}

int ata_read_sector(unsigned int lba, unsigned char* buffer){
    in_ebx(lba);
    in_edx(buffer);
    syscall_ata(0);
}
