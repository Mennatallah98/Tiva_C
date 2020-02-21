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
    ADDRESS reg=GPIOHBCTL;
    ULI data= *reg;
    if(bus==AHB)
    {
        SET_BIT(data, port);
    }
    else if (bus==APB)
    {
        CLR_BIT(data, port);
    }
}

gpio_bus GPIOBusGet(gpio_port port)
{
    ADDRESS reg=GPIOHBCTL;
    ULI data= *reg;
    return GET_BIT(data, port);
}
//************************************************************

//Function that adds the offset of the desired register with the chosen port
ADDRESS GPIOSetAddress(gpio_port port, ULI reg)
{
    gpio_bus bus= GPIOBusGet(port);
    ADDRESS desired_port;
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
    ADDRESS final_reg= reg + desired_port;
    return final_reg;
}
//*********************************************************************************

//clock functions
void GPIOClockSet(gpio_port port)
{
    ADDRESS reg = GPIOSetAddress(port, RCGCGPIO);
    ULI data = *reg;
    SET_BIT(data, port);
}

void GPIOClockRst(gpio_port port)
{
    ADDRESS reg = GPIOSetAddress(port, RCGCGPIO);
    ULI data = *reg;
    CLR_BIT(data, port);
}

char GPIOClockGet(gpio_port port)
{
    ADDRESS reg = GPIOSetAddress(port, RCGCGPIO);
    ULI data = *reg;
    return GET_BIT(data, port);
}
//**********************************************************************************

//Mode functions
void GPIODirModeSet(gpio_port port, unsigned char pins, gpio_mode Mode)
{
    ADDRESS reg_AF = GPIOSetAddress(port, GPIOAFSEL);
    ADDRESS reg_DIR = GPIOSetAddress(port, GPIODIR);

    ULI data_AF = *reg_AF;
    ULI data_DIR = *reg_DIR;

    data_AF &= ~(pins);
    if (Mode == MODE_AF)
        SET_BITS(data_AF,pins);
    else
        CLR_BITS(data_AF,pins);

    data_DIR &= ~(pins);
    data_DIR |= (Mode & pins);
}

unsigned char GPIODirGet(gpio_port port, unsigned char pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIOAFSEL);
    ULI data =*reg;
    unsigned char data_get = (data&pins);

    return data_get;
}

unsigned char GPIOModeGet(gpio_port port, unsigned char pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIODIR);
    ULI data =*reg;

    unsigned char data_get = (data&pins);
    return data_get;
}
//****************************************************************************************

//Pad and drive functions
void GPIOPadSet(gpio_port port, unsigned char pins, gpio_drive str, gpio_pad pad)
{
    //Drive functions
    ADDRESS reg_2drive = GPIOSetAddress(port, GPIODR2R);
    ADDRESS reg_4drive = GPIOSetAddress(port, GPIODR4R);
    ADDRESS reg_8drive = GPIOSetAddress(port, GPIODR8R);
    ADDRESS reg_slew8drive = GPIOSetAddress(port, GPIOSLR);

    ULI data_2drive = *reg_2drive;
    ULI data_4drive = *reg_4drive;
    ULI data_8drive = *reg_8drive;
    ULI data_slew8drive = *reg_slew8drive;

    if (str==Drive_2mA)
    {
        data_2drive &= ~(pins);
        SET_BITS(data_2drive, pins);
    }
    else if (str==Drive_4mA)
    {
        data_4drive &= ~(pins);
        SET_BITS(data_4drive, pins);
    }

    else if (str==Drive_8mA)
    {
        data_8drive &= ~(pins);
        data_slew8drive &= ~(pins);
        SET_BITS(data_8drive, pins);
        CLR_BITS(data_slew8drive, pins);
    }

    else if (str==Drive_8mA)
    {
        data_8drive &= ~(pins);
        data_slew8drive &= ~(pins);
        SET_BITS(data_8drive, pins);
        SET_BITS(data_slew8drive, pins);
    }
    //**********************************************************************************

    //PAD functions
    ADDRESS reg_PU = GPIOSetAddress(port, GPIOPUR) ;
    ADDRESS reg_PD = GPIOSetAddress(port, GPIOPDR) ;
    ADDRESS reg_OD = GPIOSetAddress(port, GPIOODR) ;

    ULI data_PU = *reg_PU;
    ULI data_PD = *reg_PD;
    ULI data_OD = *reg_OD;

    if (pad==Pad_PU)
    {
        data_PU &= ~(pins);
        SET_BITS(data_PU, pins);
    }
    else if (pad==Pad_PD)
    {
        data_PD &= ~(pins);
        SET_BITS(data_PD, pins);
    }
    else if (pad==PAD_NPU_NPD)
    {
        data_PD &= ~(pins);
        data_PU &= ~(pins);
        CLR_BITS(data_PD, pins);
        CLR_BITS(data_PU, pins);
    }
    else if (pad==PAD_OD)
    {
        data_OD &= ~(pins);
        SET_BITS(data_OD, pins);
    }
    //**********************************************************************
}

unsigned char GPIOPadOpenDrainGet(gpio_port port, unsigned char pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIOODR);
    ULI data = *reg;
    unsigned char data_get = (data&pins);
    return data_get;
}

unsigned char GPIOPadPullUpGet(gpio_port port, unsigned char pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIOPUR);
    ULI data = *reg;
    unsigned char data_get = (data&pins);
    return data_get;
}

unsigned char GPIOPadPullDownGet(gpio_port port, unsigned char pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIOPDR);
    ULI data = *reg;
    unsigned char data_get = (data&pins);
    return data_get;
}

//Read and Write functions
unsigned char GPIORead(gpio_port port, unsigned char pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIODATA);
    ULI data = *reg;
    ULI reg_shifted = ((reg<<2)&pins);
    unsigned char data_get = (data&reg_shifted);

    return data_get;
}

void GPIOWrite(gpio_port port, unsigned char pins, unsigned char written_data)
{
    ADDRESS reg = GPIOSetAddress(port, GPIODATA);
    ULI data = *reg;
    ULI reg_shifted = ((reg<<2)&pins);
    data = (reg_shifted & written_data);
}
//**************************************************************
