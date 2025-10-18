#ifndef INCL_DRIVER_DEVICE
#define INCL_DRIVER_DEVICE

#define MAX_DEVICE_COUNT 256

// Информация о устройстве
struct dev_info{
    // Общий идентификатор устройства
    unsigned int id;
    // Тип устройства:
    // 1 - диск
    unsigned int dev_type;
    // Название-модель
    unsigned char name[50];
    // Параметры: если 0 значит нет
    // Параметр 1:
    // Диск: количество секторов
    unsigned int option1;
    // Параметр 2:
    // Диск: флаг is_master (является ли диск главным-основным)
    unsigned int option2;
    // Параметр 3:
    unsigned int option3;
};


#endif
