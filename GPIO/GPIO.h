/*
 * GPIO.h
 *
 *  Created on: 20 Mar 2020
 *      Author: Mennatallah
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "StdFunctions.h"
#include "regmap.h"

#define ADDRESS volatile unsigned long int *
#define ULI     unsigned long int
#define UC      unsigned char

typedef enum {PORTA, PORTB, PORTC, PORTD, PORTE, PORTF} gpio_port;
typedef enum {APB, AHB} gpio_bus;
typedef enum {MODE_IN = 0x00, MODE_OUT = 0xff, MODE_AF = 0x3} gpio_mode;

//Functions prototype

//Bus functions
void GPIOBusSet(gpio_port port,gpio_bus bus);
gpio_bus  GPIOBusGet(gpio_port port);
//*******************************************************

ULI GPIOSetAddress(gpio_port port, ULI reg);

//Clock functions
void GPIOClockSet(gpio_port port);
void GPIOClockRst(gpio_port port);
UC GPIOClockGet(gpio_port port);
//*************************************************************

//Mode functions
void GPIODirModeSet(gpio_port port, UC pins, gpio_mode Mode);
UC GPIODirGet(gpio_port port, UC pins);
UC GPIOModeGet(gpio_port port, UC pins);
//*************************************************************************

#endif /* GPIO_H_ */
