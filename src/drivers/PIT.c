#define PIT_CMD  0x43
#define PIT_CH0  0x40
#define PIT_INPUT_FREQ 1193182UL

volatile unsigned long ticks = 0;

void PIT_init(unsigned int freq_hz) {
    unsigned int divisor = (unsigned int)(PIT_INPUT_FREQ / freq_hz); // 1193182 / freq
    unsigned char lo = divisor & 0xFF;
    unsigned char hi = (divisor >> 8) & 0xFF;

    // Mode 3 (square wave), access lobyte/hibyte, channel 0
    outb(PIT_CMD, 0x36);

    // write divisor low then high
    outb(PIT_CH0, lo);
    outb(PIT_CH0, hi);
}

void tick_handler(){
	ticks++;
	outb(0x20, 0x20);
}
