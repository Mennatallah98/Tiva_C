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
    return data;
}
UC GPIODirGet(gpio_port port, UC pins)
{
    ADDRESS reg = GPIOSetAddress(port,GPIODIR);
    ULI data =*reg;
    return (data&pins);
}

#endif /* GPIO_C_ */
