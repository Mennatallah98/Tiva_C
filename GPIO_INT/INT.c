/*
 * INT.c
 *
 *  Created on: 5 Mar 2020
 *      Author: Mennatallah
 */
#include "INT.h"

extern void (* g_pfnVectors[])(void);
#pragma DATA_ALIGN(g_pfnRAMVectors, 1024)
#pragma DATA_SECTION(g_pfnRAMVectors, ".vtable")
void (*g_pfnRAMVectors[155])(void);

ULI INTSetAddress(ULI offset,int reg_diff)
{
    ULI reg = 0xE000E000+reg_diff+(offset/32)*4;
    return reg;
}
//INT status
void INTEnable(INT_no INT)
{
    ADDRESS reg = INTSetAddress(INT,256);
    SET_eBIT(reg,(INT%32));
}
void INTDisable(INT_no INT)
{
    ADDRESS reg = INTSetAddress(INT,384);
    SET_dBIT(reg,(INT%32));
}
INT_status INTGetStatus(INT_no INT)
{
    ADDRESS reg = INTSetAddress(INT,256);
    return GET_BIT(reg,(INT%32));
}
//**************************************************
//INT pending
void INTSetPending(INT_no INT)
{
    ADDRESS reg = INTSetAddress(INT,512);
    SET_eBIT(reg,(INT%32));
}
void INTClearPending(INT_no INT)
{
    ADDRESS reg = INTSetAddress(INT,640);
    SET_dBIT(reg,(INT%32));
}
INT_pending INTGetPending(INT_no INT)
{
    ADDRESS reg = INTSetAddress(INT,512);
    return GET_BIT(reg,(INT%32));
}
//********************************************************

//INT activation
Int_activation INTGetActivation(INT_no INT)
{
    ADDRESS reg = INTSetAddress(INT,768);
    return GET_BIT(reg,(INT%32));
}
//********************************************************

//Priority
void INTSetPriority(INT_no INT,UC priority)
{
    int n = (INT/4)*4;
    ADDRESS reg = 0xE000E400+n;
    UC rem = INT%4;
    *reg= (priority<<(5*(rem+1)+3*(rem)));
}
//*********************************************************

//Software trigger
void INTSoftwareTrigger(INT_no INT)
{
    ADDRESS reg = 0xE000EF00;
    *reg = INT;
}
//****************************************************************

//INT function
void IntSetFunctions(INT_no INT, void (*INT_Function) (void))
{
    int i = 0;
    for( i = 0; i < 155; i++)
    {
        g_pfnRAMVectors[i] = g_pfnVectors[i];
    }

    ADDRESS reg     =   0xE000ED08 ;
    *reg = (unsigned long int)g_pfnRAMVectors; // Point the NVIC at the RAM vector table.

    g_pfnRAMVectors[(INT+16)] = INT_Function;
}
