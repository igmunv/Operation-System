#include "pci.h"
#include "../devices.h"
#include "../../libs/asm.h"
#include "../../libs/device.h"

unsigned short pci_config_read_word(unsigned int bus, unsigned int dev, unsigned int func, unsigned char offset){

    unsigned int address = 0;
    // bus, device, function, offset, enable bit
    address = (unsigned int)((bus << 16) | (dev << 11) | (func << 8) | (offset & 0b11111100) | ((unsigned int)0x80000000));
    outl(CONFIG_ADDRESS, address);
    unsigned short result = (unsigned short)((inl(CONFIG_DATA) >> ((offset & 0b00000010) * 8)) & 0xFFFF);
    return result;

}


unsigned int pci_config_read_dword(unsigned int bus, unsigned int dev, unsigned int func, unsigned char offset){

    unsigned int address = 0;
    // bus, device, function, offset, enable bit
    address = (unsigned int)((bus << 16) | (dev << 11) | (func << 8) | (offset & 0b11111100) | ((unsigned int)0x80000000));
    outl(CONFIG_ADDRESS, address);
    return inl(CONFIG_DATA);

}


void pci_config_write_word(unsigned int bus, unsigned int dev, unsigned int func, unsigned char offset, unsigned short word){
    unsigned int address = 0;
    // bus, device, function, offset, enable bit
    address = (unsigned int)((bus << 16) | (dev << 11) | (func << 8) | (offset & 0b11111100) | ((unsigned int)0x80000000));
    outl(CONFIG_ADDRESS, address);

    // дальше изменяем полученное, и отправляем обратно

    // Эта проверка определяет в какой половине 32-битного регистра находятся нужные 16 бит
    // так как в одних 32 битах, может быть 2 значения по 16 бит, к примеру command и status
    if ((offset & 0b00000010) == 0b00000010){ // проверяем один бит
        unsigned int tmp = inl(CONFIG_DATA) & 0x0000FFFF;
        tmp |= ((unsigned int)word << 16);
        outl(CONFIG_DATA, tmp);
    }
    else{
        unsigned int tmp = inl(CONFIG_DATA) & 0xFFFF0000;
        tmp |= (unsigned int)word;
        outl(CONFIG_DATA, tmp);
    }

}


struct pci_common_header pci_config_get_common_header(unsigned int bus, unsigned int dev, unsigned int func){

    struct pci_common_header header;

    unsigned int vendor_device = pci_config_read_dword(bus, dev, func, 0x0);
    unsigned int command_status = pci_config_read_dword(bus, dev, func, 0x4);
    unsigned int rev_prog_sclass_class = pci_config_read_dword(bus, dev, func, 0x8);
    unsigned int cls_lt_headt_bist = pci_config_read_dword(bus, dev, func, 0xC);

    unsigned short vendor_id = vendor_device & 0x0000FFFF;
    unsigned short device_id = (vendor_device >> 16) & 0x0000FFFF;

    unsigned short command = command_status & 0x0000FFFF;
    unsigned short status = (command_status >> 16) & 0x0000FFFF;

    unsigned char revision_id = rev_prog_sclass_class & 0x000000FF;
    unsigned char prog_if = (rev_prog_sclass_class >> 8) & 0x000000FF;
    unsigned char subclass = (rev_prog_sclass_class >> 16) & 0x000000FF;
    unsigned char class_code = (rev_prog_sclass_class >> 24) & 0x000000FF;

    unsigned char cache_line_size = cls_lt_headt_bist & 0x000000FF;
    unsigned char latency_timer = (cls_lt_headt_bist >> 8) & 0x000000FF;

    unsigned char mf = (((cls_lt_headt_bist >> 16) & 0x000000FF) & 0b10000000) >> 7;
    unsigned char header_type = ((cls_lt_headt_bist >> 16) & 0x000000FF) & 0b01111111;

    unsigned char bist = (cls_lt_headt_bist >> 24) & 0x000000FF;

    header.vendor_id = vendor_id;
    header.device_id = device_id;
    header.command = command;
    header.status = status;
    header.revision_id = revision_id;
    header.prog_if = prog_if;
    header.subclass = subclass;
    header.classcode = class_code;
    header.cache_line_size = cache_line_size;
    header.latency_timer = latency_timer;
    header.mf = mf;
    header.header_type = header_type;
    header.bist = bist;

    return header;

}


struct pci_header_0 pci_config_get_header_0(unsigned int bus, unsigned int dev, unsigned int func){
    struct pci_common_header common_header = pci_config_get_common_header(bus, dev, func);
    struct pci_header_0 result;
    result.common_header = common_header;
    result.bar0 = pci_config_read_dword(bus, dev, func, 0x10);
    result.bar1 = pci_config_read_dword(bus, dev, func, 0x14);
    result.bar2 = pci_config_read_dword(bus, dev, func, 0x18);
    result.bar3 = pci_config_read_dword(bus, dev, func, 0x1C);
    result.bar4 = pci_config_read_dword(bus, dev, func, 0x20);
    result.bar5 = pci_config_read_dword(bus, dev, func, 0x24);
    return result;
}


