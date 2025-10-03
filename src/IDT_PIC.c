struct IDT_row
{
    unsigned short low_bits;
    unsigned short segm_sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short high_bits;
} __attribute__((packed));

struct IDT_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct IDT_row IDT_table[256];
struct IDT_ptr IDT_desc;

typedef void (*intr_handler)();

void IDT_reg_handler(int number, unsigned short segm_sel, unsigned short flags, intr_handler handler)
{
	unsigned int handler_addr = (unsigned int) handler;
	IDT_table[number].low_bits = (unsigned short) (handler_addr & 0xFFFF);
	IDT_table[number].segm_sel = segm_sel;
	IDT_table[number].always0 = 0;
	IDT_table[number].flags = flags;
	IDT_table[number].high_bits = (unsigned short) (handler_addr >> 16);
}

void IDT_load()
{
    int IDT_row_count = sizeof(IDT_table) / sizeof(IDT_table[0]);
    IDT_desc.base = (unsigned int)(&IDT_table[0]);
    IDT_desc.limit = (sizeof(struct IDT_row) * IDT_row_count) - 1;
    asm("lidt %0" : : "m" (IDT_desc));
}

void interrupt_enable()
{
    asm("sti");
}

void interrupt_disable()
{
    asm("cli");
}

static inline void io_wait(void){ outb(0x80, 0); }

void PIC_remap(){
    outb(0x20, 0x11); io_wait();   // ICW1
    outb(0xA0, 0x11); io_wait();

    outb(0x21, 0x20); io_wait();   // ICW2: master offset = 0x20
    outb(0xA1, 0x28); io_wait();   // ICW2: slave  offset = 0x28

    outb(0x21, 0x04); io_wait();   // ICW3: master has slave at IRQ2
    outb(0xA1, 0x02); io_wait();   // ICW3: slave cascade identity

    outb(0x21, 0x01); io_wait();   // ICW4: 8086 mode
    outb(0xA1, 0x01); io_wait();

    outb(0x21, 0b11111100);              // 11111110b
    outb(0xA1, 0xFF);
}
