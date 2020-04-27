/*
 * UART.h
 *
 *  Created on: 23 Apr 2020
 *      Author: Mennatallah
 */


#ifndef UART_H_
#define UART_H_

#include "StdFunctions.h"
#include "regmap.h"
#include "GPIO.h"

typedef enum {UART0, UART1, UART2, UART3, UART4, UART5, UART6, UART7} UART_id;
typedef enum {Disable, Enable}UART_set;
typedef enum {One_Bit, Two_Bits}UART_stop_bits;
typedef enum {Parity_Odd, Parity_Even}UART_parity_type;
typedef enum {UART_SysClk, UART_PIOSC=0x05}UART_clk_src;
typedef enum {UART_Clk16, UART_Clk8}UART_clk_div;
typedef enum {CTSIM=1, RXIM=4, TXIM, RTIM, FEIM, PEIM, BEIM, OEIM, BITIM9=12}UART_INT;
typedef enum {UART_FIFO1, UART_FIFO2, UART_FIFO3, UART_FIFO4, UART_FIFO5, UART_EOT/*only for Tx*/}UART_FIFOlevel;
typedef enum {NotEpmty, Empty}UART_Memory_emptiness;
typedef enum {NotFull, Full}UART_Memory_fullness;
typedef enum {Available, Busy}UART_state;
typedef enum {UART_No_Error,UART_ERROR}UART_error;

//UART Clk
void UARTClkEnable(UART_id id);
void UARTClkDisable(UART_id id);
UART_set UARTCLKGet(UART_id id);
//*************************************************

//UART GPIO functions
void UARTConfigGPIO(UART_id id, gpio_bus bus, gpio_drive str);
//*************************************************************

ULI UARTSetAddress(UART_id id, ULI reg );

//UART Enable
void UARTEnable(UART_id id);
void UARTDisable(UART_id id);
UART_set UARTGet(UART_id id);
UART_state UARTGetState(UART_id id);
//*************************************************

//Stop bits
void UARTSetStopBits(UART_id id,UART_stop_bits bits);
UART_stop_bits UARTGetStopBits(UART_id id);
UART_error UARTGetStopBitError(UART_id id);
//***************************************************

//FIFO
void UARTSetFIFO(UART_id id,UART_set set);
UART_set UARTGetFIFO(UART_id id);
UART_error UARTGetFIFOOverRun(UART_id id);
//*************************************************

// TX
void UARTEnableTX(UART_id id);
void UARTDisableTX(UART_id id);
UART_set UARTGetTX(UART_id id);
void UARTSetTriggerTX_INT(UART_id id, UART_FIFOlevel level);
UART_FIFOlevel UARTGetTriggerTX_INT(UART_id id);
UART_Memory_emptiness UARTGetTXMemoryEmpitness(UART_id id);
UART_Memory_fullness UARTGetTXMemoryFullness(UART_id id);
//*************************************************

//RX
void UARTEnableRX(UART_id id);
void UARTDisableRX(UART_id id);
UART_set UARTGetRX(UART_id id);
void UARTSetTriggerRX_INT(UART_id id, UART_FIFOlevel level);
UART_FIFOlevel UARTGetTriggerRX_INT(UART_id id);
UART_error UARTGetBreakError(UART_id id);
UART_Memory_emptiness UARTGetRXMemoryEmpitness(UART_id id);
UART_Memory_fullness UARTGetRXMemoryFullness(UART_id id);
//*************************************************

//Parity
void UARTParityConfig(UART_id id, UART_set set, UART_parity_type type);
UART_parity_type UARTParityTypeGet(UART_id id);
UART_set UARTParityGet(UART_id id);
UART_error UARTParityErrorGet(UART_id id);
//************************************************************************


//Loop back
void UARTSetLoopBack(UART_id id,UART_set LBE);
UART_set UARTGetLoopBack(UART_id id);
//**********************************************

//UART Baudrate clk
void UARTSetClkBaudrate(UART_id id, UART_clk_src clk, UART_clk_div div);
UART_clk_src UARTGetClkSrc(UART_id id);
UART_clk_div UARTGetClkDiv(UART_id id);
//*******************************************

//UART INT
void UARTSetTrigger(UART_id id, UART_INT trigger);
void UARTClrTrigger(UART_id id, UART_INT trigger);
ULI UARTGetTrigger(UART_id id);
ULI UARTGetINTOcurrance(UART_id id);
ULI UARTGetINTStatus(UART_id id);
void UARTClrINT(UART_id id, UART_INT INT);
//*********************************************************



#endif /* UART_H_ */
