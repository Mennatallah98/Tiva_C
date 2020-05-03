/*
 * Timer.c
 *
 *  Created on: 1 May 2020
 *      Author: Mennatallah
 */

#include "Timer.h"

ULI Timer_address[] = {Timer0, Timer1, Timer2, Timer3, Timer4, Timer5, TimerWide0, TimerWide1, TimerWide2, TimerWide4, TimerWide5};
gpio_port port[] = {PORTB, PORTB, PORTB, PORTB, PORTC, PORTC, PORTC, PORTC, PORTD, PORTD, PORTD, PORTD};
UC pins[] = {0xC0, 0x30, 0x03, 0x0C, 0x03, 0x0C, 0x30, 0xC0, 0x03, 0x0C, 0x30, 0xC0}; //this array holds the value of pins in each port for each UART in order (hex value)

Timer_mode TACMR,TBCMR;
Timer_capture_mode TAMR,TBMR;

//Timer clk
void TimerClkEnable(Timer_id id)
{
    if(id<6)
    {
        ADDRESS reg = RCGCTIMER;
        SET_BIT(reg,id);
    }
    else
    {
        ADDRESS reg = RCGCWTIMER;
        SET_BIT(reg,(id-6));
    }
}
void TimerClkDisable(Timer_id id)
{
    if(id<6)
    {
        ADDRESS reg = RCGCTIMER;
        CLR_BIT(reg,id);
    }
    else
    {
        ADDRESS reg = RCGCWTIMER;
        CLR_BIT(reg,(id-6));
    }
}
Timer_set TimerClkGet(Timer_id id)
{
    if(id<6)
    {
        ADDRESS reg = RCGCTIMER;
        return GET_BIT(reg,id);
    }
    else
    {
        ADDRESS reg = RCGCWTIMER;
        return GET_BIT(reg,(id-6));
    }
}
//**********************************************************************************************************

//Timer GPIO config
void TimerConfigGPIO(Timer_id id, gpio_bus bus, gpio_drive str)
{
    GPIOBusSet(port[id], bus);
    GPIOClockSet(port[id]);
    GPIODirModeSet(port[id], pins[id], MODE_AF,7);
    GPIOPadSet(port[id], pins[id], str, PAD_NPU_NPD, En_Digital);
}
//*********************************************************************************


ULI UARTSetAddress(Timer_id id, ULI reg )
{
    ULI final_reg = Timer_address[id]+reg;
    return final_reg;
}

//Timer config
void TimerSetConfig(Timer_id id,Timer_config config)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCFG);
    *reg &= ~(0x07);
    *reg |= config;
}

Timer_config TimerGetAddress(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCFG);
    return *reg;
}
//**************************************************************************

//RTC
void TimerRTCStallSet(Timer_id id, Timer_set set)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    *reg &= ~(0x10);
    *reg |= (set<<4);
}
Timer_set TimerRTCStallGet(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    return GET_BIT(reg,4);
}
ULI TimerRTCGetPredivider(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMRTCPD);
    return *reg;
}
//***************************************************************

//SYNC
void TimerSyncSet(Timer_id id, Timer_sync sync)
{
    ADDRESS reg = UARTSetAddress(id,GPTMSYNC);
    *reg &= (00<<(id*2));
    *reg |= (sync<<(id*2));
}
Timer_sync TimerSyncGet(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMSYNC);
    return (*reg>>(id*2));
}
//****************************************************************

//Timer INT
void TimerINTSetTrigger(Timer_id id, Timer_INT INT)
{
    ADDRESS reg = UARTSetAddress(id,GPTMIMR);
    SET_BIT(reg,INT);
}
void TimerINTClrTrigger(Timer_id id, Timer_INT INT)
{
    ADDRESS reg = UARTSetAddress(id,GPTMIMR);
    CLR_BIT(reg,INT);
}
ULI TimerINTGetTrigger(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMIMR);
    return *reg;
}
ULI TimerINTGetOcurrance(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMRIS);
    return *reg;
}
ULI TimerINTGetStatus(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMMIS);
    return *reg;
}
void TimerINTClr(Timer_id id, Timer_INT INT)
{
    ADDRESS reg = UARTSetAddress(id,GPTMICR);
    SET_BIT(reg,INT);
}
//****************************************************************

                        /*************************** TimerA  ******************************************/
