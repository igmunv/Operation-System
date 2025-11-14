#ifndef INCL_LIB_DEVICE
#define INCL_LIB_DEVICE

#define MAX_DEVICE_COUNT 256

// Информация о устройстве
struct dev_info{

    unsigned char is_pci_dev; // 0 or 1
    unsigned char is_virt_dev; // 0 or 1

    unsigned int bus;
    unsigned int dev;
    unsigned int func;

    unsigned short vendor_id;
    unsigned short device_id;

    unsigned short command;
    unsigned short status;

    unsigned char revision_id;
    unsigned char prog_if;

    unsigned char subclass;
    unsigned char classcode;

    unsigned char cache_line_size;
    unsigned char latency_timer;

    unsigned char mf;
    unsigned char header_type;

    unsigned char bist;

    unsigned int bar0;
    unsigned int bar1;
    unsigned int bar2;
    unsigned int bar3;
    unsigned int bar4;
    unsigned int bar5;

    struct driver_info* driver;

};


enum virt_class_codes{
    VIRT_DISPLAY_CONTROLLER                  = 0x20,
    VIRT_KEYBOARD_CONTROLLER                 = 0x21,
};

enum virt_display_subclass{
    VIRT_DISPLAY_VGATEXT                     = 0x0,
};

enum virt_keyboard_subclass{
    VIRT_KEYBOARD_LDEV                       = 0x0,
};


enum class_codes{
    UNCLASSIFIED                        = 0x0,
    STORAGE_CONTROLLER                  = 0x1,
    NETWORK_CONTROLLER                  = 0x2,
    DISPLAY_CONTROLLER                  = 0x3,
    MULTIMEDIA_CONTROLLER               = 0x4,
    MEMORY_CONTROLLER                   = 0x5,
    BRIDGE                              = 0x6,
    SIMPLE_COMMUNICATION_CONTROLLER     = 0x7,
    BASE_SYSTEM_PERIPHERAL              = 0x8,
    INPUT_DEVICE_CONTROLLER             = 0x9,
    DOCKING_STATION                     = 0xA,
    PROCESSOR                           = 0xB,
    SERIAL_BUS_CONTROLLER               = 0xC,
    WIRELESS_CONTROLLER                 = 0xD,
    INTELLIGENT_CONTROLLER              = 0xE,
    SATELLITE_COMMUNICATION_CONTROLLER  = 0xF,
    ENCRYPTION_CONTROLLER               = 0x10,
    SIGNAL_PROCESSING_CONTROLLER        = 0x11,
    PROCESSING_ACCELERATOR              = 0x12,
    NON_ESSENTIAL_INSTRUMENTATION       = 0x13,

    RESERVED_BEGIN      = 0x14,
    RESERVED_END        = 0x3F,
    CO_PROCESSOR        = 0x40,
    _0xFE_RESERVED      = 0xFE,
    UNASSIGNED_CLASS    = 0xFF
};

enum storage_subclass {
    STORAGE_SCSI_BUS_CONTROLLER        = 0x00,
    STORAGE_IDE_CONTROLLER             = 0x01,
    STORAGE_FLOPPY_DISK_CONTROLLER     = 0x02,
    STORAGE_IPI_BUS_CONTROLLER         = 0x03,
    STORAGE_RAID_CONTROLLER            = 0x04,
    STORAGE_ATA_CONTROLLER             = 0x05,
    STORAGE_SERIAL_ATA_CONTROLLER      = 0x06,
    STORAGE_SERIAL_ATTACHED_SCSI       = 0x07,
    STORAGE_NON_VOLATILE_MEMORY        = 0x08,
    STORAGE_OTHER                      = 0x80,
};

enum network_subclass {
    NETWORK_ETHERNET_CONTROLLER     = 0x0,
    NETWORK_TOKEN_RING_CONTROLLER   = 0x1,
    NETWORK_FDDI_CONTROLLER         = 0x2,
    NETWORK_ATM_CONTROLLER          = 0x3,
    NETWORK_ISDN_CONTROLLER         = 0x4,
    NETWORK_WORLDFIP_CONTROLLER     = 0x5,
    NETWORK_PICMG_MC_CONTROLLER     = 0x6,
    NETWORK_INFINIBAND_CONTROLLER   = 0x7,
    NETWORK_FABRIC_CONTROLLER       = 0x8,
    NETWORK_OTHER                   = 0x80,
};

enum display_subclass {
    DISPLAY_VGA_COMPATIBLE = 0x00,
    DISPLAY_XGA = 0x01,
    DISPLAY_3D = 0x02,
    DISPLAY_OTHER = 0x80
};

