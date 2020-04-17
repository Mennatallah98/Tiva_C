

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

    INTEnable(30);
    INTEnable(0);  //to test disable
    INTDisable(0);
    INT_status Int_30 = INTGetStatus(30);
    INT_status Int_0 = INTGetStatus(0);

    INTSetPending(0);
    INTSetPending(1);
    INTClearPending(1);
    INT_pending P_0 = INTGetPending(0);
    INT_pending P_1 = INTGetPending(1);

    Int_Activation A_0 = INTGetActivation(0);
    Int_Activation A_1 = INTGetActivation(1);
    Int_Activation A_30 = INTGetActivation(30);

    INTSoftwareTrigger(1);

    INTSetPriority(0,2);
    INTSetPriority(30,1);

	return 0;
}
