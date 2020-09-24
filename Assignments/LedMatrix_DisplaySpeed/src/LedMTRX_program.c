/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 1-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "LedMTRX_interface.h"
#include "LedMTRX_private.h"
#include "LedMTRX_config.h"
#include "Timer_interface.h"

/************************************************************************************************************* */

/*Alphabet letters array*/
static uint8 u8LedMtrx_Alphapet_Arr[28][8]={
		/*Byte A*/ {0b00000000,0b00111100,0b01100110,0b01100110,0b01111110,0b01100110,0b01100110,0b01100110},
		/*Byte B*/ {0b01111000,0b01001000,0b01001000,0b01110000,0b01001000,0b01000100,0b01000100,0b01111100},
		/*Byte C*/ {0b00000000,0b00011110,0b00100000,0b01000000,0b01000000,0b01000000,0b00100000,0b00011110},
		/*Byte D*/ {0b00000000,0b00111000,0b00100100,0b00100010,0b00100010,0b00100100,0b00111000,0b00000000},
		/*Byte E*/ {0b00000000,0b00111100,0b00100000,0b00111000,0b00100000,0b00100000,0b00111100,0b00000000},
		/*Byte F*/ {0b00000000,0b00111100,0b00100000,0b00111000,0b00100000,0b00100000,0b00100000,0b00000000},
		/*Byte G*/ {0b00000000,0b00111110,0b00100000,0b00100000,0b00101110,0b00100010,0b00111110,0b00000000},
		/*Byte H*/ {0b00000000,0b00100100,0b00100100,0b00111100,0b00100100,0b00100100,0b00100100,0b00000000},
		/*Byte I*/ {0b00000000,0b00111000,0b00010000,0b00010000,0b00010000,0b00010000,0b00111000,0b00000000},
		/*Byte J*/ {0b00000000,0b00011100,0b00001000,0b00001000,0b00001000,0b00101000,0b00111000,0b00000000},
		/*Byte K*/ {0b00000000,0b00100100,0b00101000,0b00110000,0b00101000,0b00100100,0b00100100,0b00000000},
		/*Byte L*/ {0b00000000,0b00100000,0b00100000,0b00100000,0b00100000,0b00100000,0b00111100,0b00000000},
		/*Byte M*/ {0b00000000,0b00000000,0b01000100,0b10101010,0b10010010,0b10000010,0b10000010,0b00000000},
		/*Byte N*/ {0b00000000,0b00100010,0b00110010,0b00101010,0b00100110,0b00100010,0b00000000,0b00000000},
		/*Byte O*/ {0b00000000,0b00111100,0b01000010,0b01000010,0b01000010,0b01000010,0b00111100,0b00000000},
		/*Byte P*/ {0b00000000,0b00111000,0b00100100,0b00100100,0b00111000,0b00100000,0b00100000,0b00000000},
		/*Byte Q*/ {0b00000000,0b00111100,0b01000010,0b01000010,0b01000010,0b01000110,0b00111110,0b00000001},
		/*Byte R*/ {0b00000000,0b00111000,0b00100100,0b00100100,0b00111000,0b00100100,0b00100100,0b00000000},
		/*Byte S*/ {0b00000000,0b00111100,0b00100000,0b00111100,0b00000100,0b00000100,0b00111100,0b00000000},
		/*Byte T*/ {0b00000000,0b01111100,0b00010000,0b00010000,0b00010000,0b00010000,0b00010000,0b00000000},
		/*Byte U*/ {0b00000000,0b01000010,0b01000010,0b01000010,0b01000010,0b00100100,0b00011000,0b00000000},
		/*Byte V*/ {0b00000000,0b00100010,0b00100010,0b00100010,0b00010100,0b00010100,0b00001000,0b00000000},
		/*Byte W*/ {0b00000000,0b10000010,0b10010010,0b01010100,0b01010100,0b00101000,0b00000000,0b00000000},
		/*Byte X*/ {0b00000000,0b01000010,0b00100100,0b00011000,0b00011000,0b00100100,0b01000010,0b00000000},
		/*Byte Y*/ {0b00000000,0b01000100,0b00101000,0b00010000,0b00010000,0b00010000,0b00010000,0b00000000},
		/*Byte Z*/ {0b00000000,0b00111100,0b00000100,0b00001000,0b00010000,0b00100000,0b00111100,0b00000000},
		/*Byte Space*/ {0b00000000,0b00111100,0b00000100,0b00001000,0b00010000,0b00100000,0b00111100,0b00000000}
};