enum multimedia_subclass {
    MULTIMEDIA_VIDEO = 0x00,
    MULTIMEDIA_AUDIO = 0x01,
    MULTIMEDIA_TELEPHONY = 0x02,
    MULTIMEDIA_AUDIO_DEVICE = 0x03,
    MULTIMEDIA_OTHER = 0x80
};

enum memory_subclass {
    MEMORY_RAM = 0x00,
    MEMORY_FLASH = 0x01,
    MEMORY_OTHER = 0x80
};

enum bridge_subclass {
    BRIDGE_HOST = 0x00,
    BRIDGE_ISA = 0x01,
    BRIDGE_EISA = 0x02,
    BRIDGE_MCA = 0x03,
    BRIDGE_PCI_TO_PCI = 0x04,
    BRIDGE_PCMCIA = 0x05,
    BRIDGE_NUBUS = 0x06,
    BRIDGE_CARDBUS = 0x07,
    BRIDGE_RACEWAY = 0x08,
    BRIDGE_PCI_TO_PCI1 = 0x09,
    BRIDGE_INFINIBAND_TO_PCI = 0x0A,
    BRIDGE_OTHER = 0x80
};

enum scomm_subclass {
    SCOMM_SERIAL = 0x00,
    SCOMM_PARALLEL = 0x01,
    SCOMM_MULTI_SERIAL = 0x02,
    SCOMM_MODEM = 0x03,
    SCOMM_GPIB = 0x04,
    SCOMM_SMART_CARD = 0x05,
    SCOMM_OTHER = 0x80
};

enum base_sys_peripheral_subclass {
    BSP_PIC = 0x00,
    BSP_DMA = 0x01,
    BSP_TIMER = 0x02,
    BSP_RTC = 0x03,
    BSP_PCI_HOTPLUG = 0x04,
    BSP_SD_HOST = 0x05,
    BSP_IOMMU = 0x06,
    BSP_OTHER = 0x80
};

enum input_device_subclass {
    INPUT_KEYBOARD = 0x00,
    INPUT_DIGITIZER = 0x01,
    INPUT_MOUSE = 0x02,
    INPUT_SCANNER = 0x03,
    INPUT_GAMEPORT = 0x04,
    INPUT_OTHER = 0x80
};

enum docking_station_subclass {
    OCK_GENERIC = 0x00,
    DOCK_OTHER = 0x80
};

enum processor_subclass {
    PROC_386       = 0x00,
    PROC_486       = 0x01,
    PROC_PENTIUM   = 0x02,
    PROC_PENTIUM_PRO = 0x03,
    PROC_ALPHA     = 0x10,
    PROC_POWERPC   = 0x20,
    PROC_MIPS      = 0x30,
    PROC_CO_PROCESSOR = 0x40,
    PROC_OTHER     = 0x80
};

enum serbus_subclass {
    SERBUS_FIREWIRE       = 0x00,
    SERBUS_ACCESS         = 0x01,
    SERBUS_SSA            = 0x02,
    SERBUS_USB            = 0x03,
    SERBUS_FIBRE_CHANNEL  = 0x04,
    SERBUS_SMBUS          = 0x05,
    SERBUS_INFINIBAND     = 0x06,
    SERBUS_IPMI           = 0x07,
    SERBUS_SERCOS         = 0x08,
    SERBUS_CANBUS         = 0x09,
    SERBUS_OTHER          = 0x80
};

enum wireless_subclass {
    WIRELESS_IRDA        = 0x00,
    WIRELESS_CONSUMER_IR = 0x01,
    WIRELESS_RF          = 0x10,
    WIRELESS_BLUETOOTH   = 0x11,
    WIRELESS_BROADBAND   = 0x12,
    WIRELESS_ETHERNET_A  = 0x20,
    WIRELESS_ETHERNET_B  = 0x21,
    WIRELESS_OTHER       = 0x80
};

enum intelligent_subclass {
    INTELLIGENT_I20 = 0x00
};

enum satcomm_subclass {
    SATCOMM_TV      = 0x01,
    SATCOMM_AUDIO   = 0x02,
    SATCOMM_VOICE   = 0x03,
    SATCOMM_DATA    = 0x04
};

enum encryption_subclass {
    ENCRYPTION_NET_COMP = 0x00,
    ENCRYPTION_ENTERTAIN = 0x10,
    ENCRYPTION_OTHER     = 0x80
};

enum signproccs_subclass {
    SIGPROC_DPIO_MODULES  = 0x00,
    SIGPROC_PERF_COUNTERS = 0x01,
    SIGPROC_COMM_SYNC     = 0x10,
    SIGPROC_SIG_PROC_MGMT = 0x20,
    SIGPROC_OTHER         = 0x80
};

#endif
