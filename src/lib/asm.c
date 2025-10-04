// Полезные ASM функции
void outb (unsigned short port, unsigned char byte){
	asm volatile ("outb %b0, %w1" : : "a" (byte), "Nd" (port));
}

unsigned char inb (unsigned short port){
	unsigned char byte;
	asm volatile ("inb %w1, %b0" : "=a" (byte) : "Nd" (port));
	return byte;
}

void outw(unsigned short port, unsigned short value) {
    asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

// Write in 8-bit registers
extern void in_ah(unsigned char byte);
extern void in_al(unsigned char byte);
extern void in_bh(unsigned char byte);
extern void in_bl(unsigned char byte);
extern void in_ch(unsigned char byte);
extern void in_cl(unsigned char byte);
extern void in_dh(unsigned char byte);
extern void in_dl(unsigned char byte);

// Write in 16-bit registers
extern void in_ax(short word);
extern void in_bx(short word);
extern void in_cx(short word);
extern void in_dx(short word);

// Write in 32-bit registers
extern void in_ebx(int dword);
extern void in_esi(int dword);

// Read from 8-bit registers
extern unsigned char get_ah();
extern unsigned char get_al();
extern unsigned char get_bh();
extern unsigned char get_bl();
extern unsigned char get_ch();
extern unsigned char get_cl();
extern unsigned char get_dh();
extern unsigned char get_dl();

// Read from 16-bit registers
extern short get_ax();
extern short get_bx();
extern short get_cx();
extern short get_dx();

// Read from 32-bit registers
extern int get_ebx();
extern int get_esi();

// Clear 8-bit registers
extern void clear_ah();
extern void clear_al();
extern void clear_bh();
extern void clear_bl();
extern void clear_ch();
extern void clear_cl();
extern void clear_dh();
extern void clear_dl();

// Clear 16-bit registers
extern void clear_ax();
extern void clear_bx();
extern void clear_cx();
extern void clear_dx();
