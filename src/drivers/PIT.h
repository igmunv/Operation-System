#ifndef INCL_DRIVER_PIT
#define INCL_DRIVER_PIT

void PIT_init(unsigned int freq_hz);
void tick_handler();

#endif
