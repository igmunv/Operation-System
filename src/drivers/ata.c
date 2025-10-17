#define ATA_BASE 0x1F0

#include "ata.h"


// стандартная задержка для ATA
void ata_delay(){
    inb(ATA_BASE + 7);
    inb(ATA_BASE + 7);
    inb(ATA_BASE + 7);
    inb(ATA_BASE + 7);
}

// Ожидание готовности принятия или отдачи данных и проверяет Занято ли устройство
int ata_wait_ready() {
    int timeout = 1000000;
    while (timeout-- > 0) {
        unsigned char status = inb(ATA_BASE + 7);

        if ((status & 0b10000000) == 0) {       // BSY=0
            // в QEMU не работают
            // if (status & 0x01) return -1; // ERR
            // if (status & 0x20) return -1; // Device Fault
            // if (status & 0b00001000) return 0;  // DRQ
            return 0;
        }

    }
    return -1; // Timeout
}

// Читаем данные с диска
void ata_read(int word_count, unsigned char* buffer){
    for (int i = 0; i < word_count; i++) {
        unsigned short word = inw(ATA_BASE);
        buffer[i*2] = (word & 0xFF);
        buffer[i*2 + 1] = (word >> 8) & 0xFF;
    }
}


// Есть ли диск
// 0 - ok, -1 - not found
int ata_driver_find_disks(){

    // Проверяем подключен ли вообще диск

    outb(ATA_BASE + 6, 0xA0); // Выбираем диск (Master)
    outb(ATA_BASE + 2, 0);
    outb(ATA_BASE + 3, 0);
    outb(ATA_BASE + 4, 0);
    outb(ATA_BASE + 5, 0);
    ata_delay();
    unsigned char status = inb(ATA_BASE + 7); // Читаем подключено ли
    if (status == 0xFF || status == 0x00){
        return -1; // нет
    }

    // Если подключено то ждем пока диск ответит
    int is_timeout = ata_wait_ready();
    if (is_timeout == -1){
        return -1; // timeout
    }

    outb(ATA_BASE + 7, 0xEC);

    ata_delay();

    status = inb(ATA_BASE + 7);

    if (status == 0){
        return -1; // не существует
    }


    // В QEMU не работает
    // unsigned char lbamid = inb(ATA_BASE + 4);
    // unsigned char lbahi = inb(ATA_BASE + 5);
    // if (lbamid == 0 && lbahi == 0){
    //     return -1; // не является ATA диском
    // }


    if (ata_wait_ready() == -1){
        return -1;
    }
    else{
        // Читаем IDENTIFY информацию с диска
        unsigned char ident_buffer[512];
        ata_read(256, ident_buffer);
    }

    return 0;
}


// Чтение определенного секотра
// lba - номер сектора
// buffer - буффер
int ata_driver_read_sector(unsigned int lba, unsigned char* buffer) {

    // Ждем пока диск не занят
    if (ata_wait_ready() < 0) {
        //print("ATA: Drive busy");
        return -1;
    }

    // Выбираем диск Master + LBA (старший байт)
    outb(ATA_BASE + 6, 0xE0 | ((lba >> 24) & 0x0F));

    // Параметры
    outb(ATA_BASE + 2, 1);              // 1 сектор
    outb(ATA_BASE + 3, lba & 0xFF);     // LBA 0-7
    outb(ATA_BASE + 4, (lba >> 8) & 0xFF);  // LBA 8-15
    outb(ATA_BASE + 5, (lba >> 16) & 0xFF); // LBA 16-23

    // Команда чтения
    outb(ATA_BASE + 7, 0x20);

    // Ждем данные
    if (ata_wait_ready() < 0) {
        //print("ATA: Data not ready");
        return -1;
    }

    // Читаем 512 байт (один сектор)


    for (int i = 0; i < 256; i++) { // делим так как читаем слова
        unsigned short word = inw(ATA_BASE);
        buffer[i*2] = (word & 0xFF);
        buffer[i*2 + 1] = (word >> 8) & 0xFF;
    }

    return 0;
}

int ata_driver_write_sector(){

}
