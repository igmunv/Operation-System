#ifndef INCL_LIB_ASM
#define INCL_LIB_ASM

// Полезные ASM функции
void outb (unsigned short port, unsigned char byte);
void outw(unsigned short port, unsigned short value);
unsigned char inb (unsigned short port);
unsigned short inw (unsigned short port);

// Write in 8-bit registers
void in_ah(unsigned char byte);
void in_al(unsigned char byte);
void in_bh(unsigned char byte);
void in_bl(unsigned char byte);
void in_ch(unsigned char byte);
void in_cl(unsigned char byte);
void in_dh(unsigned char byte);
void in_dl(unsigned char byte);

// Write in 16-bit registers
void in_ax(short word);
void in_bx(short word);
void in_cx(short word);
void in_dx(short word);
void in_si(short word);

// Write in 32-bit registers
void in_ebx(int dword);
void in_edx(int dword);
void in_esi(int dword);

// Read from 8-bit registers
unsigned char get_ah();
unsigned char get_al();
unsigned char get_bh();
unsigned char get_bl();
unsigned char get_ch();
unsigned char get_cl();
unsigned char get_dh();
unsigned char get_dl();

// Read from 16-bit registers
unsigned short get_ax();
unsigned short get_bx();
unsigned short get_cx();
unsigned short get_dx();
unsigned short get_si();

// Read from 32-bit registers
int get_ebx();
int get_edx();
int get_esi();

// Clear 8-bit registers
void clear_ah();
void clear_al();
void clear_bh();
void clear_bl();
void clear_ch();
void clear_cl();
void clear_dh();
void clear_dl();

// Clear 16-bit registers
void clear_ax();
void clear_bx();
void clear_cx();
void clear_dx();

#endif
