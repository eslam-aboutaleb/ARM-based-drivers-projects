/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date	  : 31-8-2020                                                            */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"

/************************************************************************************************************* */

/*Static array of pointers to function to be executed in EXTI handler*/
static void (*EXTI_vEXTI_CallBack[19])(void);

/************************************************************************************************************* */
/*Public function definitions*/
/************************************************************************************************************* */

void EXTI_vSetSignalLatch(uint8 Copy_u8EXTI_Line , uint8 Copy_u8EXTI_TrigerMode)
{
	switch(Copy_u8EXTI_TrigerMode)
	{
	case EXTI_TRIGGER_FALLING_EDGE:
		SET_BIT(EXTI->FTSR,Copy_u8EXTI_Line);
		break;
	case EXTI_TRIGGER_RISING_EDGE:
		SET_BIT(EXTI->RTSR,Copy_u8EXTI_Line);
		break;
	case EXTI_TRIGGER_ON_CHANGE:
		SET_BIT(EXTI->FTSR,Copy_u8EXTI_Line);
		SET_BIT(EXTI->RTSR,Copy_u8EXTI_Line);
		break;
	default:
		break;
	}

	/*Enable EXTI for the user's liner*/
	SET_BIT(EXTI->IMR,Copy_u8EXTI_Line);
}

/************************************************************************************************************* */

void EXTI_vDeInit(void)
{
	/*All the EXTI registers are uninitialized*/
	EXTI->IMR  = 0x00000000;
	EXTI->EMR  = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->PR   = 0x000FFFFF;
}

/************************************************************************************************************* */

void EXTI_vEnableEXTI(uint8 Copy_u8EXTI_Line)
{
	SET_BIT(EXTI->IMR,Copy_u8EXTI_Line);
}

/************************************************************************************************************* */

void EXTI_vDisableEXTI(uint8 Copy_u8EXTI_Line)
{
	CLEAR_BIT(EXTI->IMR,Copy_u8EXTI_Line);
}

/************************************************************************************************************* */

uint8 EXTI_u8GetFlagStatus(uint8 Copy_u8EXTI_Line)
{
	uint8 LOC_u8LineFlagStatus = 0;

	LOC_u8LineFlagStatus = GET_BIT(EXTI->PR,Copy_u8EXTI_Line);

	return LOC_u8LineFlagStatus;
}

/************************************************************************************************************* */

void EXTI_vSoftwareTrigger(uint8 Copy_u8EXTI_Line)
{
	SET_BIT(EXTI->SWIER , Copy_u8EXTI_Line);
}

/************************************************************************************************************* */

void EXTI_vSetCallBack(uint8 Copy_u8EXTI_Line, void(*Copy_vFuncPtr)(void))
{
	EXTI_vEXTI_CallBack[Copy_u8EXTI_Line] = Copy_vFuncPtr;
}

/************************************************************************************************************* */

void EXTI0_IRQHandler(void)
{
	/*Execute callback function*/
	EXTI_vEXTI_CallBack[0]();
	/*Clear pending flag*/
	SET_BIT(EXTI->PR,EXTI_LINE0);
}


void EXTI1_IRQHandler(void)
{
	/*Execute callback function*/
	EXTI_vEXTI_CallBack[1]();
	/*Clear pending flag*/
	SET_BIT(EXTI->PR,EXTI_LINE1);
}

