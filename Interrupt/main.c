

/**
 * main.c
 */
#define REG volatile unsigned long int *
#include "INT.h"
//GENERAL REFISTERS
REG RCC = 0x400FE060;   //base+offset  //volatile--> no optimization , depends on hardware
REG GPIOHBCTL = 0x400FE06C;
REG RCGCGPIO = 0x400FE608;
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

    INTSetEnable(5);

	return 0;
}
