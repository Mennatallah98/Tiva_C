/*
 * Timer.h
 *
 *  Created on: 1 May 2020
 *      Author: Mennatallah
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "StdFunctions.h"
#include "regmap.h"
#include "GPIO.h"

typedef enum{TIMER0, TIMER1, TIMER2, TIMER3, TIMER4, TIMER5, TIMERWide0, TIMERWide1, TIMERWide2, TIMERWide3, TIMERWide4, TIMERWide5}Timer_id;
typedef enum{Disable, Enable}Timer_set;
typedef enum{Concatenated, RealTimeClock, Seprated=0x4}Timer_config;
typedef enum{OneShot=0x01, Periodic, Capture}Timer_mode;
typedef enum{EdgeCount, EdgeTime}Timer_capture_mode;
typedef enum{Down, Up}Timer_count_direction;
typedef enum{Automatic, WaitTrigger/*for daisy chaining*/}Timer_trigger_action;
typedef enum{NextCycle, NextTimeout}Timer_match_update;
typedef enum{PostiveEdege, NegativeEdge, Reversed, BothEdges}Timer_event;
typedef enum{Normal, Iinverted}Timer_pwm_output;
typedef enum{Unaffected, TimerA, TimerB, BothAandB}Timer_sync;
typedef enum{TATOIM, CAMIM, CAEIM, RTCIM, TAMIM, TBTOIM=8, CBMIM, CBEIM, TBMIM, WUEIM=16}Timer_INT;

//Timer clk
void TimerClkEnable(Timer_id id);
void TimerClkDisable(Timer_id id);
Timer_set TimerClkGet(Timer_id id);
//************************************************************

//Timer GPIO config
void TimerConfigGPIO(Timer_id id, gpio_bus bus, gpio_drive str);
//***************************************************************

ULI TimerSetAddress(Timer_id id, ULI reg);

//Timer config
void TimerSetConfig(Timer_id id,Timer_config config);
Timer_config TimerGetConfig(Timer_id id);
//**********************************************************

//RTC
void TimerRTCStallSet(Timer_id id, Timer_set set);
Timer_set TimerRTCStallGet(Timer_id id);
ULI TimerRTCGetPredivider(Timer_id id);
//***********************************************************

//SYNC
void TimerSyncSet(Timer_id id, Timer_sync sync);
Timer_sync TimerSyncGet(Timer_id id);
//*****************************************************

//Timer INT
void TimerINTSetTrigger(Timer_id id, Timer_INT INT);
void TimerINTClrTrigger(Timer_id id, Timer_INT INT);
ULI TimerINTGetTrigger(Timer_id id);
ULI TimerINTGetOcurrance(Timer_id id);
ULI TimerINTGetStatus(Timer_id id);
void TimerINTClr(Timer_id id, Timer_INT INT);
//**********************************************************

                   /*************************** TimerA  ******************************************/

//Timer Setup
void TimerAEnable(Timer_id id);
void TimerADisable(Timer_id id);
Timer_set TimerAGetStatus(Timer_id id);
void TimerAStallSet(Timer_id id, Timer_set set);
Timer_set TimerAStallGet(Timer_id id);
void TimerAEventSet(Timer_id id, Timer_event event);
Timer_event TimerAEventGet(Timer_id id);
//*************************************************

//values
void TimerALoadSetValue(Timer_id id, ULI value);
ULI TimerALoadGetValue(Timer_id id);
void TimerAMatchSetValue(Timer_id id, ULI value); //set duty cycle with load in PWM
ULI TimerAMatchGetValue(Timer_id id);
void TimerAPrescalerSetValue(Timer_id id, ULI value);
ULI TimerAPrescalerGetValue(Timer_id id);
void TimerAMatchPrescalerSetValue(Timer_id id, ULI value);
ULI TimerAMatchPrescalerGetValue(Timer_id id);
ULI TimerACounterEdgesGetValue(Timer_id id);
void TimerACounterEdgesSetValue(Timer_id id, ULI value);
ULI TimerAValueGetCurrent(Timer_id id);
ULI TimerASnapshotPrescalerGetValue(Timer_id id);
ULI TimerAPrescalerGetCurrent(Timer_id id);
//*********************************************************

//Timer mode
void TimerASetMode(Timer_id id, Timer_mode mode);
Timer_mode TimerAGetMode(Timer_id id);
//****************************************************

//PWM
void TimerAPWMEnable(Timer_id id);
void TimerAPWMDisable(Timer_id id);
Timer_set TimerAPWMGet(Timer_id id);
void TimerAPWMSetINT(Timer_id id, Timer_set set);
Timer_set TimerAPWMGetINT(Timer_id id);
void TimerAPWMSetLegacy(Timer_id id, Timer_set set);
Timer_set TimerAPWMGetLegacy(Timer_id id);
void TimerAPWMSetOutput(Timer_id id, Timer_pwm_output output);
Timer_pwm_output TimerAPWMGetOutput(Timer_id id);
//****************************************************