//Timer Setup
void TimerAEnable(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    SET_BIT(reg,0);
}

void TimerADisable(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    CLR_BIT(reg,0);
}
Timer_set TimerAGetStatus(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    return GET_BIT(reg,0);
}
void TimerAStallSet(Timer_id id, Timer_set set)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    *reg &= ~(0x02);
    *reg |= (set<<1);
}
Timer_set TimerAStallGet(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    return GET_BIT(reg,1);
}
void TimerAEventSet(Timer_id id, Timer_event event)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    *reg &= ~(0x0C);
    *reg |= (event<<2);
}
Timer_event TimerAEventGet(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    ULI data = *reg & (0x0C);
    return data;
}
//************************************************************

//Set values
void TimerALoadSetValue(Timer_id id, ULI value)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAILR);
    *reg=value;
}
ULI TimerALoadGetValue(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAILR);
    return *reg;
}
void TimerAMatchSetValue(Timer_id id, ULI value)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMATCHR);
    *reg=value;
}
ULI TimerAMatchGetValue(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMATCHR);
    return *reg;
}
void TimerAPrescalerSetValue(Timer_id id, ULI value)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAPR);
    *reg=value;
}
ULI TimerAPrescalerGetValue(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAPR);
    return *reg;
}
void TimerAMatchPrescalerSetValue(Timer_id id, ULI value)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAPMR);
    *reg=value;
}
ULI TimerAMatchPrescalerGetValue(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAPMR);
    return *reg;
}
ULI TimerACounterEdgesGetValue(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAR);
    return *reg;
}
void TimerACounterEdgesSetValue(Timer_id id, ULI value)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAV);
    *reg=value;
}
ULI TimerAValueGetCurrent(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAV);
    return *reg;
}
ULI TimerASnapshotPrescalerGetValue(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAPS);
    return *reg;
}
ULI TimerAPrescalerGetCurrent(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAPV);
    return *reg;
}
//********************************************************
//Timer mode
void TimerASetMode(Timer_id id, Timer_mode mode)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    *reg &= ~(0x03);
    *reg |= mode;
}
Timer_mode TimerAGetMode(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    ULI data = *reg & (0x03);
    return data;
}
//*************************************************************

//PWM
void TimerAPWMEnable(Timer_id id)
{
    TACMR = TimerAGetMode(id);
    TAMR = TimerACaptureGetMode(id);

    TimerASetMode(id,Periodic);
    TimerACaptureSetMode(id,EdgeCount);

    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    SET_BIT(reg,3);
}
void TimerAPWMDisable(Timer_id id)
{
    TimerASetMode(id,TACMR);
    TimerACaptureSetMode(id,TAMR);

    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    CLR_BIT(reg,3);
}
Timer_set TimerAPWMGet(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,3);
}
void TimerAPWMSetINT(Timer_id id, Timer_set set)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    *reg &= ~(0x200);
    *reg |= (set<<9);
}
Timer_set TimerAPWMGetINT(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,9);
}
void TimerAPWMSetLegacy(Timer_id id, Timer_set set)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    *reg &= ~(0x800);
    *reg |= (set<<11);
}
Timer_set TimerAPWMGetLegacy(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,11);
}
void TimerAPWMSetOutput(Timer_id id, Timer_pwm_output output)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    *reg &= ~(0x40);
    *reg |= (output<<6);
}
Timer_pwm_output TimerAPWMGetOutput(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    return GET_BIT(reg,6);
}
//*****************************************************************

