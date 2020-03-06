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

//typedef enum{ZERO, ONE, TWO, THREE, FOUR}register_division;

#define ADDRESS volatile unsigned long int *
#define ULI     unsigned long int
#define UC      unsigned char

ULI INTSetAddress(ULI offset);
//register_division INTGetDivision (UC INT_no);
void INTSetEnable(UC INT_no);

#endif /* INT_H_ */
