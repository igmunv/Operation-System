#ifndef INCL_DRIVER_PIT
#define INCL_DRIVER_PIT

extern unsigned int TICKS;

void PIT_init(unsigned int freq_hz);
void tick_handler();

#endif
