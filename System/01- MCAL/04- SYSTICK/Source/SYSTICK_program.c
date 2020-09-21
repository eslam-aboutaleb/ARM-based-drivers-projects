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
/*Static global variables*/
/************************************************************************************************************* */
/* Variable to define interval mode of Systick*/
static volatile uint8 STK_u8IntervalMode;

/************************************************************************************************************* */
/*Private macros*/
/************************************************************************************************************* */
/* Local macros to set and get Interval mode for Systick exception*/
#define STK_SET_INTERVAL_MODE(MODE)                          STK_u8IntervalMode = MODE
#define STK_GET_INTERVAL_MODE()                             (STK_u8IntervalMode & 1)

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

void STK_vSetBusyWait(uint32 Copy_u32Ticks, uint32 Copy_u32TicksTybe)
{
	/*Assign ticks to load register*/
	STK_UPDATE_LOAD_REGISTER(Copy_u32Ticks * Copy_u32TicksTybe );
	/*Start timer*/
	STK_START_COUNTER();
	/*Wait until busy wait flag is raised */
	STK_BUSY_WAIT_FLAG();
	/*Stop timer*/
	STK_STOP_COUNTER();
	/*Clear Systick registers*/
	STK_CLEAR_REGISTERS();
}

/************************************************************************************************************* */

void STK_vSetIntervalSingle  ( uint32 Copy_u32Ticks, uint32 Copy_u32TicksTybe, void (*Copy_vpFuncPtr)(void) )
{
	/*Stop timer*/
	STK_STOP_COUNTER();
	/*Clear Systick registers*/
	STK_CLEAR_REGISTERS();
	/*Assign ticks to load register*/
	STK_UPDATE_LOAD_REGISTER(Copy_u32Ticks * Copy_u32TicksTybe );
	/* Assign callBack function */
	SysTick_CallBack = Copy_vpFuncPtr;
	/* Set Mode to Single */
	STK_SET_INTERVAL_MODE(STK_SINGLE_INTERVAL_MODE);
	/*Enable Systick exception*/
	STK_ENABLE_EXCEPTION();
	/*Start timer*/
	STK_START_COUNTER();
}

/************************************************************************************************************* */

void STK_vSetIntervalPeriodic(uint32 Copy_u32Ticks ,uint32 Copy_u32TicksTybe , void (* Copy_vpFuncPtr) (void))
{
	/*Assign ticks to load register*/
	STK_UPDATE_LOAD_REGISTER(Copy_u32Ticks * Copy_u32TicksTybe );
	/*Assign the function to the callback function */
	SysTick_CallBack = Copy_vpFuncPtr;
	/* Set Mode to Single */
	STK_SET_INTERVAL_MODE(STK_PERIODIC_INTERVAL_MODE);
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
	STK_STOP_COUNTER();
	/*Clear Systick registers*/
	STK_CLEAR_REGISTERS();
}

/************************************************************************************************************* */

uint32 STK_u32GetRemainingTime(uint32 Copy_u32TicksTybe)
{
	return ((SYSTICK->VAL) * Copy_u32TicksTybe);
}

/************************************************************************************************************* */

uint32 STK_u32GetElapsedTime(uint32 Copy_u32TicksTybe)
{
	return (((SYSTICK->LOAD) - (SYSTICK->VAL)) * Copy_u32TicksTybe);
}

/************************************************************************************************************* */

void SysTick_Handler(void)
{
	uint8 Local_u8Temporary = 0;
	if(STK_GET_INTERVAL_MODE() == STK_SINGLE_INTERVAL_MODE)
	{
		/*Disable systick exception*/
		STK_DISABLE_EXCEPTION();
		/*Stop the counter*/
		STK_STOP_COUNTER();
		/*Clear Systick registers*/
		STK_CLEAR_REGISTERS();
	}
	else
	{
		/*No Action*/
	}

	/*Execute callback function*/
	SysTick_CallBack();

	/*Clear exception flag*/
	Local_u8Temporary = GET_BIT(SYSTICK->CTRL,16);
}
