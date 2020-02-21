/*
 * GPIO.h
 *
 *  Created on: 14 Feb 2020
 *      Author: Mennatallah
 */

#ifndef GPIO_H_
#define GPIO_H_

#define REG volatile unsigned long int *

//CLOCK REFISTERS
REG RCC = 0x400FE060;   //base+offset  //volatile--> no optimization , depends on hardware
REG GPIOHBCTL = 0x400FE06C;
REG RCGCGPIO = 0x400FE608;
//*****************************************************************

//BASE ADRESSES
unsigned long int A_BASE;
unsigned long int B_BASE;
unsigned long int C_BASE;
unsigned long int D_BASE;
unsigned long int E_BASE;
unsigned long int F_BASE;
unsigned long int BASE;
//******************************************************************

//BUS
#define APB   0
#define AHB   1
//****************************************************************

//PORTs
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
//***********************************************************************

//REGISTERS OFFSET
#define GPIODIR_O       0x400
#define GPIOAFSEL_O     0x420

//*******************************************************************

//REGISTER ADRESSES
#define B(offset) BASE+offset
//*****************************************************************

//DIRECTION
#define INPUT  8
#define OUTPUT 9
//*****************************************************************

//FUNCTION
#define GPIO       10
#define ALTERNATE  11
//***********************************************************************

#endif /* GPIO_H_ */
