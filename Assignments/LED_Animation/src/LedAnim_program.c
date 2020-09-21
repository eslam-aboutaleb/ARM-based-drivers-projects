/*////////////////////////////////////////////////////////////////////////////// */
/* Author: Eslam Ehab Aboutaleb                                                  */
/* File:  LedAnim_program.c                                                      */
/* Version: V01                                                                  */
/* Date: 28-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"
#include "LED_interface.h"
#include "SYSTICK_interface.h"
#include "LedAnim_interface.h"
#include "LedAnim_config.h"

/* ************************************************************************************************************ */
/*Static Global variables*/

static uint8 Static_u8BingBongCounter     = 		0;
static uint8 Static_u8IN_OUT_Counter      = 		0;
static uint8 Static_u8BlinkCounter  	  = 		0;

static uint8 Static_u8BlinkFlag 	      =		    E_NOK;
static uint8 Static_u8InOutFlag           =			E_NOK;

/* ************************************************************************************************************ */

/*Static functions prototypes*/
static void LedAnim_vSet(tLED xCopy_LedNum);
static void LedAnim_vSetDouble(tLED xCopy_Led_1_Num, tLED xCopy_Led_2_Num);
static void LedAnim_vSetAll(tLED_State Copy_xLedState);
static uint8 LedAnim_u8BingBong(void);
static uint8 LedAnim_u8IN_OUT(void);
static uint8 LedAnim_u8Blink(void);
static void LedAnim_vClrFlags(void);
static void LedAnim_vClrCounters(void);
static void LedAnim_vTask_1(void);
static void LedAnim_vTask_2(void);

/* ************************************************************************************************************ */
/*Static functions definitions*/
/* ************************************************************************************************************ */

static void LedAnim_vSet(tLED xCopy_LedNum)
{
	uint8 LOC_u8Index = 0;
	for(LOC_u8Index = LED_1 ; LOC_u8Index < LED_ANIM_N_LEDS; LOC_u8Index++)
	{
		if(LOC_u8Index != xCopy_LedNum) LED_vSetState((uint8)LOC_u8Index,LED_OFF);
	}
	LED_vSetState((uint8)xCopy_LedNum, LED_ON);
}

/* ************************************************************************************************************ */

static void LedAnim_vSetDouble(tLED xCopy_Led_1_Num, tLED xCopy_Led_2_Num)
{
	tLED LOC_u8Index = (uint8)LED_1;
	for(LOC_u8Index = LED_1 ; LOC_u8Index < (uint8)LED_ANIM_N_LEDS; LOC_u8Index++)
	{
		if(LOC_u8Index != xCopy_Led_1_Num || LOC_u8Index != xCopy_Led_2_Num)
			LED_vSetState((uint8)LOC_u8Index,LED_OFF);
	}
	LED_vSetState((uint8)xCopy_Led_1_Num,LED_ON);
	LED_vSetState((uint8)xCopy_Led_2_Num,LED_ON);
}

/* ************************************************************************************************************ */

static void LedAnim_vSetAll(tLED_State Copy_xLedState)
{
	tLED LOC_u8Index = (uint8)LED_1;
	if(Copy_xLedState == LED_OFF)
	{
		for(LOC_u8Index = LED_1; LOC_u8Index < (uint8)LED_ANIM_N_LEDS; LOC_u8Index++)
		{
			LED_vSetState((uint8)LOC_u8Index,LED_OFF);
		}
	}
	else
	{
		for(LOC_u8Index = LED_1; LOC_u8Index < (uint8)LED_ANIM_N_LEDS; LOC_u8Index++)
		{
			LED_vSetState((uint8)LOC_u8Index,LED_ON);
		}
	}
}

/* ************************************************************************************************************ */

static void LedAnim_vClrFlags(void)
{
	/*Clear In Out flag*/
	Static_u8InOutFlag       =		E_NOK;
	/*Clear Blink flag*/
	Static_u8BlinkFlag       =	    E_NOK;
}

/* ************************************************************************************************************ */

static void LedAnim_vClrCounters(void)
{
	/*Clear Bing bong counter*/
	Static_u8BingBongCounter = 		0;
	/*Clear IN OUT counter*/
	Static_u8IN_OUT_Counter  = 		0;
	/*Clear Blink counter*/
	Static_u8BlinkCounter  	 = 		0;

}

/* ************************************************************************************************************ */

