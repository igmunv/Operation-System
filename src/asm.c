void outb (unsigned short port, unsigned char byte){
	asm ("outb %b0, %w1" : : "a" (byte), "Nd" (port));
}

unsigned char inb (unsigned short port){
	unsigned char byte;
	asm ("inb %w1, %b0" : "=a" (byte) : "Nd" (port));
	return byte;
}

void outw(unsigned short port, unsigned short value) {
    asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}


// Write in registers

void in_ah(char byte){
	asm("movb %0, %%ah" : : "r"(byte) : "%ah");
}

void in_al(char byte){
	asm("movb %0, %%al" : : "r"(byte) : "%al");
}

void in_bh(char byte){
	asm("movb %0, %%bh" : : "r"(byte) : "%bh");
}

void in_bl(char byte){
	asm("movb %0, %%bl" : : "r"(byte) : "%bl");
}

void in_ch(char byte){
	asm("movb %0, %%ch" : : "r"(byte) : "%ch");
}

void in_cl(char byte){
	asm("movb %0, %%cl" : : "r"(byte) : "%cl");
}

void in_dh(char byte){
	asm volatile ("movb %0, %%dh" : : "r"(byte) : "%dh");
}

void in_dl(char byte){
	asm("movb %0, %%dl" : : "r"(byte) : "%dl");
}

// Read from registers

unsigned char get_ah(){
	unsigned char byte = 0;
	asm("movb %%ah, %0" : "=r"(byte) : :);
	return byte;
}

unsigned char get_al(){
	unsigned char byte = 0;
	asm("movb %%al, %0" : "=r"(byte) : :);
	return byte;
}


unsigned char get_bh(){
	unsigned char byte = 0;
	asm("movb %%bh, %0" : "=r"(byte) : :);
	return byte;
}

unsigned char get_bl(){
	unsigned char byte = 0;
	asm("movb %%bl, %0" : "=r"(byte) : :);
	return byte;
}

unsigned char get_ch(){
	unsigned char byte = 0;
	asm("movb %%ch, %0" : "=r"(byte) : :);
	return byte;
}

unsigned char get_cl(){
	unsigned char byte = 0;
	asm("movb %%cl, %0" : "=r"(byte) : :);
	return byte;
}

char get_dh(){
	char byte;
	asm volatile ("movb %%dh, %0" : "=r"(byte) : :);
	return byte;
}

unsigned char get_dl(){
	unsigned char byte = 0;
	asm("movb %%dl, %0" : "=r"(byte) : :);
	return byte;
}
