

/**
 * main.c
 */

#include "GPIO.h"

int main(void)
{
    //clock
        //BYPASS
        *RCC |= (1<<11);   //*--> want to change what the address points to  //|-->to set
        //USESYSDIV
        *RCC &= ~(1<<22);  //&-->to clear
        //OSCSRC
        *RCC &= ~(1<<5);   //internal clock
        *RCC |= (1<<4);
        //PWDRN
        *RCC &= ~(1<<13);
    //*******************************************************

	return 0;
}
