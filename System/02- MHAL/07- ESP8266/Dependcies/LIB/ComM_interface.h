/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: ComM_interface.h		                                             */
/* Version	: V01                                                                */
/* Date		: 28 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef COMM_INTERFACE_H_
#define COMM_INTERFACE_H_
/* **************************************************************************************** */
/* Data types */
/* **************************************************************************************** */

typedef unsigned char					ComID_t;
typedef unsigned char					ComCh_t;
typedef unsigned char					ComData_t;
typedef unsigned int					ComSize_t;
/* **************************************************************************************** */
/* Valid communication protocols */
/* **************************************************************************************** */

#define COM_USART_ID					0
#define COM_SPI_ID						1
#define COM_I2C_ID						2

/* **************************************************************************************** */
/* Valid USART channel */
/* **************************************************************************************** */

#define USART_CHANNEL_1										1
#define USART_CHANNEL_2										2
#define USART_CHANNEL_3										3

/* **************************************************************************************** */

/* Function like macro to return the selected channel */
#define USART_CHOOSE_CHANNEL(NUM)							((NUM == USART_CHANNEL_1)? USART1	:\
															(NUM == USART_CHANNEL_2)?  USART2	:\
															(NUM == USART_CHANNEL_3)?  USART3	: NULL)

/* **************************************************************************************** */

typedef struct{
	ComID_t		ComProtocolID;
	ComCh_t		Channel;
	ComData_t	*DataTx;
	ComSize_t	DataTxSize;
	ComData_t	*DataRx;
	ComSize_t	DataRxSize;
	uint32		TimeOut;
}ComM_TypeDef;

/* **************************************************************************************** */
							/* Functions prototypes */
/* **************************************************************************************** */

Error_Status ComM_xSendData(ComM_TypeDef *Com_CnfgSt);

Error_Status ComM_xReceiveData(ComM_TypeDef *Com_CnfgSt);

Error_Status ComM_xInit(ComM_TypeDef *Com_CnfgSt);

Error_Status ComM_xReceiveDataTillCharacter(ComM_TypeDef *Com_CnfgSt,uint8 LimitCharacter);

Error_Status ComM_xSendDataTillCharacter(ComM_TypeDef *Com_CnfgSt,uint8 LimitCharacter);
Error_Status ComM_xSendDataTillCharacterWithDelay(ComM_TypeDef *Com_CnfgSt,uint8 LimitCharacter , uint32 u32ByteDelay);
Error_Status ComM_xReceiveDatawithStartEnd(ComM_TypeDef *Com_CnfgSt,uint8 StartChar,uint8 LimitCharacter);


#endif
