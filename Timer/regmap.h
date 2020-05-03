/*
 * regmap.h
 *
 *  Created on: 23 Apr 2020
 *      Author: Mennatallah
 */

#ifndef REGMAP_H_
#define REGMAP_H_

//Control registers
#define     GPIOHBCTL       0x400FE06C
#define     RCGCGPIO        0x400FE608
#define     RCGCUART        0x400FE618
#define     RCGCTIMER       0x400FE604
#define     RCGCWTIMER      0x400FE65C
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
#define     GPIODR2R        0x500
#define     GPIODR4R        0x504
#define     GPIODR8R        0x508
#define     GPIOSLR         0x518
#define     GPIOODR         0x50C
#define     GPIOPUR         0x510
#define     GPIOPDR         0x514
#define     GPIODEN         0x51C
#define     GPIOAMSEL       0x528
#define     GPIODATA        0x000
#define     GPIOIS          0x404
#define     GPIOIM          0x410
#define     GPIOIBE         0x408
#define     GPIOIEV         0x40C
#define     GPIOICR         0x41C
#define     GPIORIS         0x414
#define     GPIOMIS         0x418
#define     GPIOPCTL        0x52C
//******************************************************************************

//UART addresses
#define     UART0_base      0x4000C000
#define     UART1_base      0x4000D000
#define     UART2_base      0x4000E000
#define     UART3_base      0x4000F000
#define     UART4_base      0x40010000
#define     UART5_base      0x40011000
#define     UART6_base      0x40012000
#define     UART7_base      0x40013000
//************************************************************************************

//UART Registers Offsets
#define     UARTCC          0xFC8
#define     UARTIM          0x038
#define     UARTRIS         0x03C
#define     UARTMIS         0x040
#define     UARTICR         0x044
#define     UARTIFLS        0x034
#define     UARTCTL         0x030
#define     UARTLCRH        0x02C
#define     UARTDR          0x000
#define     UARTFR          0x018
#define     UARTIBRD        0x024
#define     UARTFBRD        0x028
//**********************************************************************************************

//Timer addresses
#define     Timer0          0x40030000
#define     Timer1          0x40031000
#define     Timer2          0x40032000
#define     Timer3          0x40033000
#define     Timer4          0x40034000
#define     Timer5          0x40035000
#define     TimerWide0      0x40036000
#define     TimerWide1      0x40037000
#define     TimerWide2      0x4003C000
#define     TimerWide3      0x4003D000
#define     TimerWide4      0x4003E000
#define     TimerWide5      0x4003F000
//****************************************************************************************************

//Timer registers offsets
#define     GPTMCFG         0x000
#define     GPTMTAMR        0x004
#define     GPTMCTL         0x00C
#define     GPTMSYNC        0x010
#define     GPTMIMR         0x018
#define     GPTMRIS         0x01C
#define     GPTMMIS         0x020
#define     GPTMICR         0x024
#define     GPTMTAILR       0x028
#define     GPTMTAMATCHR    0x030
#define     GPTMTAPR        0x038
#define     GPTMTAPMR       0x040
#define     GPTMTAR         0x048
#define     GPTMTAV         0x050
#define     GPTMRTCPD       0x058
#define     GPTMTAPS        0x05C
#define     GPTMTAPV        0x064
#define     GPTMTBMR        0x008
#define     GPTMTBILR       0x02C
#define     GPTMTBMATCHR    0x034
#define     GPTMTBPR        0x03C
#define     GPTMTBPMR       0x044
#define     GPTMTBR         0x04C
#define     GPTMTBV         0x054
#define     GPTMRTCPD       0x058
#define     GPTMTBPS        0x060
#define     GPTMTBPV        0x068
//****************************************

#endif /* REGMAP_H_ */
