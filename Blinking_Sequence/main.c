

/**
 * main.c
 */

#include "GPIO.h"
#include "INT.h"
#include "Timer.h"

//GENERAL REFISTERS
ADDRESS RCC = 0x400FE060;
//*****************************************************************

#define SW1         0x10
#define Red_LED     0x02
#define Blue_LED    0x04
#define Green_LED   0x08

int counter=0;
int led_status=0xFF;

void Switch_pressed (void);
void Blinking (void);

int main(void)
{

                   /**********************clock******************************/
    *RCC &= ~(1<<0);   //Enable main OSC
    *RCC &= ~(1<<4);   //choosing main OSC
    *RCC |= (0x15<<11);//XTAl 16 MHz
    *RCC |= (1<<11);   //src OSC directly
    *RCC &= ~(1<<13);  //power down PLL
    *RCC &= ~(1<<22);  //no sysdiv
    //********************************************

                   /*********************************GPIO********************************/

    //BUS
    GPIOBusSet(PORTF,AHB);
    //CLK
    GPIOClockSet(PORTF);
    //Wait for GPIO to be ready to access
    ADDRESS reg = 0x400FEA08;
    while (*reg == 0)
        ; //after enabling the clock
    //MODE
    GPIODirModeSet(PORTF,SW1,MODE_IN,0);
    GPIODirModeSet(PORTF,Red_LED,MODE_OUT,0);
    GPIODirModeSet(PORTF,Blue_LED,MODE_OUT,0);
    GPIODirModeSet(PORTF,Green_LED,MODE_OUT,0);
    //PAD and DriverStr
    GPIOPadSet(PORTF,SW1,Drive_2mA,Pad_PU,En_Digital);
    GPIOPadSet(PORTF,Red_LED,Drive_8mA,PAD_NPU_NPD,En_Digital);
    GPIOPadSet(PORTF,Blue_LED,Drive_8mA,PAD_NPU_NPD,En_Digital);
    GPIOPadSet(PORTF,Green_LED,Drive_8mA,PAD_NPU_NPD,En_Digital);
    //GPIO Interrupt
    GPIOConfigINT(PORTF,SW1, Level, Falling_Low);
    UC sense = GPIOGetINTSense(PORTF, SW1);
    //**************************************************************************

                         /*********************************Interrupt********************************/
    INTEnable(PortF);
    INTSetPriority(PortF,1);
    IntSetFunctions(PortF, Switch_pressed);
    /*INTEnable(Timer1A_W);
    INTSetPriority(Timer1A_W,0);
    IntSetFunctions(Timer1A_W, Blinking);*/
    //*****************************************

                        /*********************************Timer********************************/
    TimerClkEnable(TIMERWide1);
    TimerSetConfig(TIMERWide1,Concatenated);
    TimerADisable(TIMERWide1);
    TimerASetMode(TIMERWide1,Periodic);
    TimerAMatchSetINT(TIMERWide1,Disable);
    TimerATriggerSet(TIMERWide1,Automatic);
    TimerACounterSetDirection(TIMERWide1,Up);
    TimerAStallSet(TIMERWide1,Disable);
    TimerALoadSetValue(TIMERWide1,48000000);
    TimerINTSetTrigger(TIMERWide1,TATOIM);
    TimerAEnable(TIMERWide1);

    while(1)
    {
       switch(counter)
       {
           case 0:
               GPIOWrite(PORTF,Red_LED,led_status);
               GPIOWrite(PORTF,Green_LED,0x00);
               GPIOWrite(PORTF,Blue_LED,0x00);
               break;
           case 1:
               GPIOWrite(PORTF,Red_LED,0x00);
               GPIOWrite(PORTF,Green_LED,led_status);
               GPIOWrite(PORTF,Blue_LED,0x00);
               break;
           case 2:
               GPIOWrite(PORTF,Red_LED,0x00);
               GPIOWrite(PORTF,Green_LED,0x00);
               GPIOWrite(PORTF,Blue_LED,led_status);
               break;
       }

    }

	return 0;
}

void Switch_pressed(void)
{
    //GPIOWrite(PORTF,Blue_LED,0xFF);
    if (counter==2)
        counter=0;
    else
        counter++;
   // GPIOClrINT (PORTF,SW1);
    while (GPIORead(PORTF,SW1)==0);
}

void Blinking (void)
{
    led_status ^= 0xFF;
    TimerINTClr(TIMERWide1, TATOIM);
}
