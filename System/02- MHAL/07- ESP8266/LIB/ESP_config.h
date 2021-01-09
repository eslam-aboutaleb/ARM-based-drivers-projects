/*
 * ESP_config.h
 *
 *  Created on: Jan 4, 2021
 *      Author: Dell
 */

#ifndef ESP_CONFIG_H_
#define ESP_CONFIG_H_

#define ESP_RESPONSE_BUF_SIZE									300
#define ESP_LENGH_BUF_SIZE										30
#define ESP_URL_BUF_SIZE										200

#define ESP_DEF_TIMEOUT											10000
#define ESP_WIFI_CON_TIMEOUT									500000

ComM_TypeDef hEspCom = {
		.ComProtocolID	= COM_USART_ID,
		.Channel		= USART_CHANNEL_1,
		.TimeOut		= ESP_DEF_TIMEOUT
};




#endif /* ESP_CONFIG_H_ */
