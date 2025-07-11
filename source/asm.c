void outb(int port, char value){
	asm ( 
		"outb %1, %0"
		:
		:"dN" (port), "a" (value)
		);
}

unsigned char inb(int port){
	unsigned char byte;
	asm ( 
		"inb %1, %0"
		: "=a" (byte)
		: "dN" (port) 
		: "memory"
		);
	return byte;
}

void sleep(int takt_num){
	asm (
		"mov %0, %%ecx\n\t"
		"delay:\n\t"
		"pause\n\t"
		"loop delay\n\t"
		:
		:"r"(takt_num)
		:"ecx"
		);
}