/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: CRC_program.c		                                                 */
/* Version	: V01                                                                */
/* Date		: 23 - 12 - 2020                                                     */
/* ***************************************************************************** */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "CRC_interface.h"
#include "CRC_private.h"
#include "CRC_reg.h"

/* ************************************************************************************************************ */
										/* Public functions definitions */
/* ************************************************************************************************************ */

void CRC_vResetDR(void)
{
	/* Reset CRC generator */
	CRC->CR = CRC_CR_RESET;
}

/* ************************************************************************************************************ */

uint32 CRC_u32CalcCRC(const uint32 Copy_u32Data)
{
	/* Reset CRC data register */
	CRC_vResetDR();

	CRC->DR = Copy_u32Data;

	return (CRC->DR);
}

/* ************************************************************************************************************ */

Error_Status CRC_xCalcBlockCRC(uint32 *pBuffer,const uint32 Copy_u32BufferLength ,const uint32 *pu32DR_Val)
{
	/* Check if the buffer is valid */
	if(pBuffer == NULL)
	{
		/* Null pointer detected */
		return E_NOK;
	}

	uint32 Local_u32Index = 0;

	/* Reset CRC data register */
	CRC_vResetDR();

	for(Local_u32Index = 0; Local_u32Index < Copy_u32BufferLength; Local_u32Index++)
	{
		CRC->DR = pBuffer[Local_u32Index];
	}

	/* Save the final value in the data register */
	*pu32DR_Val = CRC->DR;

	return E_OK;
}

/* ************************************************************************************************************ */

uint32 CRC_u32GetCRC(void)
{
	return (CRC->DR);
}

/* ************************************************************************************************************ */

void CRC_vSetIDRegister(const uint8 IDValue)
{
	CRC->IDR = IDValue;
}

/* ************************************************************************************************************ */

uint8 CRC_u8GetIDRegister(void)
{
	return (uint8)(CRC->IDR);
}

