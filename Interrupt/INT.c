/*
 * INT.c
 *
 *  Created on: 5 Mar 2020
 *      Author: Mennatallah
 */
#include "INT.h"
//determine the register of the interrupt
/*register_division INTGetDivision (UC INT_no)
{
    register_division register_no;
    if(INT_no<=31)
    {
        register_no = ZERO;
    }
    else if(INT_no<=63)
    {
        register_no = ONE;
    }
    else if(INT_no<=95)
    {
        register_no = TWO;
    }
    else if(INT_no<=127)
    {
        register_no = THREE;
    }
    else if(INT_no<=138)
    {
        register_no = FOUR;
    }
    return register_no;
}*/

ULI INTSetAddress(ULI offset)
{
    ULI reg = 0xE000E000+offset;
    return reg;
}

void INTSetEnable(unsigned char INT_no)
{
    //register_division reg_no = INTGetDivision (INT_no);
    ULI reg;
    UC pin;
    if(INT_no<=31)
    {
        reg=EN0;
        pin=INT_no;
    }
    else if(INT_no<=63)
    {
        reg=EN1;
        pin=(INT_no-31);
    }
    else if(INT_no<=95)
    {
        reg=EN2;
        pin=(INT_no-63);
    }
    else if(INT_no<=127)
    {
        reg=EN3;
        pin=(INT_no-95);
    }
    else if(INT_no<=138)
    {
        reg=EN4;
        pin=(INT_no-127);
    }
    ADDRESS reg_address = INTSetAddress(reg);
    ULI data = *reg_address;
    SET_BIT(data,pin);
}


