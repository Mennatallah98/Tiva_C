

/**
 * main.c
 */
#include"Timer.h"

int main(void)
{
    TimerClkEnable(TIMER1);
    TimerClkEnable(TIMERWide0);


    TimerSetConfig(TIMER1,Seprated);
    Timer_config config = TimerGetAddress(TIMER1);

    TimerConfigGPIO(TIMER1, AHB, Drive_8mA);

    TimerASetMode(TIMER1, Capture);
    Timer_mode modeA = TimerAGetMode(TIMER1);

    TimerACaptureSetMode(TIMER1, EdgeTime);
    Timer_capture_mode capture_mode = TimerACaptureGetMode(TIMER1);

    TimerAPWMEnable(TIMER1);
    modeA = TimerAGetMode(TIMER1);
    capture_mode = TimerACaptureGetMode(TIMER1);

    TimerAPWMDisable(TIMER1);
    modeA = TimerAGetMode(TIMER1);
    capture_mode = TimerACaptureGetMode(TIMER1);

    TimerAEventSet(TIMER1, BothEdges);

    //TimerSyncSet(TIMER1, TimerA);
    //Timer_sync sync = TimerSyncGet(TIMER1);

	return 0;
}