static uint8 LedAnim_u8BingBong(void)
{
	static tLED LOC_u8LED_Index = LED_1;
	static uint8 LOC_ReverseFlag = E_NOK;

	LedAnim_vSet((uint8)LOC_u8LED_Index);

	if(Static_u8BingBongCounter >= LED_ANIM_BING_BONG_COUNTS)
	{
		/* Last state of the task */
		LedAnim_vSet((uint8)LOC_u8LED_Index);
		return E_OK;
	}

	if(LOC_ReverseFlag == E_NOK)
	{
		LOC_u8LED_Index++;

		if(LOC_u8LED_Index == (uint8)(LED_ANIM_N_LEDS-1))
		{
			LOC_ReverseFlag = E_OK;
		}
	}
	else
	{
		LOC_u8LED_Index--;
		if(LOC_u8LED_Index == (uint8)LED_1)
		{
			LOC_ReverseFlag = E_NOK;

			Static_u8BingBongCounter++;
		}
	}
	return E_NOK;
}

/* ************************************************************************************************************ */

static uint8 LedAnim_u8IN_OUT(void)
{
	static uint8 LOC_ReverseFlag = E_NOK;
	static uint8 LOC_u8Index	 = 0;
	/*Divide number of leds by two to get the middle led*/
	uint8 LOC_u8MiddleLed = (LED_ANIM_N_LEDS/2)-1;


	LedAnim_vSetDouble((uint8)LOC_u8MiddleLed - (LOC_u8Index)  ,(uint8)LOC_u8MiddleLed + (LOC_u8Index +1));

	if(Static_u8IN_OUT_Counter >= LED_ANIM_IN_OUT_COUNTS)
	{
		/*Last state of the task*/
		LedAnim_vSetDouble((uint8)LOC_u8MiddleLed - (LOC_u8Index)  ,(uint8)LOC_u8MiddleLed + (LOC_u8Index +1));
		return E_OK;
	}
	if(LOC_ReverseFlag == E_NOK)
	{

		LOC_u8Index++;

		if(LOC_u8Index == LOC_u8MiddleLed)
		{
			LOC_ReverseFlag = E_OK;

		}
	}
	else
	{
		LOC_u8Index--;

		if(LOC_u8Index == 0)
		{
			LOC_ReverseFlag = E_NOK;
			Static_u8IN_OUT_Counter++;
		}
	}
	return E_NOK;
}

/* ************************************************************************************************************ */

static uint8 LedAnim_u8Blink(void)
{
	static uint8 LOC_u8Off_Flag = E_NOK;

	if(Static_u8BlinkCounter >= LED_ANIM_BLINK_COUNTS)
	{
		return E_OK;
	}
	if(LOC_u8Off_Flag == E_NOK)
	{
		LedAnim_vSetAll(LED_ON);
		LOC_u8Off_Flag = 1;
	}
	else
	{
		LedAnim_vSetAll(LED_OFF);
		LOC_u8Off_Flag = E_NOK;
		Static_u8BlinkCounter++;
	}
	return E_NOK;
}


/* Update sequence:
 * Ping bong 4 times 200 milliseconds per second for each led
 * IN OUT 4 times 200 milliseconds per second for each led
 *  Blink all the LEDs 4 times 500 milliseconds per second for each led */
/* ************************************************************************************************************ */

static void LedAnim_vTask_1(void)
{
	static uint16 LOC_u16TimeCounter = 0;
	LOC_u16TimeCounter += SYSTICK_TIMER_TICK_MS;

	if(LOC_u16TimeCounter != LED_ANIM_BING_BONG_TICK_MS) return;

	LOC_u16TimeCounter = 0;

	/* Check the Blink task to skip the update if it is running */
	if(Static_u8BlinkFlag == E_OK) return;

	if(Static_u8InOutFlag == E_NOK)
	{
		if(LedAnim_u8BingBong() == E_OK)
		{
			Static_u8InOutFlag  =  E_OK;
		}
	}

	if(Static_u8InOutFlag != E_OK) return;

	if(LedAnim_u8IN_OUT() == E_OK)
	{
		Static_u8BlinkFlag = E_OK;
	}
}

/* ************************************************************************************************************ */

static void LedAnim_vTask_2(void)
{
	static uint16 LOC_u16TimeCounter = 0;
	LOC_u16TimeCounter += SYSTICK_TIMER_TICK_MS;

	if(LOC_u16TimeCounter != LED_ANIM_BLINK_TICK_MS ) return;

	LOC_u16TimeCounter = 0;

	if(Static_u8BlinkFlag != E_OK) return;

	if(LedAnim_u8Blink() == E_OK)
	{
		LedAnim_vClrFlags();
		LedAnim_vClrCounters();
	}
}

/* ************************************************************************************************************ */
/* Global Functions definitions*/
/* ************************************************************************************************************ */

void LedAnim_vUpdate(void)
{
	LedAnim_vTask_1();
	LedAnim_vTask_2();
}
