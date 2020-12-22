/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: TFTLCD_program.h		                                             */
/* Version	: V01                                                                */
/* Date		: 15 - 11 - 2020                                                     */
/* ***************************************************************************** */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SPI_interface.h"

#include "TFTLCD_interface.h"
#include "TFTLCD_config.h"
#include "TFTLCD_private.h"




/************************************************************************************************************* */
											/* functions Definition */
/************************************************************************************************************* */

void TFTLCD_vInit(uint8 Copy_u8ColorMode)
{
	/* Initialize Reset pin */
	GPIO_vInitPortPin(TFTLCD_RESETPIN_PORT,TFTLCD_RESETPIN_PIN,GPIO_OUT);

	/* Initialize TFT A0 Pin */
	GPIO_vInitPortPin(TFTLCD_A0PIN_PORT,TFTLCD_A0PIN_PIN,GPIO_OUT);

	/* Reset pulse */
	TFTLCD_vResetSeq();

	/* Send Sleep out command */
	TFTLCD_vSendCommand(TFTLCD_SLEEP_OUT);
	/* Wait for 150 ms */
	TFTLCD_DELAY_US(150000);

	/* Configure color mode */
	TFTLCD_vSendCommand(TFTLCD_COLOR_MODE);
	TFTLCD_vSendByte(Copy_u8ColorMode);

	/* Display on */
	TFTLCD_vSendCommand(TFTLCD_DISPLAY_ON);
}

/************************************************************************************************************* */

void TFTLCD_vSendCommand(uint8 Copy_u8Command)
{
	uint8 Local_u8RecvData	=	0;

	/* Set A0 pin to low */
	GPIO_vWritePortPin(TFTLCD_A0PIN_PORT,TFTLCD_A0PIN_PIN,GPIO_LOW);

	/* Send command using SPI */
	SPI_xSendRecieveSynch(TFTLCD_SPI_CHANNEL,TDTLCD_SPI_SLAVE_NUM,Copy_u8Command,&Local_u8RecvData);
}

/************************************************************************************************************* */

void TFTLCD_vSendByte(uint8 Copy_u8Data)
{
	uint8 Local_u8RecvData	=	0;

	/* Set A0 pin to high */
	GPIO_vWritePortPin(TFTLCD_A0PIN_PORT,TFTLCD_A0PIN_PIN,GPIO_HIGH);

	/* Send command using SPI */
	SPI_xSendRecieveSynch(TFTLCD_SPI_CHANNEL,TDTLCD_SPI_SLAVE_NUM,Copy_u8Data,&Local_u8RecvData);
}

/************************************************************************************************************* */

void TFTLCD_vDisplayImg(uint16 *Copy_pu16Img)
{
	uint8 u8DataToSend		=	0;
	uint16 Local_u16Index	=	0;
	uint16 TFTLCD_Dimensions=	((TFTLCD_MAX_X - TFTLCD_MAX_X) * (TFTLCD_MAX_Y - TFTLCD_MAX_Y));
	TFTLCD_vReturnHomeCursor();

	TFTLCD_vSendCommand(TFTLCD_RAMWRITE_COMMAND);

	for(Local_u16Index = 0;Local_u16Index < TFTLCD_Dimensions;Local_u16Index++)
	{
		/* Get the higher byte of the index */
		u8DataToSend	=	Copy_pu16Img[Local_u16Index]>>8;
		/* Send the higher byte */
		TFTLCD_vSendByte(u8DataToSend);

		/* Get the lower byte of the index */
		u8DataToSend	=	Copy_pu16Img[Local_u16Index] & 0x00FF;
		/* Send the lower byte */
		TFTLCD_vSendByte(u8DataToSend);
	}
}

/************************************************************************************************************* */

void TFTLCD_vFillColor(uint16 Copy_u16Color)
{
	uint8 u8DataToSend		=	0;
	uint16 Local_u16Index	=	0;
	uint16 TFTLCD_Dimensions=	((TFTLCD_MAX_X - TFTLCD_MIN_X) * (TFTLCD_MAX_Y - TFTLCD_MIN_Y));
	TFTLCD_vReturnHomeCursor();

	TFTLCD_vSendCommand(TFTLCD_RAMWRITE_COMMAND);
	for(Local_u16Index = 0;Local_u16Index < TFTLCD_Dimensions;Local_u16Index++)
	{
		/* Get the higher byte of the index */
		u8DataToSend	=	Copy_u16Color>>8;
		/* Send the higher byte */
		TFTLCD_vSendByte(u8DataToSend);

		/* Get the lower byte of the index */
		u8DataToSend	=	Copy_u16Color & 0x00FF;
		/* Send the lower byte */
		TFTLCD_vSendByte(u8DataToSend);
	}
}

