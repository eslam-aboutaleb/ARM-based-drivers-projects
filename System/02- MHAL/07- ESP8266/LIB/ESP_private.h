/*
 * ESP_private.h
 *
 *  Created on: Jan 4, 2021
 *      Author: Dell
 */

#ifndef ESP_PRIVATE_H_
#define ESP_PRIVATE_H_


#define ESP_RESTART									(uint8*) "AT+RST\r\n"
#define ESP_FACTORY_RESET							(uint8*) "AT+RESTORE\r\n"
#define ESP_SLEEP									(uint8*) "AT+SLEEP\r\n"
#define ESP_DISABLE_ECHO							(uint8*) "ATE0\r\n"
#define ESP_ENABLE_ECHO								(uint8*) "ATE1\r\n"
#define ESP_MODE_STATION							(uint8*) "AT+CWMODE=1\r\n"
#define ESP_MODE_SOFTAP								(uint8*) "AT+CWMODE=2\r\n"
#define ESP_MODE_SOFTAP_STATION						(uint8*) "AT+CWMODE=3\r\n"
#define ESP_GET_CUR_MODE							(uint8*) "AT+CWMODE_CUR?\r\n"
#define ESP_CONNECT_AP								(uint8*) "AT+CWJAP=\"%s\",\"%s\"\r\n"
#define ESP_CONNECT_AP_DEF							(char*)  "AT+CWJAP_DEF=\"%s\",\"%s\"\r\n"
#define ESP_CONNECT_AP_AUTO_ON						(uint8*) "AT+CWAUTOCONN=1\r\n"
#define ESP_CONNECT_AP_AUTO_OFF						(uint8*) "AT+CWAUTOCONN=0\r\n"
#define ESP_SET_IP_ADDRESS							(uint8*) "AT+CIPSTA"
#define ESP_SET_DEF_IP_ADDRESS						(uint8*) "AT+CIPSTA_DEF"
#define ESP_ENABLE_MUL_CONNECTIONS					(uint8*) "AT+CIPMUX=1\r\n"
#define ESP_DISABLE_MUL_CONNECTIONS					(uint8*) "AT+CIPMUX=0\r\n"
#define ESP_CONNECT_SERVER							(char*)	 "AT+CIPSTART=\"%s\",\"%s\",%s\r\n"
#define ESP_DISCONNECT_SERVER						(uint8*) "AT+CIPCLOSE\r\n"

static Error_Status ESP_xSendCmd(uint8 *pu8DataBuffer);
static Error_Status ESP_xSendCmdWithDelay(uint8 *pu8DataBuffer , uint32 u32ByteDelay);
//static Flag_Status ESP_xValidateCmd(uint8* pu8Search,...);
static Flag_Status ESP_xValidateCmd(uint8* pu8Search);

#endif /* ESP_PRIVATE_H_ */
