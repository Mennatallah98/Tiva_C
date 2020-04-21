

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

    INTEnable(PortF);
    INTEnable(PortA);  //to test disable
    INTDisable(PortA);
    INT_status Int_30 = INTGetStatus(PortF);
    INT_status Int_0 = INTGetStatus(PortA);

    INTSetPending(PortA);
    INTSetPending(PortB);
    INTClearPending(1);
    INT_pending P_0 = INTGetPending(PortA);
    INT_pending P_1 = INTGetPending(PortB);

    Int_activation A_0 = INTGetActivation(PortA);
    Int_activation A_1 = INTGetActivation(PortB);
    Int_activation A_30 = INTGetActivation(PortF);

    INTSoftwareTrigger(1);

    INTSetPriority(PortA,2);
    INTSetPriority(PortF,1);

	return PortA;
}
