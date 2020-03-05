

/**
 * main.c
 */

#include "StdFunctions.h"

//ABBRIVIATIONS
#define REG volatile unsigned long int *
#define F_BASE 0x4005D000
#define FB(offset) F_BASE+offset
//*****************************************************

//GENERAL REFISTERS
REG RCC       = 0x400FE060;   //base+offset  //volatile--> no optimization , depends on hardware
REG GPIOHBCTL = 0x400FE06C;
REG RCGCGPIO  = 0x400FE608;
REG EN0       = 0xE000E100;
//*****************************************************************

//F RELATED REGISTERS
REG GPIODIR_F   = FB(0X400);
REG GPIOAFSEL_F = FB(0X420);
REG GPIODR8R_F  = FB(0X508);
REG GPIDOEN_F   = FB(0X51C);
REG GPIODATA_F1 = FB(0X008);
REG GPIOIS_F    = FB(0x404);
REG GPIOIM_F    = FB(0x410);
REG GPIOIBE_F   = FB(0x408);
REG GPIOIEV_F   = FB(0x40C);

//********************************************************************************

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

    //PORTF
    * GPIOHBCTL |= (1<<5);  //port F in AHB

    //R5
    *RCGCGPIO |= (1<<5); //Enables clock for port F

    //DIR
    *GPIODIR_F |= (1<<1); //1-->output

    //AFSEL
    *GPIOAFSEL_F &= ~(1<<1); //0-->GPIO

    //DRV8
    *GPIODR8R_F |= (1<<1) ;  //1--> 8mA driven


    //DEN
    *GPIDOEN_F |= (1<<1);   //1-->enables digital function

    //DATA
    *GPIODATA_F1 |= (1<<1); //it will change only the bits written to 1  //0b00000010

    //INT enable
    SET_BIT(*EN0,29);

    //F INT type
    SET_BIT(*GPIOIS_F,4); //level
    CLR_BIT(*GPIOIS_F,0); //edge

    //F Both edges
    CLR_BIT(*GPIOIBE_F,0);
    CLR_BIT(*GPIOIBE_F,4);

    //F High or Low Rising or Falling
    SET_BIT(*GPIOIEV_F,0); //rising
    SET_BIT(*GPIOIEV_F,4); //high

    //F INT Masking
    SET_BIT(*GPIOIM_F,0);
    SET_BIT(*GPIOIM_F,4);


    return 0;
}

void PortF_ISR(void)
{
    *GPIODATA_F1 |= (0<<1);
}
