/*
 * INT.h
 *
 *  Created on: 5 Mar 2020
 *      Author: Mennatallah
 */

#ifndef INT_H_
#define INT_H_

#include "StdFunctions.h"
#include "regmap.h"

typedef enum{GPIOPortA, GPIOPortB, GPIOPortC, GPIOPortD, GPIOPortE, UART0, UART1, SSI1, I2C0, PWM0_Fault,
 PWM0_Generator0, PWM0_Generator1, PWM0_Generator2, Timer0_A=19 , Timer0_B, Timer1_A , Timer1_B , Timer2_A , Timer2_B
 , AnalogComparator0 , AnalogComparator1 , AnalogComparator_2 , GPIOPortF=30
 , Timer3_A=35, Timer3_B=36 , PWM0Generator3 =45, ADC1Sequence0 = 48, ADC1Sequence_1,
 ADC1Sequence_2, ADC1Sequence_3, Timer4SubtimerA=70, Timer4_SubtimerB, Timer5_A=92,Timer5_B,
 WideTimer0_A, WideTimer0_B, WideTimer1_A, WideTimer1_B, WideTimer2_A, WideTimer2_B, WideTimer3_A,
 WideTimer3_B, WideTimer4_A, WideTimer4_B, WideTimer5_A, WideTimer5_B
 , PWM1Generator_0=134, PWM1Generator_1, PWM1Generator_2, PWM1Generator_3, PWM1Fault
}Interruppt_ID;

typedef enum{Disabled,Enabled}INT_status;
typedef enum{Not_pending,Pending}INT_pending;
typedef enum{Inactive, Active}Int_Activation;

#define ADDRESS volatile unsigned long int *
#define ULI     unsigned long int
#define UC      unsigned char

ULI INTSetAddress(ULI offset, int reg_diff);

void INTEnable(UC INT_no);
void INTDisable(UC INT_no);
INT_status INTGetStatus(UC INT_no);

void INTSetPending(UC INT_no);
void INTClearPending(UC INT_no);
INT_pending INTGetPending(UC INT_no);

Int_Activation INTGetActivation(UC INT_no);

void INTSetPriority(UC INT_no,UC priority);

void INTSoftwareTrigger(UC INT_no);

#endif /* INT_H_ */
