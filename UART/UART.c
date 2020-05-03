/*
 * UART.c
 *
 *  Created on: 23 Apr 2020
 *      Author: Mennatallah
 */

#include "UART.h"

//UART ports
gpio_port port[] = {PORTA, PORTB, PORTD, PORTC, PORTC, PORTE, PORTD, PORTE};
UC pins[] = {0x03, 0x03, 0xC0, 0xC0, 0x30, 0x30, 0x30, 0x30}; //this array holds the value of pins in each port for each UART in order (hex value)
ULI UART_address[] = {UART0_base, UART1_base, UART2_base, UART3_base, UART4_base, UART5_base, UART6_base, UART7_base};

//Clk Enable
void UARTClkEnable(UART_id id)
{
    ADDRESS reg = RCGCUART;
    SET_BIT(reg,id);
}

void UARTClkDisable(UART_id id)
{
    ADDRESS reg = RCGCUART;
    CLR_BIT(reg,id);
}

UART_set UARTClkGet(UART_id id)
{
    ADDRESS reg = RCGCUART;
    return GET_BIT(reg,id);
}
//********************************************************************

//UART GPIO functions
void UARTConfigGPIO(UART_id id, gpio_bus bus, gpio_drive str)
{
    GPIOBusSet(port[id], bus);
    GPIOClockSet(port[id]);
    GPIODirModeSet(port[id], pins[id], MODE_AF,1);
    GPIOPadSet(port[id], pins[id], str, PAD_NPU_NPD, En_Digital);
}
//************************************************************************
ULI UARTSetAddress(UART_id id, ULI reg )
{
    ULI final_reg = UART_address[id]+reg;
    return final_reg;
}

//UART Enable
void UARTEnable(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    SET_BIT(reg,0);
}

void UARTDisable(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    CLR_BIT(reg,0);
}

UART_set UARTGet(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    return GET_BIT(reg,0);
}
UART_state UARTGetState(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTFR);
    return GET_BIT(reg,3);
}
//********************************************************************

//Stop bits
void UARTSetStopBits(UART_id id,UART_stop_bits bits)
{
    ADDRESS reg = UARTSetAddress(id, UARTLCRH);
    *reg &= ~(0x08);
    *reg |= (bits<<3);
}
UART_stop_bits UARTGetStopBits(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTLCRH);
    return GET_BIT(reg,3);
}
UART_error UARTGetStopBitError(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTDR);
    return GET_BIT(reg,8);
}
//***************************************************************

//FIFO
void UARTSetFIFO(UART_id id,UART_set set)
{
    ADDRESS reg = UARTSetAddress(id, UARTLCRH);
    *reg &= ~(0x10);
    *reg |= (set<<4);
}
UART_set UARTGetFIFO(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTLCRH);
    return GET_BIT(reg,4);
}
UART_error UARTGetFIFOOverRun(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTDR);
    return GET_BIT(reg,11);
}
//***********************************************************************

//TX
void UARTEnableTX(UART_id id)
{
    UARTDisable(id);
    UARTSetFIFO(id,Disable);
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    SET_BIT(reg,8);
    UARTEnable(id);
    UARTSetFIFO(id,Enable);

}

void UARTDisableTX(UART_id id)
{
    UARTDisable(id);
    UARTSetFIFO(id,Disable);
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    CLR_BIT(reg,8);
    UARTEnable(id);
    UARTSetFIFO(id,Enable);
}

UART_set UARTGetTX(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    return GET_BIT(reg,8);
}

void UARTTriggerTX_INT(UART_id id, UART_FIFOlevel level)
{
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    if(level==UART_EOT)
    {
        UARTDisable(id);
        UARTSetFIFO(id,Disable);
        SET_BIT(reg,4);
        UARTEnable(id);
        UARTSetFIFO(id,Enable);
    }
    else
    {
        CLR_BIT(reg,4);
        ADDRESS reg = UARTSetAddress(id, UARTIFLS);
        *reg &= 111000;
        *reg |= level;
    }
}

UART_FIFOlevel UARTGetTriggerTX_INT(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
        if(GET_BIT(reg,4)==1)
        {
            return UART_EOT;
        }
        else
        {
            reg = UARTSetAddress(id, UARTIFLS);
            UC data = *reg & 000111;
            return data;
        }
}
UART_Memory_emptiness UARTGetTXMemoryEmpitness(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTFR);
    return GET_BIT(reg,7);
}
UART_Memory_fullness UARTGetTXMemoryFullness(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTFR);
    return GET_BIT(reg,5);
}
//********************************************************************

