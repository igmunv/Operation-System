// Special memory: ticks
volatile unsigned long* ptticks = (unsigned long*)0x5018;


// Уснуть, ждать
void sleep(int ms){
    unsigned long long ticks_local = *ptticks;
    while ((*ptticks-ticks_local) <= ms){asm("hlt");}
}
