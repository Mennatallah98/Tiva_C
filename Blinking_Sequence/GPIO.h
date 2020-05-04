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

typedef enum {PORTA, PORTB, PORTC, PORTD, PORTE, PORTF} gpio_port;
typedef enum {APB, AHB} gpio_bus;
typedef enum {MODE_IN = 0x00, MODE_OUT = 0xff, MODE_AF = 0x03} gpio_mode;
typedef enum {Drive_2mA, Drive_4mA, Drive_8mA, Drive_8mA_Selw} gpio_drive;
typedef enum {Pad_PU,Pad_PD,PAD_NPU_NPD,PAD_OD} gpio_pad;
typedef enum {En_Digital,En_Analog}gpio_enable;
typedef enum {Edge = 0x00,Level = 0xff}INT_sense;
typedef enum {Falling_Low = 0x00,Rising_High = 0xff,Double_edge = 0x03}INT_trigger;

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
void GPIODirModeSet(gpio_port port, UC pins, gpio_mode Mode, UC af_fn); //af_fn-> no of alternative function if none write 0
UC GPIODirGet(gpio_port port, UC pins);
UC GPIOModeGet(gpio_port port, UC pins);
//*************************************************************************

//PAD functions
void GPIOPadSet(gpio_port port, UC pins, gpio_drive str, gpio_pad pad, gpio_enable enable);
UC GPIOPadDriveStr2Get(gpio_port port, UC pins);
UC GPIOPadDriveStr4Get(gpio_port port, UC pins);
UC GPIOPadDriveStr8Get(gpio_port port, UC pins);
UC GPIOPadDriveStrSlewGet(gpio_port port, UC pins);
UC GPIOPadOpenDrainGet(gpio_port port, UC pins);
UC GPIOPadPullUpGet(gpio_port port, UC pins);
UC GPIOPadPullDownGet(gpio_port port, UC pins);
//************************************************************************

//Read and Write functions
UC GPIORead(gpio_port port, UC pins);
void GPIOWrite(gpio_port port, UC pins, UC written_data);
//****************************************************************************

//Interrupt  functions
void GPIOConfigINT(gpio_port port, UC pins, INT_sense sense, INT_trigger trigger);
void GPIOClrINT (gpio_port port, UC pins);
UC GPIOGetINTSense(gpio_port port, UC pins);
UC GPIOGetINTBothedges(gpio_port port, UC pins);
UC GPIOGetINTTrigger(gpio_port port, UC pins);
UC GPIOGetINTMask(gpio_port port, UC pins);
UC GPIOGetINTOcuurance(gpio_port port, UC pins);
UC GPIOGetINTStatus(gpio_port port, UC pins);
//****************************************************************************************

#endif /* GPIO_H_ */
