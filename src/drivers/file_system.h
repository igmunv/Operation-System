#ifndef INCL_DRIVER_FILE_SYSTEM
#define INCL_DRIVER_FILE_SYSTEM

#define START_INFO_SECTOR 0
#define START_TABLE_SECTOR 1
#define START_DATA_SECTOR 8200

#define MAX_FILE_COUNT 1024

#define MAX_FILE_NAME_SIZE 16
#define MAX_FILE_EXT_SIZE 8
#define MAX_FILE_SECTOR_COUNT 1016

// Size: 28
struct fs_info{
    unsigned char signature[16];
    unsigned int data_sec_count;
    unsigned int data_free_sec_count;
    unsigned int file_count;
};


// Size: 4092b
struct fs_file_table{
    unsigned char name[MAX_FILE_NAME_SIZE];
    unsigned char ext[MAX_FILE_EXT_SIZE];
    unsigned int sector_count;
    unsigned int sector[MAX_FILE_SECTOR_COUNT];
};

// Mount flag
#define ADR_FILE_SYSTEM_IS_MOUNT_FLAG 0x30000
#define FILE_SYSTEM_IS_MOUNT_FLAG (*((unsigned char*)ADR_FILE_SYSTEM_IS_MOUNT_FLAG))

// Disk struct address
#define ADR_FILE_SYSTEM_DEV_ID 0x30004
#define FILE_SYSTEM_DEV_ID (*((unsigned int*)ADR_FILE_SYSTEM_DEV_ID))

// INFO address
#define ADR_FILE_SYSTEM_INFO 0x30008
#define FILE_SYSTEM_INFO (*(struct fs_info*)ADR_FILE_SYSTEM_INFO)

// Table address
#define ADR_FILE_SYSTEM_TABLE 0x30024
#define FILE_SYSTEM_TABLE ((struct fs_file_table*)ADR_FILE_SYSTEM_TABLE)


int fs_make(unsigned int dev_id);

int fs_mount(unsigned int dev_id);

int fs_umount();

#endif
