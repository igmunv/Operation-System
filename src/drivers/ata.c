
#define ATA_BASE 0x1F0

// Занято ли устройство
int ata_wait_busy() {
    int timeout = 1000000;
    while (timeout-- > 0) {
        if ((inb(ATA_BASE + 7) & 0x80) == 0) return 0; // Not busy
    }
    return -1; // Timeout
}

// Ожидание чтения данных
int ata_wait_data_ready() {
    int timeout = 1000000;
    while (timeout-- > 0) {
        unsigned char status = inb(ATA_BASE + 7);
        if (status & 0x08) return 0; // Data ready
        if (status & 0x01) return -1; // Error
    }
    return -1; // Timeout
}

// Чтение определенного секотра
int ata_read_sector_(unsigned int lba, unsigned char* buffer) {

    // Ждем пока диск не занят
    if (ata_wait_busy() < 0) {
        //print("ATA: Drive busy");
        return -1;
    }

    // Выбираем диск (Master) + LBA
    outb(ATA_BASE + 6, 0xE0 | ((lba >> 24) & 0x0F));

    // Параметры
    outb(ATA_BASE + 2, 1);              // 1 сектор
    outb(ATA_BASE + 3, lba & 0xFF);     // LBA 0-7
    outb(ATA_BASE + 4, (lba >> 8) & 0xFF);  // LBA 8-15
    outb(ATA_BASE + 5, (lba >> 16) & 0xFF); // LBA 16-23

    // Команда чтения
    outb(ATA_BASE + 7, 0x20);

    // Ждем данные (БЕЗ ПРЕРЫВАНИЙ!)
    if (ata_wait_data_ready() < 0) {
        //print("ATA: Data not ready");
        return -1;
    }

    // Читаем 512 байт (один сектор)
    for (int i = 0; i < 256; i++) {
        unsigned short word = inw(ATA_BASE);
        buffer[i*2] = (word & 0xFF);
        buffer[i*2 + 1] = (word >> 8) & 0xFF;
    }

    return 0;
}
