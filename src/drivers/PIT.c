#define PIT_CMD  0x43
#define PIT_CH0  0x40
#define PIT_INPUT_FREQ 1193182UL

#include "PIT.h"
#include "../libs/shared_memory.h"

// Количество тиков с момента запуска
volatile unsigned long ticks __attribute__((section(".os_data"))) = 0;


// Инициализация таймера PIT
void PIT_init(unsigned int freq_hz) {

    // Выставляем заданную в freq_hz частоту (количество тиков в секунду)

    unsigned int divisor = (unsigned int)(PIT_INPUT_FREQ / freq_hz); // 1193182 / freq
    unsigned char lo = divisor & 0xFF;
    unsigned char hi = (divisor >> 8) & 0xFF;

    // Mode 3 (square wave), access lobyte/hibyte, channel 0
    outb(PIT_CMD, 0x36);

    // write divisor low then high
    outb(PIT_CH0, lo);
    outb(PIT_CH0, hi);
}

// Обработчик прерывания PIT
void tick_handler(){
	TICKS++;
	outb(0x20, 0x20);
}
