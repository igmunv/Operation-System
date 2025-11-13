#include "../../libs/io.h"
#include "../../libs/time.h"
#include "../../libs/shared_memory.h"

// Header: start
volatile unsigned char _start_header[16] __attribute__((section(".start_header"))) = {'_','_','_','I','A','M','P','R','O','G','R','A','M','_','_','_'};
// Header: info
volatile unsigned char _info_header[20] __attribute__((section(".info_header"))) = "colorama";
// Header: end
volatile unsigned char _end_header[16] __attribute__((section(".end_header"))) = {'_','_','_','E','N','D','P','R','O','G','R','A','M','_','_','_'};


// Entry point
void _start(void) __attribute__((section(".text.start")));
void _start(){

    int color = 0;
    int bcolor = 7;
    for (int i = 33; i <= 126; i++){
        char text[2];
        text[0] = (unsigned char)i;
        text[1] = '\0';
        io_printx(text, DISPLAY_CURSOR_POS_X, DISPLAY_CURSOR_POS_Y, color, bcolor);
        color = (color+1)%14;
        bcolor = (bcolor+1)%14;
        sleep(50);
    }
    io_printx("\n", DISPLAY_CURSOR_POS_X, DISPLAY_CURSOR_POS_Y, 0, 0);
    color = (color+1)%14;

}
