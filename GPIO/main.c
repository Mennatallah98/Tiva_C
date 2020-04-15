

/**
 * main.c
 */

//this program turns on the led red when SW1 is pressed

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
    GPIODirModeSet(PORTF,0x02,MODE_OUT); //red led
    GPIODirModeSet(PORTF,0x10,MODE_IN);  //switch 1
    GPIODirModeSet(PORTF,0x80,MODE_AF);  //just for testing the get function
    UC dir = GPIODirGet(PORTF,0xff);
    UC mode = GPIOModeGet(PORTF,0xff);
    //*******************************************

    //PAD and DriverStr
    GPIOPadSet(PORTF,0x02,Drive_8mA,PAD_NPU_NPD,En_Digital);
    GPIOPadSet(PORTF,0x10,Drive_2mA,Pad_PU,En_Digital);
    //********************************************************

    //GPIOWrite(PORTF,0x02,0xff);
    //int switch_1 = GPIORead(PORTF,0x10);
    while(1)
    {
        //Read and write functions
        if(GPIORead(PORTF,0x10)==0)
        {
            GPIOWrite(PORTF,0x02,0xff);
        }
        else
        {
            GPIOWrite(PORTF,0x02,0x00);
        }
    }

	return 0;
}