//Capture mode
void TimerACaptureSetMode(Timer_id id, Timer_capture_mode mode)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    *reg &= ~(0x04);
    *reg |= (mode<<2);
}
Timer_capture_mode TimerACaptureGetMode(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,2);
}
//***********************************************************************

//Timer counter
void TimerACounterSetDirection(Timer_id id, Timer_count_direction direction)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    *reg &= ~(0x10);
    *reg |= (direction<<4);
}

Timer_count_direction TimerACounterGetDirection(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,4);
}
//**************************************************************************

//one shot and periodic
void TimerAMatchSetINT(Timer_id id, Timer_set set)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    *reg &= ~(0x20);
    *reg |= (set<<5);
}

Timer_set TimerAMatchGetINT(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,5);
}

void TimerATriggerSet(Timer_id id, Timer_trigger_action trigger)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    *reg &= ~(0x40);
    *reg |= (trigger<<6);
}
Timer_trigger_action TimerATriggerGet(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,6);
}
void TimerASetSnapshot(Timer_id id, Timer_set set)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    *reg &= ~(0x80);
    *reg |= (set<<7);
}
Timer_set TimerAGetSnapshot(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,7);
}
void TimerATriggerADCSet(Timer_id id, Timer_set set)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    *reg &= ~(0x20);
    *reg |= (set<<5);
}
Timer_set TimerATriggerADCGet(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMCTL);
    return GET_BIT(reg,5);
}
//*****************************************************************************

//Timer value registers
void TimerAMatchSetUpdate(Timer_id id, Timer_match_update update)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
        *reg &= ~(0x400);
        *reg |= (update<<10);
}
Timer_match_update TimerAMatchGetUpdate(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,10);
}
void TimerAValueSetUpdate(Timer_id id, Timer_match_update update)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
        *reg &= ~(0x100);
        *reg |= (update<<8);
}
Timer_match_update TimerAValueGetUpdate(Timer_id id)
{
    ADDRESS reg = UARTSetAddress(id,GPTMTAMR);
    return GET_BIT(reg,8);
}
//****************************************************************************

       /*************************** TimerB  ******************************************/
//Timer Setup
void TimerBEnable(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   SET_BIT(reg,8);
}

void TimerBDisable(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   CLR_BIT(reg,8);
}
Timer_set TimerBGetStatus(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   return GET_BIT(reg,8);
}
void TimerBStallSet(Timer_id id, Timer_set set)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   *reg &= ~(0x200);
   *reg |= (set<<9);
}
Timer_set TimerBStallGet(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   return GET_BIT(reg,9);
}
void TimerBEventSet(Timer_id id, Timer_event event)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   *reg &= ~(0xC00);
   *reg |= (event<<10);
}
Timer_event TimerBEventGet(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   ULI data = *reg & (0xC00);
   return data;
}
//************************************************************

//Set values
void TimerBLoadSetValue(Timer_id id, ULI value)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBILR);
   *reg=value;
}
ULI TimerBLoadGetValue(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBILR);
   return *reg;
}
void TimerBMatchSetValue(Timer_id id, ULI value)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMATCHR);
   *reg=value;
}
ULI TimerBMatchGetValue(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMATCHR);
   return *reg;
}
void TimerBPrescalerSetValue(Timer_id id, ULI value)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBPR);
   *reg=value;
}
ULI TimerBPrescalerGetValue(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBPR);
   return *reg;
}
void TimerBMatchPrescalerSetValue(Timer_id id, ULI value)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBPMR);
   *reg=value;
}
ULI TimerBMatchPrescalerGetValue(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBPMR);
   return *reg;
}
ULI TimerBCounterEdgesGetValue(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBR);
   return *reg;
}
void TimerBCounterEdgesSetValue(Timer_id id, ULI value)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBV);
   *reg=value;
}
ULI TimerBValueGetCurrent(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBV);
   return *reg;
}
ULI TimerBSnapshotPrescalerGetValue(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBPS);
   return *reg;
}
ULI TimerBPrescalerGetCurrent(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBPV);
   return *reg;
}
//********************************************************
//Timer mode
void TimerBSetMode(Timer_id id, Timer_mode mode)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   *reg &= ~(0x03);
   *reg |= mode;
}
Timer_mode TimerBGetMode(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   ULI data = *reg & (0x03);
   return data;
}
//*************************************************************

