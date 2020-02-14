/*
 * GPIO.c
 *
 *  Created on: 14 Feb 2020
 *      Author: Mennatallah
 */

#include "GPIO.h"

//MODE OF OPERATION
/*
 It enables the user to choose whether to work in APB mode which is compatible with older versions or
 AHB mode which gives the tiva c more capabilities
 */
/*mode
 * ABP
 * AHB
 */
void GPIO_MODE_OF_OPERATION (int mode)
{
 if(mode==ABP)
   {
       A_BASE=0x40004000;
       B_BASE=0x40005000;
       C_BASE=0x40006000;
       D_BASE=0x40007000;
       E_BASE=0x40024000;
       F_BASE=0x40025000;
   }
   else if(mode==AHB)
   {
       A_BASE=0x40058000;
       B_BASE=0x40059000;
       C_BASE=0x4005A000;
       D_BASE=0x4005B000;
       E_BASE=0x4005C000;
       F_BASE=0x4005D000;
   }
}


//PORT
/*
 provides the user with capability to choose port on which the the change will be done
 */
/*port
 * A
 * B
 * C
 * D
 * E
 * F
 */
void GPIO_PORT (int port)
{
    if(port==A)
    {
        BASE=A_BASE;
    }
    else if(port==B)
    {
        BASE=B_BASE;
    }
    else if(port==C)
    {
        BASE=C_BASE;
    }
    else if(port==D)
    {
        BASE=D_BASE;
    }
    else if(port==E)
    {
        BASE=E_BASE;
    }
    else if(port==F)
    {
        BASE=F_BASE;
    }
}


//DIRECTION
/*
 Enables the user to either set the port as input or output
 0-->INPUT
 1-->OUTPUT
 */
/*direction
 * INPUT
 * OUTPUT
 */

void GPIO_DIRECTION (int direction)
{
    REG GPIODIR = B(GPIODIR_O);
    if(direction==INPUT)
    {
        *GPIODIR &= ~(1<<1);
    }
    else if (direction==OUTPUT)
    {
        *GPIODIR |= (1<<1);
    }
}

//GPIO
/*
 Allows the user to either use the pin as GPIO or use its alternate function
 0-->GPIO
 1-->Alternate function
 */
/*function
 * GPIO
 * ALTERNATE
 */

void GPIO_FUNCTION (int function)
{
    REG GPIOAFSEL = B(GPIOAFSEL_O);
    if (function==GPIO)
    {
        *GPIOAFSEL_F &= ~(1<<1);
    }
    else if (function==ALTERNATE)
    {
        *GPIOAFSEL_F |= (1<<1);
    }
}






