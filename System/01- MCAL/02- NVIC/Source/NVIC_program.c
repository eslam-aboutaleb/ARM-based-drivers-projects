/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 20-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"
#include "NVIC_interface.h"
#include "NVIC_config.h"
#include "NVIC_private.h"
#include "NVIC_reg.h"
#include "SCB_private.h"

/*Variables*/
/*Static global variables*/

static uint32 Static_u32CurrentPriorityGroup; /* static global variable to indicate the current Priority Group */

/************************************************************************************************************* */
/*Functions definitions*/
/************************************************************************************************************* */

void NVIC_vPriorityGroupInit(uint32 Copy_u32PriorityGroup)
{
	/* Assign the desired group to the global priority group value*/
	Static_u32CurrentPriorityGroup = SCB_AIRCR_VECTKEY | Copy_u32PriorityGroup;

	SCB->AIRCR = Static_u32CurrentPriorityGroup;
}

/************************************************************************************************************* */

Error_Status NVIC_xEnableInterrupt(IRQnum_t Copy_xIntIndex)
{
	if(NVIC_IS_VALID_IRQN(Copy_xIntIndex) == E_NOK)
	{
		return E_NOK;
	}
	SET_BIT(NVIC->ISER[Copy_xIntIndex/32] , Copy_xIntIndex);

	return E_OK;
}

/************************************************************************************************************* */

Error_Status NVIC_xDisableInterrupt(IRQnum_t Copy_xIntIndex)
{
	if(NVIC_IS_VALID_IRQN(Copy_xIntIndex) == E_NOK)
	{
		return E_NOK;
	}

	SET_BIT(NVIC->ICER[Copy_xIntIndex/32] , Copy_xIntIndex);

	return E_OK;
}

/************************************************************************************************************* */

Error_Status NVIC_xSetPendingFlag(IRQnum_t Copy_xIntIndex)
{
	if(NVIC_IS_VALID_IRQN(Copy_xIntIndex) == E_NOK)
	{
		return E_NOK;
	}

	SET_BIT(NVIC->ISPR[Copy_xIntIndex/32] , Copy_xIntIndex);

	return E_OK;
}

/************************************************************************************************************* */

Error_Status NVIC_xClearPendingFlag(IRQnum_t Copy_xIntIndex)
{
	if(NVIC_IS_VALID_IRQN(Copy_xIntIndex) == E_NOK)
	{
		return E_NOK;
	}

	SET_BIT(NVIC->ICPR[Copy_xIntIndex/32] , Copy_xIntIndex);

	return E_OK;
}

/************************************************************************************************************* */

Error_Status NVIC_xReadIntState(IRQnum_t Copy_xIntIndex, uint8 *pu8IntState)
{
	if(NVIC_IS_VALID_IRQN(Copy_xIntIndex) == E_NOK)
	{
		return E_NOK;
	}

	*pu8IntState = GET_BIT (NVIC->IABR[Copy_xIntIndex/32], Copy_xIntIndex);

	return E_OK;
}

/************************************************************************************************************* */

IRQnum_t NVIC_xCheck_CurrentInt(void)
{
	/*Check from the first maskable interrupt*/
	IRQnum_t LOC_u8Index=0;
	IRQnum_t LOC_u8Index_2=0;
	uint8 LOC_u8State=0;
	/*Check all the interrupts if there is active one or not*/
	for(LOC_u8Index=0;LOC_u8Index<=59;LOC_u8Index++)
	{
		if (LOC_u8Index <= 31)
		{
			LOC_u8State = GET_BIT (NVIC->IABR[0], LOC_u8Index);
		}
		else if (LOC_u8Index <= 59)
		{
			LOC_u8Index_2 = LOC_u8Index;
			LOC_u8Index_2 -=32;
			LOC_u8State = GET_BIT (NVIC->IABR[1], LOC_u8Index_2);
		}
		else
		{
			/*No Action*/
		}
		/*If there is an active flag break the loop*/
		if(LOC_u8State == 1)
		{
			break;
		}
		else
		{
			/*No Action*/
		}
	}
	return LOC_u8Index;
}

/************************************************************************************************************* */

Error_Status NVIC_xSetpriority(IRQnum_t Copy_xIntIndex , uint8 Copy_u8GroupPriority , uint8 Copy_u8SubPriority)
{
	/*Check if the index is non-maskable interrupt OR more than the number of available interrupts*/
	if(Copy_xIntIndex < 0 || Copy_xIntIndex > NVIC_N_IRQNS)
	{
		return E_NOK;
	}
	else
	{
		/*No Action*/
	}

	/* Subtract the first priority group from the current priority group to get priority group index
	 * Divide the result by 256 (0x100) to convert the result to decimal
	 * Shift the group priority by the result
	 * Add the result of shifting to sub priority
	 */
	uint8 LOC_u8Priority = Copy_u8SubPriority |
			(Copy_u8GroupPriority << ((Static_u32CurrentPriorityGroup - (SCB_AIRCR_VECTKEY | NVIC_PRIORITY_GROUP_0)) / 256));

	/*Shift the priority to the first 4 MSB*/
	NVIC->IP[Copy_xIntIndex] = (LOC_u8Priority << 4);

	return E_OK;
}