struct pci_command_register pci_config_get_command(unsigned int bus, unsigned int dev, unsigned int func){
    unsigned short command = pci_config_read_word(bus, dev, func, 0x4);

    struct pci_command_register result;

    result.io_space =           (command & 0b00000001);
    result.memory_space =       (command & 0b00000010) >> 1;
    result.bus_master =         (command & 0b00000100) >> 2;
    result.special_cycles =     (command & 0b00001000) >> 3;
    result.mem_wr_and_inv_en =  (command & 0b00010000) >> 4;
    result.vga_pal_sn =         (command & 0b00100000) >> 5;
    result.par_err_resp =       (command & 0b01000000) >> 6;
    result.serr_enable =        (command & 0b0000000100000000) >> 8;
    result.fast_bk_to_bk_en =   (command & 0b0000001000000000) >> 9;
    result.int_disable =        (command & 0b0000010000000000) >> 10;

    return result;
}


struct pci_status_register pci_config_get_status(unsigned int bus, unsigned int dev, unsigned int func){
    unsigned short status = pci_config_read_word(bus, dev, func, 0x6);

    struct pci_status_register result;

    result.int_status =             (status & 0b00001000) >> 3;
    result.capb_list =              (status & 0b00010000) >> 4;
    result._66mhz_cap =             (status & 0b00100000) >> 5;
    result.fast_bk_to_bk_cap =      (status & 0b10000000) >> 7;
    result.mast_dt_par_err =        (status & 0b0000000100000000) >> 8;
    result.devsel_timing =          (status & 0b0000011000000000) >> 9;
    result.sign_targ_abort =        (status & 0b0000100000000000) >> 11;
    result.received_targ_abort =    (status & 0b0001000000000000) >> 12;
    result.received_mast_abort =    (status & 0b0010000000000000) >> 13;
    result.sign_sys_err =           (status & 0b0100000000000000) >> 14;
    result.detect_par_err =         (status & 0b1000000000000000) >> 15;

    return result;
}


void pci_config_set_command(unsigned int bus, unsigned int dev, unsigned int func, struct pci_command_register cmd){
    unsigned short cmd_binary = 0;

    cmd_binary |= (cmd.io_space & 0x1) << 0;
    cmd_binary |= (cmd.memory_space & 0x1) << 1;
    cmd_binary |= (cmd.bus_master & 0x1) << 2;
    cmd_binary |= (cmd.special_cycles & 0x1) << 3;
    cmd_binary |= (cmd.mem_wr_and_inv_en & 0x1) << 4;
    cmd_binary |= (cmd.vga_pal_sn & 0x1) << 5;
    cmd_binary |= (cmd.par_err_resp & 0x1) << 6;
    cmd_binary |= (cmd.serr_enable & 0x1) << 8;
    cmd_binary |= (cmd.fast_bk_to_bk_en & 0x1) << 9;
    cmd_binary |= (cmd.int_disable & 0x1) << 10;

    pci_config_write_word(bus, dev, func, 0x4, cmd_binary);
}


void pci_device_registration(unsigned int bus, unsigned int dev, unsigned int func, struct pci_header_0 header){

    struct dev_info device;

    device.is_pci_dev = 1;

    device.bus = bus;
    device.dev = dev;
    device.func = func;

    device.vendor_id = header.common_header.vendor_id;
    device.device_id = header.common_header.device_id;

    device.command = header.common_header.command;
    device.status = header.common_header.status;

    device.revision_id = header.common_header.revision_id;
    device.prog_if = header.common_header.prog_if;

    device.subclass = header.common_header.subclass;
    device.classcode = header.common_header.classcode;

    device.cache_line_size = header.common_header.cache_line_size;
    device.latency_timer = header.common_header.latency_timer;

    device.mf = header.common_header.mf;
    device.header_type = header.common_header.header_type;

    device.bist = header.common_header.bist;

    device.bar0 = header.bar0;
    device.bar1 = header.bar1;
    device.bar2 = header.bar2;
    device.bar3 = header.bar3;
    device.bar4 = header.bar4;
    device.bar5 = header.bar5;

    device_registration(&device);

}


void pci_find_devices(){
    for (unsigned int bus = 0; bus < 256; bus++){
        for (unsigned int dev = 0; dev < 32; dev++){
            for (unsigned int func = 0; func < 8; func++){

                struct pci_common_header common_header = pci_config_get_common_header(bus, dev, func);

                // Обрабатываем только устройства, без шин и т.д
                if (common_header.header_type != 0x0) continue;

                if (func == 0){

                    if (common_header.vendor_id == 0xFFFF) break; // Not found

                    pci_device_registration(bus, dev, func, pci_config_get_header_0(bus, dev, func));

                    if (!common_header.mf) break; // Not multifunction

                }
                else{

                    if (common_header.vendor_id == 0xFFFF) continue; // Not found

                    pci_device_registration(bus, dev, func, pci_config_get_header_0(bus, dev, func));

                }

            }
        }
    }
}
