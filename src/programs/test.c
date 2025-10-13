#include "../lib/asm.c"
#include "../lib/string.c"
#include "../lib/io.c"
#include "../lib/time.c"

// Header: start
volatile unsigned char _start_header[16] __attribute__((section(".start_header"))) = {'_','_','_','I','A','M','P','R','O','G','R','A','M','_','_','_'};
// Header: info
volatile unsigned char _info_header[20] __attribute__((section(".info_header"))) = "test";
// Header: end
volatile unsigned char _end_header[16] __attribute__((section(".end_header"))) = {'_','_','_','E','N','D','P','R','O','G','R','A','M','_','_','_'};

int test(int n){

    return n+35;
}

unsigned int get_eflags() {
    unsigned int flags;
    asm volatile ("pushfd; pop %0" : "=r"(flags));
    return (flags >> 9) & 1;
}


void _start(void) __attribute__((section(".text.start")));
void _start(){

    char s = test(15);
    (*io_display_cursor_pos_x) = 0;
    *io_display_cursor_pos_y = 0;
    print_symbol(s);

    int f = get_eflags();
    char res[10];
    itos(f, &res);
    print(res);

    print_symbol('-');



    return 0;
}
