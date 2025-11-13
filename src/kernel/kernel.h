#ifndef KERNEL
#define KERNEL

extern unsigned int EXECUTE_PROGRAM;

void kernel_log(unsigned char* text);
void kernel_panic(unsigned char* where_function, unsigned char* text);
void kmain(void);

#endif