static uint8 u8DisplaySpeed = LEDMTRX_INITDISPSPEED;
static uint8 u8DispState 	= LEDMTRX_RESUME;

/************************************************************************************************************* */

void LedMtrx_vDisableAllCols(void)
{
	uint8 Local_u8ColIndex = 0;
	for(Local_u8ColIndex = 0;Local_u8ColIndex< LED_MATRX_COLUMNS_N; Local_u8ColIndex++)
	{
		GPIO_vWritePortPin(LedMtrxCols_Map[Local_u8ColIndex].LedMtrx_Port,LedMtrxCols_Map[Local_u8ColIndex].LedMtrx_Pin,GPIO_HIGH);
	}
}

/************************************************************************************************************* */

static void LedMtrx_vSetRowVals(uint8 Copy_u8Val)
{
	uint8 Local_u8RowIndex = 0;
	uint8 Local_u8Temp	   = 0;
	uint8 Local_u8BitIndex = 0;
	for(Local_u8RowIndex = 0;Local_u8RowIndex< LED_MATRX_COLUMNS_N; Local_u8RowIndex++,Local_u8BitIndex++)
	{

		Local_u8Temp = (GET_BIT(Copy_u8Val,Local_u8BitIndex));
		GPIO_vWritePortPin(LedMtrxRows_Map[Local_u8RowIndex].LedMtrx_Port,LedMtrxRows_Map[Local_u8RowIndex].LedMtrx_Pin,Local_u8Temp);
		if(Local_u8BitIndex == 7)
		{
			Local_u8BitIndex = 0;
		}
	}
}

/************************************************************************************************************* */

static void LedMtrx_vSetCol(uint8 Copy_u8ColNum)
{
	GPIO_vWritePortPin(LedMtrxCols_Map[Copy_u8ColNum].LedMtrx_Port,LedMtrxCols_Map[Copy_u8ColNum].LedMtrx_Pin,LED_MATRX_COLS_STATE);
}

/************************************************************************************************************* */

void LedMtrx_vInit(void)
{
	uint8 Local_u8ColIndex = 0;
	uint8 Local_u8RowIndex = 0;
	for(Local_u8ColIndex=0;Local_u8ColIndex<LED_MATRX_COLUMNS_N;Local_u8ColIndex++)
	{
		GPIO_vInitPortPin(LedMtrxCols_Map[Local_u8ColIndex].LedMtrx_Port,LedMtrxCols_Map[Local_u8ColIndex].LedMtrx_Pin,GPIO_OUT);
	}
	LedMtrx_vDisableAllCols();
	for(Local_u8RowIndex=0;Local_u8RowIndex<LED_MATRX_COLUMNS_N;Local_u8RowIndex++)
	{
		GPIO_vInitPortPin(LedMtrxRows_Map[Local_u8RowIndex].LedMtrx_Port,LedMtrxRows_Map[Local_u8RowIndex].LedMtrx_Pin,GPIO_OUT);
		GPIO_vWritePortPin(LedMtrxRows_Map[Local_u8RowIndex].LedMtrx_Port,LedMtrxRows_Map[Local_u8RowIndex].LedMtrx_Pin,~LED_MATRX_ROWS_STATE);
	}
}

/************************************************************************************************************* */

