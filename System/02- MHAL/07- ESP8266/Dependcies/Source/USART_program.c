/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: USART_program.c		                                             */
/* Version	: V01                                                                */
/* Date		: 26 - 12 - 2020                                                     */
/* ***************************************************************************** */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"

#include "SYSTICK_interface.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"
/* ************************************************************************************************************ */

static volatile uint32 USART_TIMEOUT_COUNTER	=	0;

/* ************************************************************************************************************ */
										/* USART functions definitions */
/* ************************************************************************************************************ */

Error_Status USART_xInit(USART_TypeDef *USARTx , USART_InitTypeDef *USART_CnfgSt)
{
	Error_Status Local_xErrorStatus	=	E_NOK;

	/* Set pins of the selected USART */
	Local_xErrorStatus	=	USART_xSetPins(USARTx);
	/* Checking errors */
	ERROR_CHECK(Local_xErrorStatus);

	/* Configure word length of the selected USART */
	Local_xErrorStatus	=	USART_xConfigWordLength(USARTx	,	USART_CnfgSt->USART_WordLength);
	/* Checking errors */
	ERROR_CHECK(Local_xErrorStatus);

	/* Configure number of stop bits of the selected USART */
	Local_xErrorStatus	=	USART_xConfigStopBits(USARTx	,	USART_CnfgSt->USART_StopBits);
	/* Checking errors */
	ERROR_CHECK(Local_xErrorStatus);

	/* Configure sending mode of the selected USART */
	Local_xErrorStatus	=	USART_xConfigTX_RX(USARTx		,	USART_CnfgSt->USART_TXRX_State);
	/* Checking errors */
	ERROR_CHECK(Local_xErrorStatus);

	/* Configure BaudRate of the selected USART */
	Local_xErrorStatus	=	USART_xConfigBaudRate(USARTx	,	USART_CnfgSt->USART_BaudRate);
	/* Checking errors */
	ERROR_CHECK(Local_xErrorStatus);

	/* Configure parity state of the selected USART */
	Local_xErrorStatus	=	USART_xConfigParity(USARTx		,	USART_CnfgSt->USART_Parity);
	/* Checking errors */
	ERROR_CHECK(Local_xErrorStatus);

	/* Configure hardware control flow */
	Local_xErrorStatus	=	USART_xConfigFlowControl(USARTx	,	USART_CnfgSt->USART_HardwareFlowControl);

	/* Configure initial state of the selected USART */
	Local_xErrorStatus	=	USART_xConfigState(USARTx		,	USART_CnfgSt->USART_InitialState);

	/* Return error status */
	return Local_xErrorStatus;
}

/* ************************************************************************************************************ */

Error_Status USART_xInitStruct(USART_InitTypeDef *USART_CnfgSt)
{
	/* Check if is it valid pointer */
	if(USART_CnfgSt == NULL)
	{
		return E_NOK;
	}

	USART_CnfgSt->USART_BaudRate				=	9600;
	USART_CnfgSt->USART_HardwareFlowControl		=	DISABLE;
	USART_CnfgSt->USART_Parity					=	DISABLE;
	USART_CnfgSt->USART_TXRX_State				=	USART_TRANSMITER_RECIEVER;
	USART_CnfgSt->USART_WordLength				=	USART_EIGHT_BITS;
	USART_CnfgSt->USART_StopBits				=	USART_ONE_STOP_BIT;
	USART_CnfgSt->USART_InitialState			=	ENABLE;

	return E_OK;
}

/* ************************************************************************************************************ */

