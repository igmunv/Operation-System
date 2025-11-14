#include "IDT_PIC.h"
#include "../libs/asm.h"

// Главная структура: хранит обработчик для конкретного прерывания
struct IDT_row
{
    unsigned short low_bits;
    unsigned short segm_sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short high_bits;
} __attribute__((packed));

// Указатель на главную структуру
struct IDT_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

// Инициализация структур
struct IDT_row IDT_table[256];
struct IDT_ptr IDT_desc;


unsigned char IRQ_MASTER_MASK = 0xff;
unsigned char IRQ_SLAVE_MASK = 0xff;

// Регистрация прерывания
void IDT_reg_handler(int number, unsigned short segm_sel, unsigned short flags, intr_handler handler)
{
	unsigned int handler_addr = (unsigned int) handler;
	IDT_table[number].low_bits = (unsigned short) (handler_addr & 0xFFFF);
	IDT_table[number].segm_sel = segm_sel;
	IDT_table[number].always0 = 0;
	IDT_table[number].flags = flags;
	IDT_table[number].high_bits = (unsigned short) (handler_addr >> 16);
}


// Загрузка таблицы прерываний
void IDT_load()
{
    int IDT_row_count = sizeof(IDT_table) / sizeof(IDT_table[0]);
    IDT_desc.base = (unsigned int)(&IDT_table[0]);
    IDT_desc.limit = (sizeof(struct IDT_row) * IDT_row_count) - 1;
    asm("lidt %0" : : "m" (IDT_desc));
}


// Разрешить/включить прерывания
void interrupt_enable()
{
    asm("sti");
}


// Запретить/выключить прерывания
void interrupt_disable()
{
    asm("cli");
}


void PIC_set_mask(unsigned char master, unsigned char slave){
    outb(0x21, master);
    outb(0xA1, slave);
}


// mst_sl - master или slave - 0: master - 1: slave
// bit - какой бит
// value - значение бита: 0 - 0, 1 - 1
// Меняет бит в маске на 0 или 1
void PIC_update_mask(unsigned char mst_sl, unsigned char bit, unsigned char value) {
    if (mst_sl == 0) {
        // Master
        if (value)
            IRQ_MASTER_MASK |= (1 << bit);   // ставим 1 - выключаем
        else
            IRQ_MASTER_MASK &= ~(1 << bit);  // ставим 0 - разрешаем
    } else if (mst_sl == 1) {
        // Slave
        if (value)
            IRQ_SLAVE_MASK |= (1 << bit); // ставим 1 - выключаем
        else
            IRQ_SLAVE_MASK &= ~(1 << bit); // ставим 0 - разрешаем
    }

    PIC_set_mask(IRQ_MASTER_MASK, IRQ_SLAVE_MASK);
}


//  Инициализация PIC для того, чтобы наши прерывания не пересекались с прерываниями процессора
void PIC_remap(){

    interrupt_disable();

    // IRQ - аппратная линия, по которому устройство может отправить прерывание

    // Master - управляет первой групой IRQ (0-7)
    // Slave - дополнительный, соединяется с Master по IRQ2 и обрабатывает вторую группу IRQ (8-15)

    // ICW - (Initialization Command Words) - управляющие команды, определяющие в каком режиме работать, куда кидать вектор прерывания, как связаны Master и Slave
    // Каждая ICW посылается через порты: 0x20/0x21 (master) и 0xA0/0xA1 (slave).


    // ICW1: начинаем инициализацию
    // 0x11 = 00010001b
    // бит 4 (1) - начинаем инициализацию
    // бит 0 (1) - будет ICW4, жди ICW4:
    outb(0x20, 0x11); in_out_wait(); // Master
    outb(0xA0, 0x11); in_out_wait(); // Slave


    // ICW2: задаём базовые адреа вектора прерываний. Самое важное
    // PIC выдает CPU номера векторов (0-15)
    // нужно сказать с какого номера начинать:
    // Master: 0x20 (т.е IRQ0 = 0x20, IRQ1 = 0x21...):
    outb(0x21, 0x20); in_out_wait();
    // Slave: 0x28 (т.е IRQ8 = 0x28, IRQ15 = 0x2F...):
    outb(0xA1, 0x28); in_out_wait();


    // ICW3: как master и slave соединены
    // Master: У меня есть Slave на линии IRQ2 (0x04 = 00000100. Т.е бит 2 (1) = IRQ2):
    outb(0x21, 0x04); in_out_wait();
    // Slave: Я подключен к мастеру через IRQ2 (0x02 - номер линии - IRQ2):
    outb(0xA1, 0x02); in_out_wait();

    // ICW4: режим работы
    // Итого: работай в обычном 8086-совместимом режиме
    // Бит 0 = 1 - 8086/88 mode (совеременные CPU):
    outb(0x21, 0x01); in_out_wait();
    // Бит 4 = 0 - не использовать "special fully nested mode":
    outb(0xA1, 0x01); in_out_wait();


    // Master: разрешаем только прерывания PIT (IRQ0) и клавиатуры (IRQ1)
    // Расшифровка (11111100):
    // бит 7 — IRQ7  (1 → выключен)
    // бит 6 — IRQ6  (1 → выключен)
    // бит 5 — IRQ5  (1 → выключен)
    // бит 4 — IRQ4  (1 → выключен)
    // бит 3 — IRQ3  (1 → выключен)
    // бит 2 — IRQ2  (1 → выключен)
    // бит 1 — IRQ1  (0 → включен)
    // бит 0 — IRQ0  (0 → включен)
    PIC_set_mask(0b11111111, 0xFF);
    // Slave: всё выключено
    // Расшифровка (1111111):
    // бит 0-7 — IRQ8-IRQ15 (1 - выключен)

    interrupt_enable();

}