//PWM
void TimerBPWMEnable(Timer_id id)
{
   TBCMR = TimerBGetMode(id);
   TBMR = TimerBCaptureGetMode(id);

   TimerBSetMode(id,Periodic);
   TimerBCaptureSetMode(id,EdgeCount);

   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   SET_BIT(reg,3);
}
void TimerBPWMDisable(Timer_id id)
{
   TimerBSetMode(id,TBCMR);
   TimerBCaptureSetMode(id,TBMR);

   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   CLR_BIT(reg,3);
}
Timer_set TimerBPWMGet(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,3);
}
void TimerBPWMSetINT(Timer_id id, Timer_set set)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   *reg &= ~(0x200);
   *reg |= (set<<9);
}
Timer_set TimerBPWMGetINT(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,9);
}
void TimerBPWMSetLegacy(Timer_id id, Timer_set set)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   *reg &= ~(0x800);
   *reg |= (set<<11);
}
Timer_set TimerBPWMGetLegacy(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,11);
}
void TimerBPWMSetOutput(Timer_id id, Timer_pwm_output output)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   *reg &= ~(0x4000);
   *reg |= (output<<14);
}
Timer_pwm_output TimerBPWMGetOutput(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   return GET_BIT(reg,14);
}
//*****************************************************************

//Capture mode
void TimerBCaptureSetMode(Timer_id id, Timer_capture_mode mode)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   *reg &= ~(0x04);
   *reg |= (mode<<2);
}
Timer_capture_mode TimerBCaptureGetMode(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,2);
}
//***********************************************************************

//Timer counter
void TimerBCounterSetDirection(Timer_id id, Timer_count_direction direction)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   *reg &= ~(0x10);
   *reg |= (direction<<4);
}

Timer_count_direction TimerBCounterGetDirection(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,4);
}
//**************************************************************************

//one shot and periodic
void TimerBMatchSetINT(Timer_id id, Timer_set set)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   *reg &= ~(0x20);
   *reg |= (set<<5);
}

Timer_set TimerBMatchGetINT(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,5);
}

void TimerBTriggerSet(Timer_id id, Timer_trigger_action trigger)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   *reg &= ~(0x40);
   *reg |= (trigger<<6);
}
Timer_trigger_action TimerBTriggerGet(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,6);
}
void TimerBSetSnapshot(Timer_id id, Timer_set set)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   *reg &= ~(0x80);
   *reg |= (set<<7);
}
Timer_set TimerBGetSnapshot(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,7);
}
void TimerBTriggerADCSet(Timer_id id, Timer_set set)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   *reg &= ~(0x2000);
   *reg |= (set<<13);
}
Timer_set TimerBTriggerADCGet(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMCTL);
   return GET_BIT(reg,13);
}
//*****************************************************************************

//Timer value registers
void TimerBMatchSetUpdate(Timer_id id, Timer_match_update update)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
       *reg &= ~(0x400);
       *reg |= (update<<10);
}
Timer_match_update TimerBMatchGetUpdate(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,10);
}
void TimerBValueSetUpdate(Timer_id id, Timer_match_update update)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
       *reg &= ~(0x100);
       *reg |= (update<<8);
}
Timer_match_update TimerBValueGetUpdate(Timer_id id)
{
   ADDRESS reg = UARTSetAddress(id,GPTMTBMR);
   return GET_BIT(reg,8);
}
//****************************************************************************

