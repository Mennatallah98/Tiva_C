

/**
 * main.c
 */

#include "GPIO.h"
//GENERAL REFISTERS
ADDRESS RCC = 0x400FE060;   //base+offset  //volatile--> no optimization , depends on hardware
//*****************************************************************

int main(void)
{
    //Setting clk
    //BYPASS
    *RCC |= (1<<11);   //*--> want to change what the address points to  //|-->to set
    //USESYSDIV
    *RCC &= ~(1<<22);  //&-->to clear
    //OSCSRC
    *RCC &= ~(1<<5);   //internal clock
    *RCC |= (1<<4);
    //PWDRN
    *RCC &= ~(1<<13);
    //******************************************************************

    //BUS
    GPIOBusSet(PORTF,AHB);
    gpio_bus bus = GPIOBusGet(PORTF);
    //******************************

    //CLK
    GPIOClockSet(PORTF);
    UC clk = GPIOClockGet(PORTF);
    //***************************

    //Wait for GPIO to be ready to access
    ADDRESS reg = 0x400FEA08;
    while (*reg == 0)
        ; //after enabling the clock
    //*******************************

    //MODE
    GPIODirModeSet(PORTF,0xff,MODE_OUT);
    //UC dir = GPIODirGet(PORTF,0xff);

	return 0;
}
