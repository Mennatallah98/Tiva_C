/*
 * regmap.h
 *
 *  Created on: 20 Mar 2020
 *      Author: Mennatallah
 */

#ifndef REGMAP_H_
#define REGMAP_H_


#define RegAddress(base,offset) base+offset

//Control registers
#define     GPIOHBCTL       0x400FE06C
#define     RCGCGPIO        0x400FE608
//********************************************************

//Ports addresses
#define     PORTA_APB       0x40004000
#define     PORTA_AHB       0x40058000

#define     PORTB_APB       0x40005000
#define     PORTB_AHB       0x40059000

#define     PORTC_APB       0x40006000
#define     PORTC_AHB       0x4005A000

#define     PORTD_APB       0x40007000
#define     PORTD_AHB       0x4005B000

#define     PORTE_APB       0x40024000
#define     PORTE_AHB       0x4005C000

#define     PORTF_APB       0x40025000
#define     PORTF_AHB       0x4005D000
//*********************************************************************

//GPIO Registers Offset
#define     GPIODIR         0x400
#define     GPIOAFSEL       0x420

#endif /* REGMAP_H_ */
