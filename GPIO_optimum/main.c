

/**
 * main.c
 */

#include "GPIO.h"
//GENERAL REFISTERS
ADDRESS RCC = 0x400FE060;   //base+offset  //volatile--> no optimization , depends on hardware
//*****************************************************************

int main(void)
{
    //BYPASS
    *RCC |= (1<<11);   //*--> want to change what the address points to  //|-->to set
    //USESYSDIV
    *RCC &= ~(1<<22);  //&-->to clear
    //OSCSRC
    *RCC &= ~(1<<5);   //internal clock
    *RCC |= (1<<4);
    //PWDRN
    *RCC &= ~(1<<13);

    GPIOBusSet(PORTF,AHB);
    //gpio_bus bus = GPIOBusGet(PORTF);

    return 0;
}
