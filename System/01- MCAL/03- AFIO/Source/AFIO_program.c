/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date	  : 31-8-2020                                                            */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "AFIO_interface.h"
#include "AFIO_private.h"

/************************************************************************************************************* */
void AFIO_vReMap(uint32 Copy_u32GPIO_Remap ,uint8 Copy_u8RemapState)
{
	if (Copy_u8RemapState == 1)
	{
		AFIO->MAPR |=  Copy_u32GPIO_Remap;
	}
	else
	{
		AFIO->MAPR &=~ Copy_u32GPIO_Remap;
	}
}

/************************************************************************************************************* */

void AFIO_vEXTILineConfig(uint8 Copy_u8EXTI_Line, uint8 Copy_u8PortNum)
{
	/*Shift the line number by 2 it is equal to Copy_u8EXTI_Line%4 */
	uint8 Local_u8RegIndex = Copy_u8EXTI_Line >> 0X02;

	AFIO->EXTICR[Local_u8RegIndex] &= ~((0xF)<<(Copy_u8EXTI_Line * 4));
	AFIO->EXTICR[Local_u8RegIndex] |=  ((Copy_u8PortNum) << (4 * (Copy_u8EXTI_Line)));
}
