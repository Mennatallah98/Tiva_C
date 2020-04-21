

/**
 * main.c
 */

//this program blinks the blue led and lights in the red led when SW1 is pressed

#define SW1        0x10
#define Red_LED    0x02
#define Blue_LED   0x04

#include "GPIO.h"
#include "INT.h"

//GENERAL REFISTERS
ADDRESS RCC = 0x400FE060;
//*****************************************************************

void INT_funtion (void);

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
    //******************************

    //CLK
    GPIOClockSet(PORTF);
    //***************************

    //Wait for GPIO to be ready to access
    ADDRESS reg = 0x400FEA08;
    while (*reg == 0)
        ; //after enabling the clock
    //*******************************

    //MODE
    GPIODirModeSet(PORTF,SW1,MODE_IN);
    GPIODirModeSet(PORTF,Red_LED,MODE_OUT);
    GPIODirModeSet(PORTF,Blue_LED,MODE_OUT);
    //*******************************************

    //PAD and DriverStr
    GPIOPadSet(PORTF,SW1,Drive_2mA,Pad_PU,En_Digital);
    GPIOPadSet(PORTF,Red_LED,Drive_8mA,PAD_NPU_NPD,En_Digital);
    GPIOPadSet(PORTF,Blue_LED,Drive_8mA,PAD_NPU_NPD,En_Digital);
    //***************************************************************

    //GPIO Interrupt
    GPIOConfigINT(PORTF,SW1, Level, Falling_Low);
    UC sense = GPIOGetINTSense(PORTF, SW1);
    //**************************************************************************

    //Interrupt
    INTEnable(PortF);
    INTSetPriority(PortF,0);
    IntSetFunctions(PortF, INT_funtion);
    //*****************************************

    //GPIOWrite(PORTF,Blue_LED,0xff);
    while(1)
    {
        int i;
        GPIOWrite(PORTF,Red_LED,0x00);

        GPIOWrite(PORTF,Blue_LED,0xff);
        for(i=0;i<=1000000;i++);

        GPIOWrite(PORTF,Blue_LED,0x00);
        for(i=0;i<=1000000;i++);

    }

	return 0;
}

void INT_funtion (void)
{
    GPIOWrite(PORTF,Red_LED,0xff);
    GPIOWrite(PORTF,Blue_LED,0x00);

}
