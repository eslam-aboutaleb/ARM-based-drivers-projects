/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: BLPrint_program.c		                                             */
/* Version	: V01                                                                */
/* Date		: 28 - 12 - 2020                                                     */
/* ***************************************************************************** */

#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ComM_interface.h"

#include "BlPrint_interface.h"
#include "BlPrint_config.h"

/* ***************************************************************************************
Function   : BlPrint_vInitCMD
Parameters : void
Return     : void
Job : initializes command port
 **************************************************************************************** */
void BlPrint_vInitCMD(void)
{
	ComM_xInit(&hPrintCmdCom);
}

/* ***************************************************************************************
Function   : BlPrint_vInitDebug
Parameters : void
Return     : void
Job : initializes debug port
 **************************************************************************************** */
void BlPrint_vInitDebug(void)
{
#if BL_DEBUG_MESSAGE_EN	==	ENABLE
	ComM_xInit(&hPrintDebugCom);
#endif
}
/* ***************************************************************************************
Function   : BlPrint_vReadCMD
Parameters : Pointer to buffer type uint8
Return     : void
Job : Receive strings by Command port
 **************************************************************************************** */
void BlPrint_vReadCMD(uint8 *pu8DataBuffer , uint16 Copy_u16DataSize)
{
	hPrintCmdCom.DataRx		= pu8DataBuffer;
	hPrintCmdCom.DataRxSize	= Copy_u16DataSize;

	ComM_xReceiveData(&hPrintCmdCom);
}

/* ***************************************************************************************
Function   : BlPrint_vTransmitCMD
Parameters : Pointer to buffer type uint8 , DataSize from type uint32
Return     : void
Job : Send data by command port
 **************************************************************************************** */
void BlPrint_vTransmitCMD(uint8 *pu8DataBuffer,uint16 Copy_u16DataSize)
{
	hPrintCmdCom.DataTx		= pu8DataBuffer;
	hPrintCmdCom.DataTxSize	= Copy_u16DataSize;

	ComM_xSendData(&hPrintCmdCom);
}

/* ***************************************************************************************
Function   : BlPrint_vPrintDebug
Parameters : Pointer to buffer type uint8
Return     : void
Job : Print function for debugging port
 **************************************************************************************** */
void BlPrint_vPrintDebug(uint8 *Data,...)
{
#if BL_DEBUG_MESSAGE_EN == ENABLE
	uint8 Str[BLPRINT_DEBUG_BUF_SIZE];
	/*Extract the the argument list using VA apis */
	va_list args;
	va_start(args, Data);
	vsprintf(Str, Data,args);
	hPrintDebugCom.DataTxSize	= strlen(Str);
	hPrintDebugCom.DataTx		= Str;
	ComM_xSendData(&hPrintDebugCom);
	va_end(args);
#endif
}
