/*
 * StdFunctions.h
 *
 *  Created on: 20 Feb 2020
 *      Author: Mennatallah
 */

#ifndef STDFUNCTIONS_H_
#define STDFUNCTIONS_H_

#define SET_BIT(reg, n) (*reg |= (1<<n))
#define CLR_BIT(reg, n) (*reg &=  ~(1<<n))
#define TOG_BIT(reg, n) (*reg ^=(1<<n))
#define GET_BIT(reg, n) ((*reg>>n)&1)

#define SET_BITS(reg, pins) (*reg |= (0xff & pins))
#define CLR_BITS(reg, pins) (*reg |= (0x00 & pins))

#endif /* STDFUNCTIONS_H_ */
