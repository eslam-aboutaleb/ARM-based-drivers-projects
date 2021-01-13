/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: USART_config.c		                                             */
/* Version	: V01                                                                */
/* Date		: 26 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

/* ************************************************************************************************************ */
										/* USART Pins configurations */
/* ************************************************************************************************************ */

#define USART_TX													0
#define USART_RX													1

/* ************************************************************************************************************ */

#define USART1_PORT_TX												GPIOA
#define USART1_PIN_TX												GPIO_PIN_9
#define USART1_PORT_RX												GPIOA
#define USART1_PIN_RX												GPIO_PIN_10

/* ************************************************************************************************************ */

#define USART2_PORT_TX												GPIOB
#define USART2_PIN_TX												GPIO_PIN_10
#define USART2_PORT_RX												GPIOB
#define USART2_PIN_RX												GPIO_PIN_11

/* ************************************************************************************************************ */

#define USART3_PORT_TX												GPIOA
#define USART3_PIN_TX												GPIO_PIN_2
#define USART3_PORT_RX												GPIOA
#define USART3_PIN_RX												GPIO_PIN_3

/* ************************************************************************************************************ */

typedef struct{
	GPIO_Port_t USART_Port;
	GPIO_Pin_t	USART_Pin;
}USART_Map_t;

/* ************************************************************************************************************ */

USART_Map_t USART1_Map[2]= {
		{USART1_PORT_TX	,	USART1_PIN_TX},
		{USART1_PORT_RX	,	USART1_PIN_RX}
};

/* ************************************************************************************************************ */

USART_Map_t USART2_Map[2]= {
		{USART2_PORT_TX	,	USART2_PIN_TX},
		{USART2_PORT_RX	,	USART2_PIN_RX}
};

/* ************************************************************************************************************ */

USART_Map_t USART3_Map[2]= {
		{USART3_PORT_TX	,	USART3_PIN_TX},
		{USART3_PORT_RX	,	USART3_PIN_RX}
};

/* ************************************************************************************************************ */
										/* Timer requirements */
/* ************************************************************************************************************ */


#define USART_USED_TIMER										TIMER1
#define USART_TICK_MS											1

#endif