//RX
void UARTEnableRX(UART_id id)
{
    UARTDisable(id);
    UARTSetFIFO(id,Disable);
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    SET_BIT(reg,9);
    UARTEnable(id);
    UARTSetFIFO(id,Enable);
}

void UARTDisableRX(UART_id id)
{
    UARTDisable(id);
    UARTSetFIFO(id,Disable);
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    CLR_BIT(reg,9);
    UARTEnable(id);
    UARTSetFIFO(id,Enable);
}

UART_set UARTGetRX(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    return GET_BIT(reg,9);
}
void UARTTriggerRX_INT(UART_id id, UART_FIFOlevel level)
{
    ADDRESS reg = UARTSetAddress(id, UARTIFLS);
    *reg &= 000111;
    *reg |= level;
}

UART_FIFOlevel UARTGetTriggerRX_INT(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTIFLS);
    UC data = *reg & 111000;
    return data;
}
UART_error UARTGetBreakError(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTDR);
    return GET_BIT(reg,10);
}
UART_Memory_emptiness UARTGetRXMemoryEmpitness(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTFR);
    return GET_BIT(reg,4);
}
UART_Memory_fullness UARTGetRXMemoryFullness(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTFR);
    return GET_BIT(reg,6);
}
//********************************************************************

//Parity
void UARTParityConfig(UART_id id, UART_set set, UART_parity_type type)
{
    ADDRESS reg = UARTSetAddress(id, UARTLCRH);
    *reg &= ~(0x86);
    *reg |= (set<<1);
    *reg |= (type<<2);
}

UART_parity_type UARTParityTypeGet(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTLCRH);
    return GET_BIT(reg,2);
}

UART_set UARTParityGet(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTLCRH);
    return GET_BIT(reg,1);
}
UART_error UARTParityErrorGet(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTDR);
    return GET_BIT(reg,9);
}
//*************************************************************************************

//Loop back
void UARTSetLoopBack(UART_id id,UART_set LBE)
{
    UARTDisable(id);
    UARTSetFIFO(id,Disable);
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    *reg &= ~(0x80);
    *reg |= (LBE<<7);
    UARTEnable(id);
    UARTSetFIFO(id,Enable);
}

UART_set UARTGetLoopBack(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    return GET_BIT(reg,7);
}
//***************************************************

//Baudrate
void UARTSetClkBaudrate(UART_id id, UART_clk_src clk, UART_clk_div div)
{
    ADDRESS reg = UARTSetAddress(id, UARTCC);
    *reg = clk;
    reg = UARTSetAddress(id, UARTCTL);
    UARTDisable(id);
    UARTSetFIFO(id,Disable);
    *reg &= ~(0x16);
    *reg |= (div<<5);
    UARTEnable(id);
    UARTSetFIFO(id,Enable);
}

UART_clk_src UARTGetClkSrc(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTCC);
    return *reg;
}
UART_clk_div UARTGetClkDiv(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTCTL);
    return GET_BIT(reg,5);
}
void UARTSetBaudrate(UART_id id, UART_baudrates baudrate)
{
    int clkdiv,clksrc;
    if(UARTGetClkDiv(id))
        clkdiv=8;
    else
        clkdiv=16;
    if(UARTGetClkSrc(id))
        clksrc=16000000;

}
//**************************************************************

//UART INT
void UARTSetTrigger(UART_id id, UART_INT trigger)
{
    ADDRESS reg = UARTSetAddress(id, UARTIM);
    SET_BIT(reg,trigger);
}

void UARTClrTrigger(UART_id id, UART_INT trigger)
{
    ADDRESS reg = UARTSetAddress(id, UARTIM);
    CLR_BIT(reg,trigger);
}

ULI UARTGetTrigger(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTIM);
    return *reg;
}

ULI UARTGetINTOcurrance(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTRIS);
    return *reg;
}

ULI UARTGetINTStatus(UART_id id)
{
    ADDRESS reg = UARTSetAddress(id, UARTMIS);
    return *reg;
}

void UARTClrINT(UART_id id, UART_INT INT)
{
    ADDRESS reg = UARTSetAddress(id, UARTICR);
    SET_BIT(reg,INT);
}
//***************************************************************************

