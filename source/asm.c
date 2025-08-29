void outb (unsigned short port, unsigned char byte){
	asm ("outb %b0, %w1" : : "a" (byte), "Nd" (port));
}

unsigned char inb (unsigned short port){
	unsigned char byte;
	asm ("inb %w1, %b0" : "=a" (byte) : "Nd" (port));
	return byte;
}