//Capture mode
void TimerACaptureSetMode(Timer_id id, Timer_capture_mode mode);
Timer_capture_mode TimerACaptureGetMode(Timer_id id);
//*************************************************************************

//one shot and periodic
void TimerAMatchSetINT(Timer_id id, Timer_set set);
Timer_set TimerAMatchGetINT(Timer_id id);
void TimerATriggerSet(Timer_id id, Timer_trigger_action trigger); //and PWM
Timer_trigger_action TimerATriggerGet(Timer_id id);
void TimerASetSnapshot(Timer_id id, Timer_set set);//periodic only
Timer_set TimerAGetSnapshot(Timer_id id);
void TimerATriggerADCSet(Timer_id id, Timer_set set);
Timer_set TimerATriggerADCGet(Timer_id id);
//****************************************************

//Timer counter
void TimerACounterSetDirection(Timer_id id, Timer_count_direction direction);
Timer_count_direction TimerACounterGetDirection(Timer_id id);
//*********************************************************************

//Timer value registers
void TimerAMatchSetUpdate(Timer_id id, Timer_match_update update);
Timer_match_update TimerAMatchGetUpdate(Timer_id id);
void TimerAValueSetUpdate(Timer_id id, Timer_match_update update);
Timer_match_update TimerAValueGetUpdate(Timer_id id);
//**********************************************************************

/*************************** TimerB  ******************************************/

//Timer Setup
void TimerBEnable(Timer_id id);
void TimerBDisable(Timer_id id);
Timer_set TimerBGetStatus(Timer_id id);
void TimerBStallSet(Timer_id id, Timer_set set);
Timer_set TimerBStallGet(Timer_id id);
void TimerBEventSet(Timer_id id, Timer_event event);
Timer_event TimerBEventGet(Timer_id id);
//*************************************************

//values
void TimerBLoadSetValue(Timer_id id, ULI value);
ULI TimerBLoadGetValue(Timer_id id);
void TimerBMatchSetValue(Timer_id id, ULI value); //set duty cycle with load in PWM
ULI TimerBMatchGetValue(Timer_id id);
void TimerBPrescalerSetValue(Timer_id id, ULI value);
ULI TimerBPrescalerGetValue(Timer_id id);
void TimerBMatchPrescalerSetValue(Timer_id id, ULI value);
ULI TimerBMatchPrescalerGetValue(Timer_id id);
ULI TimerBCounterEdgesGetValue(Timer_id id);
void TimerBCounterEdgesSetValue(Timer_id id, ULI value);
ULI TimerBValueGetCurrent(Timer_id id);
ULI TimerBSnapshotPrescalerGetValue(Timer_id id);
ULI TimerBPrescalerGetCurrent(Timer_id id);
//*********************************************************

//Timer mode
void TimerBSetMode(Timer_id id, Timer_mode mode);
Timer_mode TimerBGetMode(Timer_id id);
//****************************************************

//PWM
void TimerBPWMEnable(Timer_id id);
void TimerBPWMDisable(Timer_id id);
Timer_set TimerBPWMGet(Timer_id id);
void TimerBPWMSetINT(Timer_id id, Timer_set set);
Timer_set TimerBPWMGetINT(Timer_id id);
void TimerBPWMSetLegacy(Timer_id id, Timer_set set);
Timer_set TimerBPWMGetLegacy(Timer_id id);
void TimerBPWMSetOutput(Timer_id id, Timer_pwm_output output);
Timer_pwm_output TimerBPWMGetOutput(Timer_id id);
//****************************************************

//Capture mode
void TimerBCaptureSetMode(Timer_id id, Timer_capture_mode mode);
Timer_capture_mode TimerBCaptureGetMode(Timer_id id);
//*************************************************************************

//one shot and periodic
void TimerBMatchSetINT(Timer_id id, Timer_set set);
Timer_set TimerBMatchGetINT(Timer_id id);
void TimerBTriggerSet(Timer_id id, Timer_trigger_action trigger); //and PWM
Timer_trigger_action TimerBTriggerGet(Timer_id id);
void TimerBSetSnapshot(Timer_id id, Timer_set set);//periodic only
Timer_set TimerBGetSnapshot(Timer_id id);
void TimerBTriggerADCSet(Timer_id id, Timer_set set);
Timer_set TimerBTriggerADCGet(Timer_id id);
//****************************************************

//Timer counter
void TimerBCounterSetDirection(Timer_id id, Timer_count_direction direction);
Timer_count_direction TimerBCounterGetDirection(Timer_id id);
//*********************************************************************

//Timer value registers
void TimerBMatchSetUpdate(Timer_id id, Timer_match_update update);
Timer_match_update TimerBMatchGetUpdate(Timer_id id);
void TimerBValueSetUpdate(Timer_id id, Timer_match_update update);
Timer_match_update TimerBValueGetUpdate(Timer_id id);
//**********************************************************************

#endif /* TIMER_H_ */
