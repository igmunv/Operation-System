#include "../../libs/shared_memory.h"
#include "../../libs/asm.h"
#include "../../libs/string.h"
#include "../../libs/io.h"
#include "../../libs/time.h"

// Header: start
volatile unsigned char _start_header[16] __attribute__((section(".start_header"))) = {'_','_','_','I','A','M','P','R','O','G','R','A','M','_','_','_'};
// Header: info
volatile unsigned char _info_header[20] __attribute__((section(".info_header"))) = "uptime";
// Header: end
volatile unsigned char _end_header[16] __attribute__((section(".end_header"))) = {'_','_','_','E','N','D','P','R','O','G','R','A','M','_','_','_'};


int _start(void) __attribute__((section(".text.start")));
int _start(void){

    long uptime_second = (TICKS) / 1000;
    unsigned char uptime_second_str[50];
    itos(uptime_second, &uptime_second_str);
    print(uptime_second_str);

    return 0;
}
