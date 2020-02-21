/*
 * GPIO.C
 *
 *  Created on: 20 Feb 2020
 *      Author: Mennatallah
 */

#include "GPIO.h"

//Bus functions
void GPIOBusSet(gpio_port port,gpio_bus bus)
{
    unsigned long int reg=GPIOHBCTL;
    if(bus==AHB)
    {
        SET_BIT(reg, port);
    }
    else if (bus==APB)
    {
        CLR_BIT(reg, port);
    }
}

gpio_bus GPIOBusGet(gpio_port port)
{
    unsigned long int reg=GPIOHBCTL;
    return GET_BIT(reg, port);
}
//************************************************************

//Function that adds the offset of the desired register with the chosen port
unsigned long int GPIOSetAddress(gpio_port port, unsigned long int reg)
{
    gpio_bus bus= GPIOBusGet(port);
    unsigned long int desired_port;
    if (bus==AHB)
    {
       if (port==PORTA)
       {
           desired_port=PORTA_AHB;
       }
       else if (port==PORTB)
       {
           desired_port=PORTB_AHB;
       }
       else if (port==PORTC)
       {
           desired_port=PORTC_AHB;
       }
       else if (port==PORTD)
       {
           desired_port=PORTD_AHB;
       }
        else if (port==PORTE)
        {
            desired_port=PORTE_AHB;
        }
        else if (port==PORTF)
        {
            desired_port=PORTF_AHB;
        }
    }
    else if (bus==APB)
     {
        if (port==PORTA)
        {
            desired_port=PORTA_APB;
        }
        else if (port==PORTB)
        {
            desired_port=PORTB_APB;
        }
        else if (port==PORTC)
        {
            desired_port=PORTC_APB;
        }
        else if (port==PORTD)
        {
            desired_port=PORTD_APB;
        }
         else if (port==PORTE)
         {
             desired_port=PORTE_APB;
         }
         else if (port==PORTF)
         {
             desired_port=PORTF_APB;
         }
     }
    unsigned long int final_reg= reg + desired_port;
    return final_reg;
}
//*********************************************************************************

//clock functions
void GPIOClockSet(gpio_port port)
{
    unsigned long int reg = GPIOSetAddress(port, RCGCGPIO);
    SET_BIT(reg, port);
}

void GPIOClockRst(gpio_port port)
{
    unsigned long int reg = GPIOSetAddress(port, RCGCGPIO);
    CLR_BIT(reg, port);
}

char GPIOClockGet(gpio_port port)
{
    unsigned long int reg = GPIOSetAddress(port, RCGCGPIO);
    return GET_BIT(reg, port);
}
//**********************************************************************************

//Mode functions
void GPIODirModeSet(gpio_port port, unsigned char pins, gpio_mode Mode)
{
    unsigned long int reg_AF = GPIOSetAddress(port, GPIOAFSEL);
    unsigned long int reg_DIR = GPIOSetAddress(port, GPIODIR);

    reg_AF &= ~(pins);
    if (Mode == MODE_AF)
        reg_AF |= (0xff & pins);
    else
        reg_AF |= (0x00 & pins);

    reg_DIR &= ~(pins);
    reg_DIR |= (Mode & pins);
}

unsigned char GPIODirGet(gpio_port port, unsigned char pins)
{
    unsigned long int reg = GPIOSetAddress(port, GPIODIR);

    reg &= pins;
    return reg;
}

unsigned char GPIOModeGet(gpio_port port, unsigned char pins)
{
    unsigned long int reg = GPIOSetAddress(port, GPIOAFSEL);

      reg &= pins;
      return reg;
}
//****************************************************************************************

//Pad functions
void GPIOPadSet(gpio_port port, unsigned char pins, gpio_drive str, gpio_pad pad)
{

}
