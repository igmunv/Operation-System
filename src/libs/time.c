#include "time.h"

// Уснуть, ждать
void sleep(int ms){
    unsigned long ticks_local = TICKS;
    while ((TICKS-ticks_local) <= ms){}
}
