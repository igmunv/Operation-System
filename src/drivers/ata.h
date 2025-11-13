#ifndef INCL_DRIVER_ATA
#define INCL_DRIVER_ATA

// Чтение сектора с диска в buffer
int ata_driver_read_sector(unsigned int lba, unsigned char* buffer);

// Запись src на сектор диска
int ata_driver_write_sector(unsigned int lba, unsigned char* src);

// Если есть мастер диск, то добавляет его в устройства
// * Будет удалён или изменён после реализации поиска устройств через PCI
int ata_driver_find_master_disks();

#endif
