/*////////////////////////////////////////////////////////////////////////////// */
/* Author:  Eslam Ehab Aboutaleb                                                 */
/* File:   	Systick_program.c                                                    */
/* Version: V01                                                                  */
/* Date: 	28-8-2020                                                            */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"

/************************************************************************************************************* */
/*Static functions prototypes*/
/************************************************************************************************************* */
static void (*SysTick_CallBack) (void);

/************************************************************************************************************* */
/*Functions definition */
/************************************************************************************************************* */

void STK_vInit(uint8 Copy_xClockSource)
{
	switch(Copy_xClockSource)
	{
	case STK_CLK_SRC_AHB_DIVIDED_BY_8:
		CLEAR_BIT(SYSTICK->CTRL,2);
		break;
	case STK_CLK_SRC_AHB:
		SET_BIT(SYSTICK->CTRL,2);
		break;
	default:
		/*No Action*/
		break;
	}

	/*Disable systick exception*/
	STK_DISABLE_EXCEPTION();
}


/************************************************************************************************************* */

void STK_vSetIntervalPeriodic(uint32 Copy_u32Ticks ,uint32 Copy_u32TicksTybe , void (* Copy_vpFunc) (void))
{
	/*Assign ticks to load register*/
	STK_UPDATE_LOAD_REGISTER(Copy_u32Ticks * Copy_u32TicksTybe );
	/*Assign the function to the callback function */
	SysTick_CallBack = Copy_vpFunc;
	/*Enable Systick exception*/
	STK_ENABLE_EXCEPTION();
	/*Start the counter*/
	STK_START_COUNTER();
}

/************************************************************************************************************* */

void STK_vStopInterval(void)
{
	/*Disable systick exception*/
	STK_DISABLE_EXCEPTION();
	/*Stop the counter*/
	STK_Stop_COUNTER();
}

/************************************************************************************************************* */

uint32 STK_u32GetRemainingTime(uint32 Copy_u32TicksTybe)
{
	return ((SYSTICK->VAL)*Copy_u32TicksTybe);
}

/************************************************************************************************************* */

uint32 STK_u32GetElapsedTime(uint32 Copy_u32TicksTybe)
{
	return (((SYSTICK->LOAD) - (SYSTICK->VAL)) * Copy_u32TicksTybe);
}

/************************************************************************************************************* */

void SysTick_Handler(void)
{
	SysTick_CallBack();
}
