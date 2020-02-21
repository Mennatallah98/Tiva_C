/*
 * GPIO.h
 *
 *  Created on: 20 Feb 2020
 *      Author: Mennatallah
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "StdFunctions.h"
#include "regmap.h"

typedef enum {MODE_IN = 0x00, MODE_OUT = 0xff, MODE_AF = 0x3} gpio_mode;
typedef enum {PORTA, PORTB, PORTC, PORTD, PORTE, PORTF} gpio_port;
typedef enum {AHB, APB} gpio_bus;
typedef enum {Drive_2mA, Drive_4mA, Drive_8mA, Drive_8mA_Selw} gpio_drive;
typedef enum {Pad_PU,Pad_PD,PAD_NPU_NPD,PAD_OD} gpio_pad;

#define ADDRESS volatile unsigned long int *
#define ULI     unsigned long int
//Functions prototype

//Bus functions
void GPIOBusSet(gpio_port port,gpio_bus bus);
gpio_bus GPIOBusGet(gpio_port port);
//*******************************************************

ADDRESS GPIOSetAddress(gpio_port port, unsigned long int reg);

//Clock functions
void GPIOClockSet(gpio_port port);
void GPIOClockRst(gpio_port port);
char GPIOClockGet(gpio_port port);
//*************************************************************

//Mode functions
void GPIODirModeSet(gpio_port port, unsigned char pins, gpio_mode Mode);
unsigned char GPIODirGet(gpio_port port, unsigned char pins);
unsigned char GPIOModeGet(gpio_port port, unsigned char pins);
//*************************************************************************

//PAD functions
void GPIOPadSet(gpio_port port, unsigned char pins, gpio_drive str, gpio_pad pad);
unsigned char GPIOPadDriveStrGet(gpio_port port, unsigned char pins); //how
unsigned char GPIOPadOpenDrainGet(gpio_port port, unsigned char pins);
unsigned char GPIOPadPullUpGet(gpio_port port, unsigned char pins);
unsigned char GPIOPadPullDownGet(gpio_port port, unsigned char pins);
//************************************************************************

//Read and Write functions
unsigned char GPIORead(gpio_port port, unsigned char pins);
void GPIOWrite(gpio_port port, unsigned char pins, unsigned char written_data);
//****************************************************************************


#endif /* GPIO_H_ */
