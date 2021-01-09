/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: USART_private.h		                                             */
/* Version	: V01                                                                */
/* Date		: 26 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

/* ************************************************************************************************************ */

#define USART_FRACTION_MAX										1550

/* ************************************************************************************************************ */
								/* *********** Error checkers *********** */
/* ************************************************************************************************************ */
#define USART_IS_VALID_STOP_BITS(STOPBITS) 		(((STOPBITS) == USART_ONE_STOP_BIT) || \
                                     	 	 	 ((STOPBITS) == USART_HALF_STOP_BIT) || \
												 ((STOPBITS) == USART_TWO_STOP_BITS) || \
												 ((STOPBITS) == USART_ONE_AND_HALF_STOP_BIT))
/* ************************************************************************************************************ */


#define USART_IS_VALID_BAUDRATE(BAUDRATE) 		(((BAUDRATE) > 0) && ((BAUDRATE) < 0x0044AA21))
/* ************************************************************************************************************ */

#define USART_IS_VALID_FLOW_CNTRL(CNTRL)		((CNTRL == USART_HARDWAREFLOWCONTROL_NONE) 		||\
												(CNTRL 	== USART_HARDWAREFLOWCONTROL_RTS) 		||\
												(CNTRL 	== USART_HARDWAREFLOWCONTROL_CTS) 		||\
												(CNTRL 	== USART_HARDWAREFLOWCONTROL_RTS_CTS))
/* ************************************************************************************************************ */

#define USART_IS_FLAG(FLAG) 					(((FLAG) == USART_FLAG_PE) || ((FLAG) == USART_FLAG_TXE) || \
												 ((FLAG) == USART_FLAG_TC) || ((FLAG) == USART_FLAG_RXNE) || \
												 ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_LBD) || \
												 ((FLAG) == USART_FLAG_CTS) || ((FLAG) == USART_FLAG_ORE) || \
												 ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE))


/* ************************************************************************************************************ */
										/* Local functions prototypes */
/* ************************************************************************************************************ */

static Error_Status USART_xConfigWordLength(USART_TypeDef *USARTx, USART_WordLength_t Copy_xLength);
static Error_Status USART_xConfigStopBits(USART_TypeDef *UARTx, USART_StopBits_t Copy_xNStop);
static Error_Status USART_xSetPins(USART_TypeDef *USARTx);
static Error_Status USART_xConfigBaudRate(USART_TypeDef *USARTx	,	uint32 Copy_u32BaudRate);
static Error_Status USART_xConfigFlowControl(USART_TypeDef *USARTx , USART_FlowCntrl_t Copy_xState);
static Error_Status USART_xConfigParity(USART_TypeDef *USARTx , USART_ParityBit_t Copy_xParityState );;

#endif /* USART_PRIVATE_H_ */
