#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ComM_interface.h"
#include "Util_String_interface.h"

#include "ESP_interface.h"
#include "ESP_config.h"
#include "ESP_private.h"

Error_Status ESP_xInit(void)
{
	Error_Status Local_xErrorStatus	=	E_NOK;

	/* Initialize communication */
	Local_xErrorStatus		=	ComM_xInit(&hEspCom);

	Local_xErrorStatus		=	E_NOK;

	/* Restart */
/*	while(Local_xErrorStatus != E_OK)
	{
		hEspCom.TimeOut = 300000;
		Local_xErrorStatus	=	ESP_xSendCmd(ESP_RESTART);
		Local_xErrorStatus	=	ESP_xValidateCmd((uint8*)"ready");
	}
*/
	Local_xErrorStatus		=	E_NOK;

	/* Stop ECHO */
	/*while(Local_xErrorStatus != E_OK)
	{
		Local_xErrorStatus	=	ESP_xSendCmd(ESP_DISABLE_ECHO);
		Local_xErrorStatus	=	ESP_xValidateCmd("OK");
	}*/

	Local_xErrorStatus		=	E_NOK;

	/* Set Station Mode */
	while(Local_xErrorStatus != E_OK)
	{
		Local_xErrorStatus	=	ESP_xSendCmd(ESP_MODE_STATION);
		Local_xErrorStatus	=	ESP_xValidateCmd("OK");
	}

	return Local_xErrorStatus;
}

Error_Status ESP_xRestart(void)
{
	Error_Status Local_xErrorStatus	=	E_OK;
	hEspCom.TimeOut = 200000;
	ESP_xSendCmd(ESP_RESTART);
	return Local_xErrorStatus;
}

Error_Status ESP_xWifiConnect(uint8* pu8Name , uint8* pu8Password)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	uint8 Local_u8WifiCmd[100] 		=	{0};

	hEspCom.TimeOut = ESP_WIFI_CON_TIMEOUT;
	sprintf((char*) Local_u8WifiCmd, ESP_CONNECT_AP_DEF,(char*) pu8Name,(char*) pu8Password);

	/* Send the WIFI SSD and password */
	while(Local_xErrorStatus != E_OK)
	{
		Local_xErrorStatus	=	ESP_xSendCmd(Local_u8WifiCmd);
		Local_xErrorStatus	=	ESP_xValidateCmd((uint8*)"CONNECTED",(uint8*)"IP");
	}

	return Local_xErrorStatus;
}

Error_Status ESP_xServerConnect(uint8 *pu8Protocol,uint8 *pu8ServerIP , uint8 *pu8PortNum)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	uint8 Local_U8ConServer[100] 	= 	{0};
	hEspCom.TimeOut = 200000;
	sprintf((char*) Local_U8ConServer, ESP_CONNECT_SERVER ,(char*)pu8Protocol ,(char*) pu8ServerIP ,(char*) pu8PortNum );

	while(Local_xErrorStatus != E_OK)
	{
		Local_xErrorStatus	=	ESP_xSendCmd(Local_U8ConServer);
		Local_xErrorStatus	=	ESP_xValidateCmd((uint8*)"CONNECT");
	}

	return Local_xErrorStatus;
}


Flag_Status ESP_xGetData(uint8 * pu8URL ,uint8 *pu8RecvData)
{
	uint8 Local_u8SendLength[ESP_LENGH_BUF_SIZE]	=	{0};
	uint8 Local_u8SendURL[ESP_URL_BUF_SIZE]			=	{0};
	uint16 Local_u16Length							=	0;
	Flag_Status Local_FlagStatus					=	E_NOK;

	hEspCom.DataRx 									=	pu8RecvData;
	hEspCom.TimeOut									=	500000;

	sprintf((uint8*)Local_u8SendURL , "GET %s\r\n",(uint8*)pu8URL);

	Local_u16Length = UtilString_u16countStr(Local_u8SendURL);

	sprintf((uint8*)Local_u8SendLength , "AT+CIPSEND=%d\r\n",Local_u16Length );

	hEspCom.TimeOut = 0;
	while(Local_FlagStatus != E_OK)
	{
		Local_FlagStatus	=	ESP_xSendCmd(Local_u8SendLength);
		Local_FlagStatus	=	ESP_xValidateCmd((uint8*)"OK");

	}

	ESP_xSendCmd(Local_u8SendURL);

	Local_FlagStatus	=	ComM_xReceiveDataTillCharacter(&hEspCom,'\0');

	return Local_FlagStatus;
}


static Error_Status ESP_xSendCmd(uint8 *pu8DataBuffer)
{
	Error_Status Local_xErrorStatus	=	E_OK;
	hEspCom.DataTx		= pu8DataBuffer;

	Local_xErrorStatus	=	ComM_xSendDataTillCharacter(&hEspCom , '\0');

	return Local_xErrorStatus;
}

static Flag_Status ESP_xValidateCmd(uint8* pu8Search,...)
{
	Flag_Status Local_FlagStatus				=	E_OK;
	uint8 u8ResponseBuf[ESP_RESPONSE_BUF_SIZE]	=	{0};
	uint8 *Local_pu8ptr 						=	NULL;
	hEspCom.DataRx 								=	u8ResponseBuf;

	va_list args;
	va_start(args, pu8Search);
	vsprintf((uint8*)u8ResponseBuf, (uint8*)pu8Search,args);

	Local_FlagStatus	=	ComM_xReceiveDataTillCharacter(&hEspCom,'\0');
	Local_pu8ptr = strtok((uint8*)u8ResponseBuf,' ');

	while(Local_pu8ptr != NULL)
	{
		Local_FlagStatus	=	UtilString_xFindWord(Local_pu8ptr ,u8ResponseBuf);
		Local_pu8ptr = strtok((uint8*)u8ResponseBuf,' ');
		if(Local_FlagStatus == E_OK)
		{
			break;
		}
	}

	va_end(args);

	hEspCom.TimeOut = ESP_DEF_TIMEOUT;

	return Local_FlagStatus;
}