/************************************************************************************************************* */

Error_Status TFTLCD_xDrawPixel(uint16 Copy_u16X, uint16 Copy_u16Y, uint16 Copy_xColor)
{
	Error_Status Local_xErrorStatus	=	E_NOK;

	TFTLCD_xSetCursor(Copy_u16X, Copy_u16Y, Copy_u16X, Copy_u16Y);
	TFTLCD_vSendCommand(TFTLCD_RAMWRITE_COMMAND);
	TFTLCD_vSendByte(Copy_xColor>>8);
	TFTLCD_vSendByte(Copy_xColor&0xFF);

	return Local_xErrorStatus;
}

/************************************************************************************************************* */

Error_Status TFTLCD_xDrawRect(uint16 Copy_u16Min_X,uint16 Copy_u16Max_X,uint16 Copy_u16Min_Y,uint16 Copy_u16Max_Y,uint16 Copy_u16Color)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	uint16 Local_u16Index			=	0;
	uint8 u8DataToSend				=	0;

	Local_xErrorStatus	=	TFTLCD_xSetCursor(Copy_u16Min_X,Copy_u16Max_X,Copy_u16Min_Y,Copy_u16Max_Y);

	uint16 TFTLCD_Dimensions=	((Copy_u16Max_X - Copy_u16Min_X) * (Copy_u16Max_Y - Copy_u16Min_Y));

	TFTLCD_vSendCommand(TFTLCD_RAMWRITE_COMMAND);

	for(Local_u16Index = 0;Local_u16Index < TFTLCD_Dimensions;Local_u16Index++)
	{
		/* Get the higher byte of the index */
		u8DataToSend	=	Copy_u16Color>>8;
		/* Send the higher byte */
		TFTLCD_vSendByte(u8DataToSend);

		/* Get the lower byte of the index */
		u8DataToSend	=	Copy_u16Color & 0x00FF;
		/* Send the lower byte */
		TFTLCD_vSendByte(u8DataToSend);
	}
	return Local_xErrorStatus;
}

/************************************************************************************************************* */

void TFTLCD_xDrawCircle(uint16 Copy_u16X, uint16 Copy_u16Y, uint16 Copy_u16Radius, uint16 Copy_u16Color)
{
	uint16 Local_u16Index = 0;
	uint16 Local_u16Index2 = 0;

	for(Local_u16Index = 0; Local_u16Index < 50; Local_u16Index++)
	{

	}
}

/************************************************************************************************************* */

void TFTLCD_xDrawCharacter(uint8 Copy_u8Char,uint16 Copy_u16X, uint16 Copy_u16Y, uint16 Copy_u16Size, uint16 Copy_u16Color,uint16 Copy_u16BackColor)
{
	if(Copy_u8Char == ' '){return;}
	Copy_u8Char -= '0';

	TFTLCD_xDrawRect( Copy_u16X, Copy_u16Size*7+5,Copy_u16Y ,Copy_u16Size *5+5 ,Copy_u16BackColor);

	for(int i =0 ; i<(7* Copy_u16Size);i++)
	{
		for(int j =0;j<(5*Copy_u16Size);j++){
			if (Char_Array[Copy_u8Char][i/Copy_u16Size] >>(j/Copy_u16Size) &1)
			{
				TFTLCD_xDrawRect (  Copy_u16X+(j),  Copy_u16X+(j)+1,  Copy_u16Y+(i),  Copy_u16Y+(i)+1, Copy_u16Color);
			}
		}
	}
}

/************************************************************************************************************* */

void TFT_vDrawHLine (uint16 Xaxis , uint16 Yaxis , uint16 Copy_u16Length , uint16 Copy_u16Color )
{
	uint8 u8DataToSend = 0;

	for ( ; Copy_u16Length > 0 ; Copy_u16Length-- )
	{
		TFTLCD_xSetCursor(Xaxis,Xaxis,Yaxis,Yaxis);

		TFTLCD_vSendCommand(TFTLCD_RAMWRITE_COMMAND);


		u8DataToSend = Copy_u16Color >> 8;
		TFTLCD_vSendByte(u8DataToSend); // write high byte
		u8DataToSend = Copy_u16Color & 0xFF;
		TFTLCD_vSendByte (u8DataToSend); // write low byte

		Xaxis++;
	}

}

