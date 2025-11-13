#include "file_system.h"
#include "device.h"
#include "../libs/memory.h"

int fs_mount(unsigned int dev_id){

    struct dev_info disk_info;
    device_get(dev_id, &disk_info);

    if (disk_info.dev_type != 1) return -1; // Не является диском/накопителем

    struct fs_info* info;

    if (disk_info.option3 == 1) { // ATA диск

        // Info
        unsigned char info_sector[512];
        ata_driver_read_sector(START_INFO_SECTOR, info_sector);
        info = &info_sector;

        // Table
        for (int i = 1; i <= (info.file_count); i++){
             // * 4096 / 512
        }

    }

    FILE_SYSTEM_DEV_ID = dev_id;
    FILE_SYSTEM_IS_MOUNT_FLAG = 1;
    FILE_SYSTEM_INFO = *info;
    // FILE_SYSTEM_TABLE = таблица ФС с диска

    // нужно еще сделать проверку на то сколько записей в таблице ФС, так как если не делать то можно
    // перечитывать данные а так нельзя

}

int fs_umount(){
    FILE_SYSTEM_DEV_ID = 0;
    FILE_SYSTEM_IS_MOUNT_FLAG = 0;
}

int fs_make(unsigned int dev_id){

    struct dev_info disk_info;
    int result_dev_get = device_get(dev_id, &disk_info);

    if (result_dev_get != 0) return -1;
    if (disk_info.dev_type != 1) return -1; // Не является диском/накопителем

    struct fs_info info;
    unsigned char* signature = "___IAMFILESYS___";
    memcpy(info.signature, signature, 16);
    info.data_sec_count = disk_info.option1 - 8200;
    info.data_free_sec_count = disk_info.option1 - 8200;
    info.file_count = 0;

    unsigned char info_bytes[512];
    memcpy(info_bytes, &info, sizeof(struct fs_info));

    struct fs_file_table file_table;

    if (disk_info.option3 == 1) { // ATA диск
        // Записываем INFO
        int result = ata_driver_write_sector(0, info_bytes);

        return result;
    }

}
