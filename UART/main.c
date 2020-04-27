

/**
 * main.c
 */

#include "UART.h"

int main(void)
{
    UARTClkEnable(UART1);
    UARTClkEnable(UART2);
    UARTClkDisable(UART2);
    UART_set value = UARTClkGet(UART1);

    UARTConfigGPIO(UART1, AHB, Drive_8mA);

    UARTEnable(UART1);
    UART_set uart = UARTGet(UART1);

    UARTSetFIFO(UART1 ,Enable);

    UARTEnableTX(UART1);
    UART_set TX = UARTGetTX(UART1);
    UARTTriggerTX_INT(UART1, UART_FIFO2);
    UART_FIFOlevel TX_trigger = UARTGetTriggerTX_INT(UART1);

    UARTEnableRX(UART1);
    UART_set RX = UARTGetRX(UART1);
    UARTTriggerRX_INT(UART1, UART_FIFO2);
    UART_FIFOlevel RX_trigger = UARTGetTriggerTX_INT(UART1);

    UARTParityConfig(UART1,Enable, Parity_Even);

    UARTSetLoopBack(UART1, Enable);

    UARTSetClkBaudrate(UART1, UART_PIOSC, UART_Clk8);
    UART_clk_src clk = UARTGetClkSrc(UART1);
    UART_clk_div div = UARTGetClkDiv(UART1);

    UARTSetTrigger(UART1,RXIM);
    UARTSetTrigger(UART1,OEIM);
    ULI mask = UARTGetTrigger(UART1);
    UARTClrINT(UART1,OEIM);
    mask = UARTGetTrigger(UART1);


	return 0;
}
