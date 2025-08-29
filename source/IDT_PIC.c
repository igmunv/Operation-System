#define PIC1_PORT 0x20

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

extern void tick_handler();
extern void asm_keyboard_handler();

static inline void idt_set(int n, void* h){
    unsigned int a = (unsigned int)h;
    IDT_table[n].low_bits = a & 0xFFFF;
    IDT_table[n].segm_sel = 0x08;
    IDT_table[n].always0 = 0;
    IDT_table[n].flags = 0x8E;
    IDT_table[n].high_bits = (a >> 16);
}

void IDT_reg_handler(int num, unsigned short segm_sel, unsigned short flags, intr_handler handler)
{
	unsigned int handler_addr = (unsigned int) handler;
	IDT_table[num].low_bits = (unsigned short) (handler_addr & 0xFFFF);
	IDT_table[num].segm_sel = segm_sel;
	IDT_table[num].always0 = 0;
	IDT_table[num].flags = flags;
	IDT_table[num].high_bits = (unsigned short) (handler_addr >> 16);
}

void IDT_load()
{
    int IDT_row_count = sizeof(IDT_table) / sizeof(IDT_table[0]);
    IDT_desc.base = (unsigned int)(&IDT_table[0]);
    IDT_desc.limit = (sizeof(struct IDT_row) * IDT_row_count) - 1;
    asm("lidt %0" : : "m" (IDT_desc));
}

void IDT_enable()
{
    asm("sti");
}

void IDT_disable()
{
    asm("cli");
}

void IDT_handlers_init(){
	IDT_reg_handler(32, 0x08, 0x80 | 0x0E, tick_handler);
    IDT_reg_handler(33, 0x08, 0x80 | 0x0E, asm_keyboard_handler);
	//outb(PIC1_PORT + 1, 0xFF ^ 0x01);
}

static inline void io_wait(void){ outb(0x80, 0); }

void PIC_remap(){
	unsigned char a1 = inb(0x21);
    unsigned char a2 = inb(0xA1);

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