void LedMtrx_vDisplayAlphabet(LedMtrx_Alphapet Copy_xAlphabet)
{
	uint8 Local_u8ColIndex  = 0;
	for(Local_u8ColIndex = 0;Local_u8ColIndex<LED_MATRX_COLUMNS_N;Local_u8ColIndex++)
	{
		LedMtrx_vDisableAllCols();
		LedMtrx_vSetRowVals(u8LedMtrx_Alphapet_Arr[Copy_xAlphabet][Local_u8ColIndex]);
		LedMtrx_vSetCol(Local_u8ColIndex);
		LedMtrx_vDelay(LED_MATRIX_DELAY_US);
	}
}

/************************************************************************************************************* */

void LedMtrx_vDisplayArr(uint8* Copy_pu8Arr)
{
	uint8 Local_u8ColIndex  = 0;
	for(Local_u8ColIndex = 0;Local_u8ColIndex<LED_MATRX_COLUMNS_N;Local_u8ColIndex++)
	{
		LedMtrx_vDisableAllCols();
		LedMtrx_vSetRowVals(Copy_pu8Arr[Local_u8ColIndex]);
		LedMtrx_vSetCol(Local_u8ColIndex);
		LedMtrx_vDelay(LED_MATRIX_DELAY_US);
	}
}

/************************************************************************************************************* */

void LedMtrx_vDisplayLine( uint8 *Copy_u8Line , uint8 Copy_u8ColsCount)
{
	uint8 Local_uint8LineIndex;
	uint8 Local_uint8WaitIndex;

	for (Local_uint8LineIndex = 0; Local_uint8LineIndex < Copy_u8ColsCount ; )
	{
		if(u8DispState == LEDMTRX_RESUME)
		{
			Local_uint8LineIndex++;
		}
		else
		{
			/*No Action*/
		}

		for ( Local_uint8WaitIndex = 0 ; Local_uint8WaitIndex < u8DisplaySpeed ;Local_uint8WaitIndex++ )
		{
			LedMtrx_vDisplayArr( Copy_u8Line + Local_uint8LineIndex   );
		}
	}
}

/************************************************************************************************************* */

void LedMtrx_vDisplayShapes( uint8 *Copy_u8ShapesArr , uint32 Copy_u32ColsCountDiv_8)
{
	uint32 Local_uint32LineIndex;
	uint8 Local_u8WaitIndex;

	for (Local_uint32LineIndex = 0; Local_uint32LineIndex < Copy_u32ColsCountDiv_8 ; )
	{
		if(u8DispState == LEDMTRX_RESUME)
		{
			Local_uint32LineIndex++;
		}
		else
		{
			/*No Action*/
		}

		for ( Local_u8WaitIndex = 0 ; Local_u8WaitIndex < u8DisplaySpeed ;Local_u8WaitIndex++ )
		{
			LedMtrx_vDisplayArr( Copy_u8ShapesArr + Local_uint32LineIndex*8   );
		}
	}
}

/************************************************************************************************************* */

void LedMtrx_vSetSpeed(uint8 Copy_u8SpeedCmd)
{
	switch(Copy_u8SpeedCmd)
	{
	case LEDMTRX_DECSPEED:
		if(u8DisplaySpeed <= LEDMTRX_SPEEDLIMIT1ST)
		{
			return;
		}
		u8DisplaySpeed -= LEDMTRX_SPEEDSTEP;
		break;

	case LEDMTRX_INCSPEED:
		if(u8DisplaySpeed >= LEDMTRX_SPEEDLIMIT2ND)
		{
			return;
		}
		u8DisplaySpeed += LEDMTRX_SPEEDSTEP;
		break;

	default:
		break;
	}
}

/************************************************************************************************************* */

void LedMtrx_vSetDispState(uint8 Copy_u8DispState)
{
	switch(Copy_u8DispState)
	{
	case LEDMTRX_STOP:
		u8DispState = LEDMTRX_STOP;
		break;
	case LEDMTRX_RESUME:
		u8DispState = LEDMTRX_RESUME;
		break;
	default:
		break;
	}
}

