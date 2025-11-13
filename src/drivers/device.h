#ifndef INCL_DRIVER_DEVICE
#define INCL_DRIVER_DEVICE

#define MAX_DEVICE_COUNT 256

// Информация о устройстве
struct dev_info{
    // Общий идентификатор устройства
    unsigned int id;
    // Тип устройства:
    // 1 - диск/накопитель
    unsigned int dev_type;
    // Название-модель
    unsigned char name[41];
    // Параметры:
    // Параметр 1:
    // Диск: количество секторов
    unsigned int option1;
    // Параметр 2:
    // Диск: флаг is_master (является ли диск главным-основным) - 1 да, 0 нет
    unsigned int option2;
    // Параметр 3:
    // Диск: тип диска (ATA, и т.д)
    // ATA - 1
    unsigned int option3;
};

int device_reg(unsigned int dev_type, unsigned char* name, unsigned int name_size, unsigned int option1, unsigned int option2, unsigned int option3);

int device_get(unsigned int dev_id, struct dev_info* dst);

#endif
