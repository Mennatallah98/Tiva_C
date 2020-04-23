/*
 * INT.h
 *
 *  Created on: 5 Mar 2020
 *      Author: Mennatallah
 */

#ifndef INT_H_
#define INT_H_

#include "StdFunctions.h"

typedef enum{PortA, PortB, PortC, PortD, PortE, UART0, UART1, SSI0, I2C0, PWM0_Fault,PWM0_G0, PWM0_G1, PWM0_G2,
QEI0, ADC0_S0, ADC0_S1, ADC0_S2, ADC0_S3, WatchdogTimers0_1,Timer0A , Timer0B, Timer1A , Timer1B, Timer2A, Timer2B,
AnalogComparator0 , AnalogComparator1, Sys_Ctrl=28, FlashMemory_EEPROM_Ctrl, PortF,UART2=33, SSI1,Timer3A, Timer3B,
I2C1, QEI1, CAN0, CAN1, Hibernation_Module=43, USB,PWM0_G3, UDMA_Software, UDMA_Error,ADC1_S0, ADC1_S1, ADC1_S2, ADC1_S3,
SSI2=57, SSI3, UART3, UART4, UART5, UART6, UART7, I2C2=68, I2C3, Timer4A, Timer4B, Timer5A=92,Timer5B,
Timer0A_W, Timer0B_W, Timer1A_W, Timer1B_W, Timer2A_W, Timer2B_W, Timer3A_W, Timer3B_W, Timer4A_W, Timer4B_W, Timer5A_W, Timer5B_W,
Sys_Exceotion, PWM1_G0=134, PWM1_G1, PWM1_G2, PWM1_G3,PWM1_Fault}INT_no;

typedef enum{Disabled,Enabled}INT_status;
typedef enum{Not_pending,Pending}INT_pending;
typedef enum{Inactive, Active}Int_activation;

ULI INTSetAddress(ULI offset, int reg_diff);

void INTEnable(INT_no INT);
void INTDisable(INT_no INT);
INT_status INTGetStatus(INT_no INT);

void INTSetPending(INT_no INT);
void INTClearPending(INT_no INT);
INT_pending INTGetPending(INT_no INT);

Int_activation INTGetActivation(INT_no INT);

void INTSetPriority(INT_no INT,UC priority);

void INTSoftwareTrigger(INT_no INT);

void IntSetFunctions(INT_no INT, void (*INT_Function) (void));

#endif /* INT_H_ */
