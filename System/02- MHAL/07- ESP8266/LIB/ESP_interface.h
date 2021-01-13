/*
 * ESP_interface.h
 *
 *  Created on: Jan 4, 2021
 *      Author: Dell
 */

#ifndef ESP_INTERFACE_H_
#define ESP_INTERFACE_H_


#define ESP_TCP_PROTOCOL													"TCP"
#define ESP_UDP_PROTOCOL													"UDP"


Error_Status ESP_xInit(void);
Error_Status ESP_xWifiConnect(uint8* pu8Name , uint8* pu8Password);
Error_Status ESP_xServerConnect(uint8 *pu8Protocol,uint8 *pu8ServerIP , uint8 *pu8PortNum);
Error_Status ESP_xRestart(void);
Error_Status ESP_xSendGetCmd(uint8 *pu8LinkUrl);
Flag_Status ESP_xGetData(uint8 * pu8URL ,uint8 *pu8RecvData);
Flag_Status ESP_xGetDataCustomStart(uint8 * pu8URL ,uint8 Copy_u8StartChar ,uint8 *pu8RecvData);
void ESP_vCloseConnection(void);

#endif /* ESP_INTERFACE_H_ */
