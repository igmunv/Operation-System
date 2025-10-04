

// Уснуть, ждать
void sleep(int ms){
    unsigned long long ticks_local = ticks;
    while ((ticks-ticks_local) <= ms){asm("hlt");}
}
