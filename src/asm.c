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
