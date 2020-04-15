/*
 * GPIO.c
 *
 *  Created on: 20 Mar 2020
 *      Author: Mennatallah
 */

#ifndef GPIO_C_
#define GPIO_C_

#include "GPIO.h"

//Port addresses arrays
ADDRESS AHB_Ports[] = {PORTA_AHB, PORTB_AHB, PORTC_AHB, PORTD_AHB, PORTE_AHB, PORTF_AHB};
ADDRESS APB_Ports[] = {PORTA_APB, PORTB_APB, PORTC_APB, PORTD_APB, PORTE_APB, PORTF_APB};
//*****************************************************************


//Bus functions
void GPIOBusSet(gpio_port port,gpio_bus bus)
{
    ADDRESS reg = GPIOHBCTL;
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
    ADDRESS reg=GPIOHBCTL;
    return GET_BIT(reg, port);
}
//**********************************************************


//clock functions
void GPIOClockSet(gpio_port port)
{
    ADDRESS reg =  RCGCGPIO;
    SET_BIT(reg, port);
}

void GPIOClockRst(gpio_port port)
{
    ADDRESS reg =  RCGCGPIO;
    CLR_BIT(reg, port);
}

UC GPIOClockGet(gpio_port port)
{
    ADDRESS reg =  RCGCGPIO;
    return GET_BIT(reg, port);
}
//***************************************************************

//Function that adds the offset of the desired register with the chosen port
ULI GPIOSetAddress(gpio_port port, ULI reg )
{
    gpio_bus bus= GPIOBusGet(port);
    ULI desired_port;
    if (bus==AHB)
    {
       desired_port = AHB_Ports[port];
    }
    else if (bus==APB)
     {
        desired_port = APB_Ports[port];
     }
    ULI final_reg = desired_port+reg;
    return final_reg;
}
//*********************************************************************************

//Mode functions
void GPIODirModeSet(gpio_port port, UC pins, gpio_mode Mode)
{
    //AF
    ADDRESS reg = GPIOSetAddress(port,GPIOAFSEL);
    *reg &= ~(pins);
    if (Mode == MODE_AF)
        SET_BITS(reg,pins);
    else
        CLR_BITS(reg,pins);
    //DIR
    reg = GPIOSetAddress(port,GPIODIR);
    ULI data = *reg;
    data &= ~(pins);
    data |= (Mode & pins);
    *reg=data;
}
UC GPIODirGet(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port,GPIODIR);
    ULI data =*reg;
    return (data&pins);
}

UC GPIOModeGet(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port,GPIOAFSEL);
    ULI data =*reg;
    return (data&pins);
}
//*********************************************************************************************

//Pad and drive functions
void GPIOPadSet(gpio_port port, UC pins, gpio_drive str, gpio_pad pad, gpio_enable enable)
{
    //Drive functions
    ADDRESS reg_2drive = GPIOSetAddress(port, GPIODR2R);
    ADDRESS reg_4drive = GPIOSetAddress(port, GPIODR4R);
    ADDRESS reg_8drive = GPIOSetAddress(port, GPIODR8R);
    ADDRESS reg_slew8drive = GPIOSetAddress(port, GPIOSLR);

    if (str==Drive_2mA)
    {
        *reg_2drive &= ~(pins);
        SET_BITS(reg_2drive, pins);
    }
    else if (str==Drive_4mA)
    {
        *reg_4drive &= ~(pins);
        SET_BITS(reg_4drive, pins);
    }

    else if (str==Drive_8mA)
    {
        *reg_8drive &= ~(pins);
        *reg_slew8drive &= ~(pins);
        SET_BITS(reg_8drive, pins);
        CLR_BITS(reg_slew8drive, pins);
    }

    else if (str==Drive_8mA)
    {
        *reg_8drive &= ~(pins);
        *reg_slew8drive &= ~(pins);
        SET_BITS(reg_8drive, pins);
        SET_BITS(reg_slew8drive, pins);
    }
    //**********************************************************************************

    //PAD functions
    ADDRESS reg_PU = GPIOSetAddress(port, GPIOPUR) ;
    ADDRESS reg_PD = GPIOSetAddress(port, GPIOPDR) ;
    ADDRESS reg_OD = GPIOSetAddress(port, GPIOODR) ;

    if (pad==Pad_PU)
    {
        *reg_PU &= ~(pins);
        SET_BITS(reg_PU, pins);
    }
    else if (pad==Pad_PD)
    {
        *reg_PD &= ~(pins);
        SET_BITS(reg_PD, pins);
    }
    else if (pad==PAD_NPU_NPD)
    {
        *reg_PD &= ~(pins);
        *reg_PU &= ~(pins);
        CLR_BITS(reg_PD, pins);
        CLR_BITS(reg_PU, pins);
    }
    else if (pad==PAD_OD)
    {
        *reg_OD &= ~(pins);
        SET_BITS(reg_OD, pins);
    }
    //**********************************************************************

    //Enabling
    ADDRESS reg_Dig = GPIOSetAddress(port, GPIODEN);
    ADDRESS reg_Ang = GPIOSetAddress(port, GPIOAMSEL);
    if(enable==En_Digital)
    {
        *reg_Dig &= ~(pins);
        SET_BITS(reg_Dig, pins);
    }
    else if(enable==En_Analog)
    {
        *reg_Ang &= ~(pins);
        SET_BITS(reg_Ang, pins);
    }
}
UC GPIOPadDriveStr2Get(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIODR2R);
    ULI data = *reg;
    return (data&pins);
}
UC GPIOPadDriveStr4Get(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIODR4R);
    ULI data = *reg;
    return (data&pins);
}
UC GPIOPadDriveStr8Get(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIODR8R);
    ULI data = *reg;
    return (data&pins);
}
UC GPIOPadDriveStrSlewGet(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIOSLR);
    ULI data = *reg;
    return (data&pins);
}
UC GPIOPadOpenDrainGet(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIOODR);
    ULI data = *reg;
    return (data&pins);
}

UC GPIOPadPullUpGet(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIOPUR);
    ULI data = *reg;
    return (data&pins);
}

UC GPIOPadPullDownGet(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIOPDR);
    ULI data = *reg;
    return (data&pins);
}
//****************************************************************************************

//Read and Write functions
UC GPIORead(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port, GPIODATA);
    ULI data = *reg;
    ULI reg_address = reg;
    ULI reg_shifted = ((pins<<2)|reg_address);
    UC data_get = (data&reg_shifted);

    return data_get;
}

void GPIOWrite(gpio_port port, UC pins, UC written_data)
{
    ADDRESS reg = GPIOSetAddress(port, GPIODATA);
    ULI data = *reg;
    ULI reg_address = reg;
    ULI reg_shifted = ((pins<<2)|reg_address);
    data = (reg_shifted & written_data);
    *reg=data;
}
//**************************************************************


#endif /* GPIO_C_ */
