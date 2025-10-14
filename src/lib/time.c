// Special memory: ticks
volatile unsigned long* ticks = (unsigned long*)0x5018;


// Уснуть, ждать
void sleep(int ms){
    unsigned long ticks_local = *ticks;
    while (((*ticks)-ticks_local) <= ms){}
}