Error_Status USART_xConfigState(USART_TypeDef *USARTx , FunctionalState Copy_xState)
{
	switch(Copy_xState)
	{
	case DISABLE:
		CLEAR_BIT(USARTx->CR1,13);
		break;
	case ENABLE:
		SET_BIT(USARTx->CR1,13);
		break;
	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/* ************************************************************************************************************ */

Error_Status USART_xConfigTX_RX(USART_TypeDef *USARTx , USART_TXRX_t Copy_xState)
{
	/*Clear TX & RX bits*/
	USARTx->CR1 &= ~USART_REG_CR1_RE;
	USARTx->CR1 &= ~USART_REG_CR1_TE;

	switch(Copy_xState)
	{
	case USART_TRANSMITER:
		USARTx->CR1 |= USART_REG_CR1_TE;
		break;

	case USART_RECIEVER:
		USARTx->CR1 |= USART_REG_CR1_RE;
		break;

	case USART_TRANSMITER_RECIEVER:
		USARTx->CR1 |= USART_REG_CR1_RE;
		USARTx->CR1 |= USART_REG_CR1_TE;
		break;

	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/* ************************************************************************************************************ */

Error_Status USART_xConfigTXE_Interrupt(USART_TypeDef *USARTx, FunctionalState TXE_State)
{
	switch(TXE_State)
	{
	case DISABLE:
		USARTx->CR1 &= ~USART_REG_CR1_TXE_INT_EN;
		break;

	case ENABLE:
		USARTx->CR1 |= USART_REG_CR1_TXE_INT_EN;
		break;

	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/* ************************************************************************************************************ */

Error_Status USART_xConfigRXNE_Interrupt(USART_TypeDef *USARTx, FunctionalState RXNE_State)
{
	switch(RXNE_State)
	{
	case DISABLE:
		USARTx->CR1 &= ~USART_REG_CR1_RXNE_INT_EN;
		break;

	case ENABLE:
		USARTx->CR1 |= USART_REG_CR1_RXNE_INT_EN;
		break;

	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/* ************************************************************************************************************ */

Error_Status USART_xConfigERR_Interrupt(USART_TypeDef *USARTx, FunctionalState ERR_State)
{
	switch(ERR_State)
	{
	case DISABLE:
		USARTx->CR3 &= ~USART_REG_CR3_ERR_INT_EN;
		break;

	case ENABLE:
		USARTx->CR3 |= USART_REG_CR3_ERR_INT_EN;
		break;

	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/* ************************************************************************************************************ */

Error_Status USART_xConfigParityERR_Interrupt(USART_TypeDef *USARTx, FunctionalState PE_State)
{
	switch(PE_State)
	{
	case DISABLE:
		USARTx->CR1 &= ~USART_REG_CR1_PEIE_INT_EN;
		break;

	case ENABLE:
		USARTx->CR1 |= USART_REG_CR1_PEIE_INT_EN;
		break;

	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/* ************************************************************************************************************ */

void USART_vSendByte(USART_TypeDef *USARTx,uint8 data)
{
	/*Put data in the first 8 bits of data register*/
	USARTx->DR=data;

	/*Check if TXE bit, Transmit data register empty*/
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==E_NOK)
	{
		asm("NOP");
	}
}

/* ************************************************************************************************************ */

uint8 USART_u8GetByte(USART_TypeDef *USARTx)
{
	/*Check if RXNE bit until it is not empty, Read data register not empty*/
	while(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE)==E_NOK)
	{
		asm("NOP");
	}

	return ((uint8)(USARTx->DR & 0x00FF));
}

/* ************************************************************************************************************ */

Error_Status USART_xSendByteTimeOut(USART_TypeDef *USARTx,uint8 data , uint32 Copy_u32TimeOutMS)
{
	Flag_Status Local_FlagStatus	=	E_OK;
	uint32 u32TimeOut = 0;
	/*Put data in the first 8 bits of data register*/
	USARTx->DR=data;


	/*Check if TXE bit, Transmit data register empty*/
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==E_NOK)
	{
		u32TimeOut++;
		if(u32TimeOut >= Copy_u32TimeOutMS)
		{
			Local_FlagStatus	=	E_NOK;
			break;
		}
	}

	return Local_FlagStatus;
}

/* ************************************************************************************************************ */

Flag_Status USART_xGetByteTimeOut(USART_TypeDef *USARTx , uint8 *pu8RecvData , uint32 Copy_u32TimeOutMS)
{
	Flag_Status Local_FlagStatus	=	E_OK;
	uint32 u32TimeOut				=	0;
	//USART_START_TIMEOUT_TICK();

	/*Check if RXNE bit until it is not empty, Read data register not empty*/
	while(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE)==E_NOK)
	{
		u32TimeOut++;
		if(u32TimeOut >= Copy_u32TimeOutMS)
		{
			Local_FlagStatus	=	E_NOK;
			//USART_STOP_TIMEOUT_TICK();
			//USART_vClearTimeOutCounter();
			*pu8RecvData = '\0';
			return Local_FlagStatus;
		}
	}

	*pu8RecvData	=	(uint8)(USARTx->DR & 0x00FF);

	//USART_STOP_TIMEOUT_TICK();
	//USART_vClearTimeOutCounter();

	return Local_FlagStatus;
}

/* ************************************************************************************************************ */

void UART_vWriteBuf(USART_TypeDef *USARTx ,uint8 * pu8MsgBuf)
{
	while(*pu8MsgBuf!='\0')
	{
		USART_vSendByte(USARTx,*pu8MsgBuf);
		pu8MsgBuf++;
	}
	USART_vSendByte(USARTx,'\0');
}

/* ************************************************************************************************************ */

void UART_vReadBuf(USART_TypeDef *USARTx ,uint8 * pu8RecvBuf)
{
	/*temporary variable as a buffer*/
	uint8 data;
	while(1)
	{
		data=USART_u8GetByte(USARTx);
		/*assign data to the Buffer*/
		*pu8RecvBuf	=	data;
		/*move to next address*/
		if (data=='\0' || data=='\r' || data=='\n')
		{
			break;
		}
		pu8RecvBuf++;
	}
}

/* ************************************************************************************************************ */

void UART_vReadBufCustomEnd(USART_TypeDef *USARTx ,uint8 * pu8RecvBuf , uint8 Copy_EndChar)
{
	/*temporary variable as a buffer*/
	uint8 data;
	while(1)
	{
		data=USART_u8GetByte(USARTx);
		/*assign data to the Buffer*/
		*pu8RecvBuf	=	data;
		/*move to next address*/
		if (data == Copy_EndChar)
		{
			break;
		}
		pu8RecvBuf++;
	}
}

/* ************************************************************************************************************ */

Flag_Status USART_GetFlagStatus(USART_TypeDef* USARTx, uint16 USART_FLAG)
{
	ERROR_CHECK(USART_IS_FLAG(USART_FLAG));

	Flag_Status Local_xFlagStatus = E_NOK;

	if ((USARTx->SR & USART_FLAG) != (uint16)E_NOK)
	{
		Local_xFlagStatus = E_OK;
	}
	else
	{
		Local_xFlagStatus = E_NOK;
	}
	return Local_xFlagStatus;
}

/* ************************************************************************************************************ */

void USART_vTimeOutIncreament(void)
{
	USART_TIMEOUT_COUNTER++;
}

/* ************************************************************************************************************ */

void USART_vClearTimeOutCounter(void)
{
	USART_TIMEOUT_COUNTER	=	0;
}

/* ************************************************************************************************************ */

uint32 USART_u32GetTimeOut(void)
{
	return USART_TIMEOUT_COUNTER;
}

/* ************************************************************************************************************ */
										/* USART Local functions definitions */
/* ************************************************************************************************************ */

static Error_Status USART_xConfigBaudRate(USART_TypeDef *USARTx	,	uint32 Copy_u32BaudRate)
{
	Error_Status Local_xErrorStatus	=	0;
	uint32 Local_u32PCLK			=	0;
	uint32 Local_u32Mantissa		=	0;
	uint32 Local_u32Fraction		=	0;

	/* Check if is it valid baudrate */
	Local_xErrorStatus	=	USART_IS_VALID_BAUDRATE(Copy_u32BaudRate);
	ERROR_CHECK(Local_xErrorStatus);

	/* Get clock frequency of the selected USART clock */
	if(USARTx == USART1)
	{
		Local_xErrorStatus	=	RCC_xGetAPB2_Freq(&Local_u32PCLK);
	}

	else if(USARTx == USART2)
	{
		Local_xErrorStatus	=	RCC_xGetAPB1_Freq(&Local_u32PCLK);
	}
	else if(USARTx == USART3)
	{
		Local_xErrorStatus	=	RCC_xGetAPB1_Freq(&Local_u32PCLK);
	}
	else
	{
		Local_xErrorStatus	= E_NOK;
	}

	ERROR_CHECK(Local_xErrorStatus);


	Local_u32Mantissa	=	(Local_u32PCLK) / ( 16 * Copy_u32BaudRate);
	Local_u32Fraction	=	(((Local_u32PCLK * 100 ) / ( 16 * Copy_u32BaudRate)) % 100 ) * 16;

	if(Local_u32Fraction > USART_FRACTION_MAX)
	{
		Local_u32Mantissa	+=	1;
		Local_u32Fraction	=	0;
	}

	/* Assign the baudrate value */
	USARTx->BRR	=	(Local_u32Mantissa << 4 )	| (Local_u32Fraction / 100 );

	return Local_xErrorStatus;
}

/* ************************************************************************************************************ */

static Error_Status USART_xConfigWordLength(USART_TypeDef *USARTx, USART_WordLength_t Copy_xLength)
{
	switch(Copy_xLength)
	{
	case USART_NINE_BITS:
		USARTx->CR1 |= USART_REG_CR1_UART_WL; /* 9data bits */
		break;

	case USART_EIGHT_BITS:
		USARTx->CR1 &= ~USART_REG_CR1_UART_WL; /* 8 data bits */
		break;

	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/* ************************************************************************************************************ */

static Error_Status USART_xConfigStopBits(USART_TypeDef *UARTx, USART_StopBits_t Copy_xNStop)
{
	/* Check if is it valid number of stop bits */
	ERROR_CHECK(USART_IS_VALID_STOP_BITS(Copy_xNStop));

	/*clear the 12th and 13 th bits */
	UARTx->CR2 &= ~( 0x3 << USART_REG_CR2_STOP_BITS);

	UARTx->CR2 |= ( Copy_xNStop<< USART_REG_CR2_STOP_BITS);

	return E_OK;
}

/* ************************************************************************************************************ */

static Error_Status USART_xConfigParity(USART_TypeDef *USARTx , USART_ParityBit_t Copy_xParityState )
{
	switch(Copy_xParityState)
	{
	case USART_DISABLE_PARITY:
		CLEAR_BIT(USARTx->CR1,10);
		break;
	case USART_ODD_PARITY:
		SET_BIT(USARTx->CR1,10);
		SET_BIT(USARTx->CR1,9);
		break;
	case USART_EVEN_PARITY:
		SET_BIT(USARTx->CR1,10);
		CLEAR_BIT(USARTx->CR1,9);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ************************************************************************************************************ */

static Error_Status USART_xSetPins(USART_TypeDef *USARTx)
{
	if(USARTx == USART1)
	{
		GPIO_vInitPortPin(USART1_Map[USART_TX].USART_Port,
				USART1_Map[USART_TX].USART_Pin,
				GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_2MHZ);

		GPIO_vInitPortPin(USART1_Map[USART_RX].USART_Port,
				USART1_Map[USART_RX].USART_Pin,
				GPIO_PIN_INPUT_FLOATING_MODE);
	}

	else if(USARTx == USART2)
	{
		GPIO_vInitPortPin(USART2_Map[USART_TX].USART_Port,
				USART2_Map[USART_TX].USART_Pin,
				GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_2MHZ);

		GPIO_vInitPortPin(USART2_Map[USART_RX].USART_Port,
				USART2_Map[USART_RX].USART_Pin,
				GPIO_PIN_INPUT_FLOATING_MODE);
	}
	else if(USARTx == USART3)
	{
		GPIO_vInitPortPin(USART3_Map[USART_TX].USART_Port,
				USART3_Map[USART_TX].USART_Pin,
				GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_2MHZ);

		GPIO_vInitPortPin(USART3_Map[USART_RX].USART_Port,
				USART3_Map[USART_RX].USART_Pin,
				GPIO_PIN_INPUT_FLOATING_MODE);
	}
	else
	{
		return E_NOK;
	}


	return E_OK;
}

/* ************************************************************************************************************ */

static Error_Status USART_xConfigFlowControl(USART_TypeDef *USARTx , USART_FlowCntrl_t Copy_xState)
{
	ERROR_CHECK(USART_IS_VALID_FLOW_CNTRL(Copy_xState) );

	USARTx->CR3 |= ((Copy_xState & 0x0300) << 8);
	return E_OK;
}
