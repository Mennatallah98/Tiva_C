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
int A_BASE;
int B_BASE;
int C_BASE;
int D_BASE;
int E_BASE;
int F_BASE;
int BASE;
//******************************************************************

//MODE OF OPERATION
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
#define GPIODIR_O   0x400

//*******************************************************************

//REGISTER ADRESSES
#define B(offset) BASE+offset
//***************************************************

//DIRECTION
#define INPUT

#endif /* GPIO_H_ */
