/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: TFTLCD_interface.h		                                         */
/* Version	: V01                                                                */
/* Date		: 15 - 11 - 2020                                                     */
/* ***************************************************************************** */

#ifndef TFTLCD_INTERFACE_H_
#define TFTLCD_INTERFACE_H_

/************************************************************************************************************* */

/* TFT colors */
#define TFTLCD_RGB565_COLOR											0x05

/************************************************************************************************************* */
											/* functions prototypes */
/************************************************************************************************************* */

void TFTLCD_vInit(uint8 Copy_u8ColorMode);
/************************************************************************************************************* */

void TFTLCD_vSendByte(uint8 Copy_u8Data);
/************************************************************************************************************* */

Error_Status TFTLCD_xSetCursor(uint16 Copy_u16Min_X,uint16 Copy_u16Max_X,uint16 Copy_u16Min_Y,uint8 Copy_u16Max_Y);
/************************************************************************************************************* */

void TFTLCD_vReturnHomeCursor(void);
/************************************************************************************************************* */

void TFTLCD_vFillColor(uint16 Copy_u16Color);
/************************************************************************************************************* */

Error_Status TFTLCD_xDrawPixel(uint16 Copy_u16X, uint16 Copy_u16Y, uint16 Copy_xColor);
/************************************************************************************************************* */

Error_Status TFTLCD_xDrawRect(uint16 Copy_u16Min_X,uint16 Copy_u16Max_X,uint16 Copy_u16Min_Y,uint16 Copy_u16Max_Y,uint16 Copy_u16Color);
/************************************************************************************************************* */

void TFTLCD_xDrawCircle(uint16 Copy_u16X, uint16 Copy_u16Y, uint16 Copy_u16Radius, uint16 Copy_u16Color);
/************************************************************************************************************* */

void TFTLCD_xDrawCharacter(uint8 Copy_u8Char,uint16 Copy_u16X, uint16 Copy_u16Y, uint16 Copy_u16Size, uint16 Copy_u16Color,uint16 Copy_u16BackColor);
/************************************************************************************************************* */

void TFTLCD_vDrawText (uint8 *Copy_pu8Text, uint16 Copy_u16X, uint16 Copy_u16Y, uint16 Copy_u16Size,uint16 Copy_u16Color);
/************************************************************************************************************* */

void TFT_voidPrintChar(sint8 copy_s8Char , uint16 copy_u16X , uint16 copy_u16Y, uint16 copy_u16Size , uint16 copy_u16Color , uint16 copy_u16BackColor);
/************************************************************************************************************* */

void TFT_vDrawVLine (uint16 Xaxis , uint16 Yaxis , uint16 Copy_u16Length , uint16 Copy_u16Color );
/************************************************************************************************************* */

void TFT_vDrawHLine (uint16 Xaxis , uint16 Yaxis , uint16 Copy_u16Length , uint16 Copy_u16Color );
/************************************************************************************************************* */

void TFTLCD_vSendCommand(uint8 Copy_u8Command);
/************************************************************************************************************* */


#endif /* TFTLCD_INTERFACE_H_ */
