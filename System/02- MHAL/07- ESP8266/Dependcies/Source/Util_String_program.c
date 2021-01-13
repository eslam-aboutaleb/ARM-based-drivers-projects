#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Util_String_interface.h"
#include "Util_String_private.h"

void UtilString_vNumtoStr(sint32 Copy_s32Num,uint8 *pu8Buffer)
{
	sint32 		 Local_s32Index		= 	0;
	sint32 		 Local_s32Copy 		= 	0;
	Flag_Status  Local_xSignFlag	=	E_NOK;
	uint8		 Local_xSignBorder	=	0;

	/* Checks if the number is negative */
	if(Copy_s32Num < 0)
	{
		/* Turn it to positive */
		Copy_s32Num 	= -1 * Copy_s32Num;
		/* Raise sign flag*/
		Local_xSignFlag = E_OK;
	}

	/* Buffer to count number of digits in the number */
	Local_s32Copy = Copy_s32Num;

	while(Local_s32Copy > 0)
	{
		Local_s32Copy /=10;
		Local_s32Index++;
	}
	/* If the number is negative */
	if(Local_xSignFlag == E_OK)
	{
		/* Increase the index to be able to store sign in the buffer */
		Local_s32Index++;
		/* Assign the sign in the first index */
		pu8Buffer[0] = '-';
		/* Leave the first index empty for the sign */
		Local_xSignBorder = 1;
	}
	pu8Buffer[Local_s32Index--] = '\0';
	while(Local_s32Index >= Local_xSignBorder)
	{
		/* Convert the numbers to characters and store them in the buffer */
		pu8Buffer[Local_s32Index--] = ((Copy_s32Num % 10) + '0');
		Copy_s32Num /= 10;
	}
}


Flag_Status UtilString_xFindWord(uint8 *pu8WordToFind , uint8 *pu8Line)
{
	uint16 Local_u16Index	=	0;
	uint16 Local_u16Index2	=	0;
	Flag_Status Local_xFlag	=	0;

	for(Local_u16Index = 0; pu8Line[Local_u16Index] != '\0'; Local_u16Index++ )
	{
		if(pu8Line[Local_u16Index] == pu8WordToFind[0])
		{
			Local_xFlag	=	E_OK;
			for(Local_u16Index2 = 0; pu8WordToFind[Local_u16Index2] != '\0'; Local_u16Index2++ )
			{
				if(pu8Line[Local_u16Index + Local_u16Index2] != pu8WordToFind[Local_u16Index2])
				{
					Local_xFlag	=	E_NOK;
					break;
				}
			}
		}

		if(E_OK == Local_xFlag)
		{
			break;
		}
	}

	return Local_xFlag;
}


uint16 UtilString_u16HexToDecLittleEndian ( uint8 *Copy_HexNum )
{
	uint16 Base_Mul = (uint16)((UtilString_u32Pow(16,UtilString_u16countStr(Copy_HexNum)))/16);
	uint16 DecNum = 0;
	uint16 FinalNum = 0;
	uint8 Local_u8Iterator = 0;

	for(Local_u8Iterator = 0; Copy_HexNum[Local_u8Iterator] != '\0'; Local_u8Iterator++ , Base_Mul= Base_Mul/16)
	{
		if((Copy_HexNum[Local_u8Iterator] >= '0') && (Copy_HexNum[Local_u8Iterator] <= '9'))
		{
			/*Convert the number from char to integer*/
			DecNum = Copy_HexNum[Local_u8Iterator] - '0';

			DecNum *= Base_Mul;

			FinalNum+=DecNum;
		}
		else if((Copy_HexNum[Local_u8Iterator] >= 'A') && (Copy_HexNum[Local_u8Iterator] <= 'F') )
		{
			DecNum = Copy_HexNum[Local_u8Iterator] - 55;
			DecNum *= Base_Mul;
			FinalNum+=DecNum;
		}
		else if((Copy_HexNum[Local_u8Iterator] >= 'a') && (Copy_HexNum[Local_u8Iterator] <= 'f'))
		{
			DecNum = (Copy_HexNum[Local_u8Iterator] - 86);
			DecNum = (DecNum * Base_Mul)-1;
			FinalNum+=DecNum;
		}
		else
		{
			/* No Action */
		}
	}
	return FinalNum;
}

Error_Status UtilString_xStrToNum(uint8 *pu8Str , uint32 *pu32Result)
{
	uint16 Local_u16Index = 0;
	uint16 Loca_u16Mul;
	uint16 LocaL_u16Temp = 0;
	uint32 Local_u32ActNum = 0;
	uint16 Local_u16Length =UtilString_u16countStr(pu8Str);

	Loca_u16Mul = UtilString_u32Pow(10,(Local_u16Length - 1));

	for(Local_u16Index = 0;Local_u16Index < Local_u16Length;Local_u16Index++ , Loca_u16Mul/=10)
	{
		if(pu8Str[Local_u16Index] >= '0' && pu8Str[Local_u16Index] <= '9')
		{
			LocaL_u16Temp = pu8Str[Local_u16Index] - '0';
			Local_u32ActNum +=(uint32) (Loca_u16Mul * LocaL_u16Temp);
		}
		else{
			return E_NOK;
		}
	}

	*pu32Result = Local_u32ActNum;
	return E_OK;
}


uint16 UtilString_u16countStr(uint8 *pu8Str)
{
	uint16 Local_u16Counter = 0;
	while(*pu8Str++)
	{
		Local_u16Counter++;
	}
	return Local_u16Counter;
}

uint32 UtilString_u32Pow(uint32 Copy_u32Base ,uint32 Copy_u32Power)
{
	uint32 Local_u32Result = 1;
	while(Copy_u32Power--)
	{
		Local_u32Result *= Copy_u32Base;
	}

	return Local_u32Result;
}
