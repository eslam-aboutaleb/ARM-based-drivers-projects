/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 21-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef SOUND_PRIVATE_H
#define SOUND_PRIVATE_H

#include "Timer_interface.h"

static void SoundM_vOut(void);

#define SoundM_SetIntervalPeriodic(Timeus,Func)             TIM_vSetIntervalPeriodic(TIMER1,Timeus,TIM_TICKS_US,Func)

#define SOUNDM_REMOTE_OFF									0
#define SOUNDM_REMOTE_ON										1


#endif
