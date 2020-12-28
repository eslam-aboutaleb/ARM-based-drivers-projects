/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: BLPrint_config.h			                                         */
/* Version	: V01                                                                */
/* Date		: 28 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef BLPRINT_CONFIG_H_
#define BLPRINT_CONFIG_H_

/* **************************************************************************************** */

#define BL_DEBUG_MESSAGE_EN										ENABLE
#define BLPRINT_DEBUG_BUF_SIZE									80

/* **************************************************************************************** */

ComM_TypeDef hPrintCmdCom = {
		.ComProtocolID	= COM_USART_ID,
		.Channel		= USART_CHANNEL_1,
		.TimeOut		= 5000
};


/* **************************************************************************************** */

#if BL_DEBUG_MESSAGE_EN	==	ENABLE
ComM_TypeDef hPrintDebugCom = {
		.ComProtocolID	= COM_USART_ID,
		.Channel		= USART_CHANNEL_1,
		.TimeOut		= 5000

};

#endif

/* **************************************************************************************** */


#endif
