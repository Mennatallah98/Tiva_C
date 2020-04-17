/*
 * INT.c
 *
 *  Created on: 5 Mar 2020
 *      Author: Mennatallah
 */
#include "INT.h"


ULI INTSetAddress(ULI offset,int reg_diff)
{
    ULI reg = 0xE000E000+reg_diff+(offset/32)*4;
    return reg;
}
//INT status
void INTEnable(UC INT_no)
{
    ADDRESS reg = INTSetAddress(INT_no,256);
    SET_eBIT(reg,(INT_no%32));
}
void INTDisable(UC INT_no)
{
    ADDRESS reg = INTSetAddress(INT_no,384);
    SET_dBIT(reg,(INT_no%32));
}
INT_status INTGetStatus(UC INT_no)
{
    ADDRESS reg = INTSetAddress(INT_no,256);
    return GET_BIT(reg,(INT_no%32));
}
//**************************************************
//INT pending
void INTSetPending(UC INT_no)
{
    ADDRESS reg = INTSetAddress(INT_no,512);
    SET_eBIT(reg,(INT_no%32));
}
void INTClearPending(UC INT_no)
{
    ADDRESS reg = INTSetAddress(INT_no,640);
    SET_dBIT(reg,(INT_no%32));
}
INT_pending INTGetPending(UC INT_no)
{
    ADDRESS reg = INTSetAddress(INT_no,512);
    return GET_BIT(reg,(INT_no%32));
}
//********************************************************

//INT activation
Int_Activation INTGetActivation(UC INT_no)
{
    ADDRESS reg = INTSetAddress(INT_no,768);
    return GET_BIT(reg,(INT_no%32));
}
//********************************************************

//Priority
void INTSetPriority(UC INT_no,UC priority)
{
    int n = (INT_no/4)*4;
    ADDRESS reg = 0xE000E400+n;
    UC rem = INT_no%4;
    *reg= (priority<<(5*(rem+1)+3*(rem)));
}

//Software trigger
void INTSoftwareTrigger(UC INT_no)
{
    ADDRESS reg = 0xE000EF00;
    *reg = INT_no;
}
