/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: USART_interface.h		                                             */
/* Version	: V01                                                                */
/* Date		: 26 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

#include "USART_reg.h"



/*******************  USART data types  ********************/
typedef unsigned int								USART_StopBits_t;

/*******************  Stop bits definitions  ********************/
#define USART_ONE_STOP_BIT                        		(uint32)0
#define USART_HALF_STOP_BIT                       		(uint32)1
#define USART_TWO_STOP_BITS                        		(uint32)2
#define USART_ONE_AND_HALF_STOP_BIT                		(uint32)3


/*******************  Flags definitions  ********************/

#define USART_FLAG_CTS                       ((uint16)0x0200)
#define USART_FLAG_LBD                       ((uint16)0x0100)
#define USART_FLAG_TXE                       ((uint16)0x0080)
#define USART_FLAG_TC                        ((uint16)0x0040)
#define USART_FLAG_RXNE                      ((uint16)0x0020)
#define USART_FLAG_IDLE                      ((uint16)0x0010)
#define USART_FLAG_ORE                       ((uint16)0x0008)
#define USART_FLAG_NE                        ((uint16)0x0004)
#define USART_FLAG_FE                        ((uint16)0x0002)
#define USART_FLAG_PE                        ((uint16)0x0001)

/* ************************************************************************************************************ */
/* USART interrupts data type */
typedef enum
{
	USART_INTERRUPT_OFF,
	USART_INTERRUPT_ON,
	USART_INTERRUPT_RX_ON,
	USART_INTERRUPT_RX_OFF,
	USART_INTERRUPT_TX_ON,
	USART_INTERRUPT_TX_OFF,
	USART_INTERRUPT_PE_ON,
	USART_INTERRUPT_PE_OFF,
	USART_INTERRUPT_IDLE_ON,
	USART_INTERRUPT_IDLE_OFF,
	USART_INTERRUPT_TC_ON,
	USART_INTERRUPT_TC_OFF,
	USART_INTERRUPT_ERR_OFF,
	USART_INTERRUPT_ERR_ON
}USART_Int_t;

/* ************************************************************************************************************ */

/* USART modes data type */
typedef enum
{
	USART_TRANSMITER,
	USART_RECIEVER,
	USART_TRANSMITER_RECIEVER
}USART_TXRX_t;

/* ************************************************************************************************************ */

/* USART word length data type */
typedef enum
{
	USART_EIGHT_BITS,
	USART_NINE_BITS
}USART_WordLength_t;

/* ************************************************************************************************************ */

/* USART parity data type */
typedef enum
{
	USART_DISABLE_PARITY,
	USART_EVEN_PARITY,
	USART_ODD_PARITY
}USART_ParityBit_t;

/* ************************************************************************************************************ */

/* USART hardware control flow data type */
typedef enum
{
	USART_HARDWAREFLOWCONTROL_NONE,
	USART_HARDWAREFLOWCONTROL_RTS ,
	USART_HARDWAREFLOWCONTROL_CTS,
	USART_HARDWAREFLOWCONTROL_RTS_CTS
}USART_FlowCntrl_t;

/* ************************************************************************************************************ */

/* Clock data structure for future use */
typedef struct
{
	uint16 USART_Clock;   /*  Specifies whether the USART clock is enabled or disabled. */

	uint16 USART_CPOL;    /*  Specifies the steady state value of the serial clock. */

	uint16 USART_CPHA;    /*  Specifies the clock transition on which the bit capture is made. */

	uint16 USART_LastBit; /*  Specifies whether the clock pulse corresponding to the last transmitted
                               data bit (MSB) has to be output on the SCLK pin in synchronous mode. */
} USART_ClockInitTypeDef;

/* ************************************************************************************************************ */

/* USART Configuration structure */
typedef struct
{
	uint32 USART_BaudRate;            /* This member configures the USART communication baud rate.
                                         The baud rate is computed using the following formula:
                                          - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                          - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

	USART_WordLength_t USART_WordLength;          /* Specifies the number of data bits transmitted or received in a frame. */

	USART_StopBits_t USART_StopBits;  /* Specifies the number of stop bits transmitted. */


	USART_ParityBit_t USART_Parity;              /* Specifies the parity mode.
                                         	 	 When parity is enabled, the computed parity is inserted
                                               	 at the MSB position of the transmitted data (9th bit when
                                               	 the word length is set to 9 data bits; 8th bit when the
                                               	 word length is set to 8 data bits). */

	USART_FlowCntrl_t USART_HardwareFlowControl; /* Specifies wether the hardware flow control mode is enabled
                                           or disabled. */

	USART_TXRX_t USART_TXRX_State;		/* Specifies TX and RX states of selected USART */

	FunctionalState USART_InitialState;	/* Specifies the initial state for the selected USART */

	USART_ClockInitTypeDef USART_ClkSettingsSt; /* Specifies clock settings for selected USART */

} USART_InitTypeDef;


/* ************************************************************************************************************ */
						/*******************  Functions prototypes  ********************/
/* ************************************************************************************************************ */
Error_Status USART_xInit(USART_TypeDef *USARTx , USART_InitTypeDef *USART_CnfgSt);
Error_Status USART_xInitStruct(USART_InitTypeDef *USART_CnfgSt);
Error_Status USART_xConfigTX_RX(USART_TypeDef *USARTx,USART_TXRX_t Copy_xState);
Error_Status USART_xConfigTXE_Interrupt(USART_TypeDef *USARTx, FunctionalState TXE_State);
Error_Status USART_xConfigRXNE_Interrupt(USART_TypeDef *USARTx, FunctionalState RXNE_State);
Error_Status USART_xConfigRXNE_Interrupt(USART_TypeDef *USARTx, FunctionalState RXNE_State);
Error_Status USART_xConfigERR_Interrupt(USART_TypeDef *USARTx, FunctionalState ERR_State);
Error_Status USART_xConfigParityERR_Interrupt(USART_TypeDef *USARTx, FunctionalState PE_State);
Error_Status USART_xConfigState(USART_TypeDef *USARTx , FunctionalState Copy_xState);
Flag_Status USART_GetFlagStatus(USART_TypeDef* USARTx, uint16 USART_FLAG);
void USART_vSendByte(USART_TypeDef *USARTx,uint8 data);
uint8 USART_u8GetByte(USART_TypeDef *USARTx);
Error_Status USART_xSendByteTimeOut(USART_TypeDef *USARTx,uint8 data , uint32 Copy_u32TimeOutMS);
Flag_Status USART_xGetByteTimeOut(USART_TypeDef *USARTx , uint8 *pu8RecvData , uint32 Copy_u32TimeOutMS);
void UART_vWriteBuf(USART_TypeDef *USARTx ,uint8 * pu8MsgBuf);
void UART_vReadBuf(USART_TypeDef *USARTx ,uint8 * pu8RecvBuf);
void UART_vReadBufCustomEnd(USART_TypeDef *USARTx ,uint8 * pu8RecvBuf , uint8 Copy_EndChar);
void USART_vTimeOutIncreament(void);
void USART_vClearTimeOutCounter(void);
uint32 USART_u32GetTimeOut(void);


#endif /* USART_INTERFACE_H_ */