/************************************************************************************************************* */

void TFT_vDrawVLine (uint16 Xaxis , uint16 Yaxis , uint16 Copy_u16Length , uint16 Copy_u16Color )
{
	uint8 u8DataToSend = 0;

	for ( ; Copy_u16Length > 0 ; Copy_u16Length-- )
	{
		TFTLCD_xSetCursor(Xaxis,Xaxis,Yaxis,Yaxis);

		TFTLCD_vSendCommand(TFTLCD_RAMWRITE_COMMAND);

		u8DataToSend = Copy_u16Color >> 8;
		TFTLCD_vSendByte(u8DataToSend); // write high byte
		u8DataToSend = Copy_u16Color & 0xFF;
		TFTLCD_vSendByte (u8DataToSend); // write low byte

		Yaxis++;
	}

}

/************************************************************************************************************* */

void TFTLCD_vDrawText (uint8 *Copy_pu8Text, uint16 Copy_u16X, uint16 Copy_u16Y, uint16 Copy_u16Size,uint16 Copy_u16Color)
{
	while(*Copy_pu8Text != '\0')
	{
		if(*Copy_pu8Text == ' ')
		{
			Copy_u16X-=3;
		}
		else
		{
			Copy_u16X -= 6*Copy_u16Size;
			TFTLCD_xDrawCharacter ( *Copy_pu8Text,   Copy_u16X,  Copy_u16Y,  Copy_u16Size, Copy_u16Color,0xffff);
		}

		Copy_pu8Text++;
	}

}

/************************************************************************************************************* */

Error_Status TFTLCD_xSetCursor(uint16 Copy_u16Min_X,uint16 Copy_u16Max_X,uint16 Copy_u16Min_Y,uint8 Copy_u16Max_Y)
{
	if(TFTLCD_IS_VALID_POSITION(Copy_u16Min_X,Copy_u16Max_X,Copy_u16Min_Y,Copy_u16Max_Y) != E_OK)
	{
		return E_NOK;
	}

	TFTLCD_vSendCommand(TFTLCD_SET_X_ADD_COMMAND);
	/* Send MIN X */
	/* Send high byte */
	TFTLCD_vSendByte(0);
	/* Send low byte */
	TFTLCD_vSendByte(Copy_u16Min_X);

	/* Send MAX X */
	TFTLCD_vSendByte(0);
	TFTLCD_vSendByte(Copy_u16Max_X);

	TFTLCD_vSendCommand(TFTLCD_SET_Y_ADD_COMMAND);
	/* Send MIN Y */

	/* Send high byte */
	TFTLCD_vSendByte(0);
	/* Send low byte */
	TFTLCD_vSendByte(Copy_u16Min_Y);

	/* Send MAX Y */
	TFTLCD_vSendByte(0);
	TFTLCD_vSendByte(Copy_u16Max_Y);

	return E_OK;
}

/************************************************************************************************************* */

void TFTLCD_vReturnHomeCursor(void)
{
	TFTLCD_xSetCursor(TFTLCD_MIN_X,TFTLCD_MAX_X,TFTLCD_MIN_Y,TFTLCD_MAX_Y);
}

/************************************************************************************************************* */
									/* Local functions Definition */
/************************************************************************************************************* */

static void TFTLCD_vResetSeq(void)
{
	GPIO_vWritePortPin(TFTLCD_RESETPIN_PORT,TFTLCD_RESETPIN_PIN,GPIO_HIGH);
	TFTLCD_DELAY_US(100);
	GPIO_vWritePortPin(TFTLCD_RESETPIN_PORT,TFTLCD_RESETPIN_PIN,GPIO_LOW);
	TFTLCD_DELAY_US(1);
	GPIO_vWritePortPin(TFTLCD_RESETPIN_PORT,TFTLCD_RESETPIN_PIN,GPIO_HIGH);
	TFTLCD_DELAY_US(100);
	GPIO_vWritePortPin(TFTLCD_RESETPIN_PORT,TFTLCD_RESETPIN_PIN,GPIO_LOW);
	TFTLCD_DELAY_US(100);
	GPIO_vWritePortPin(TFTLCD_RESETPIN_PORT,TFTLCD_RESETPIN_PIN,GPIO_HIGH);
	TFTLCD_DELAY_US(120000);
}
