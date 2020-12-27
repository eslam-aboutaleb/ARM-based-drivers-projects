/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: USART_reg.h			                                             */
/* Version	: V01                                                                */
/* Date		: 26 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef USART_REG_H_
#define USART_REG_H_

#define USART1_BASE_ADDRESS											(0x40013800)
#define USART2_BASE_ADDRESS											(0x40004400)
#define USART3_BASE_ADDRESS											(0x40004800)

typedef struct
{
  volatile uint16 SR;
  uint16  RESERVED0;
  volatile uint16 DR;
  uint16  RESERVED1;
  volatile uint16 BRR;
  uint16  RESERVED2;
  volatile uint16 CR1;
  uint16  RESERVED3;
  volatile uint16 CR2;
  uint16  RESERVED4;
  volatile uint16 CR3;
  uint16  RESERVED5;
  volatile uint16 GTPR;
  uint16  RESERVED6;
} USART_TypeDef;


#define USART1												((USART_TypeDef *)	USART1_BASE_ADDRESS		)
#define USART2												((USART_TypeDef *)	USART2_BASE_ADDRESS		)
#define USART3	     									  	((USART_TypeDef *)	USART3_BASE_ADDRESS		)



/*******************  Bit definition for USART_CR1 register  ********************/
#define USART_REG_CR1_OVER8               			( (uint16)( 1 << 15 ) )

#define USART_REG_CR1_USART_EN                    	( (uint16)( 1 << 13 ) )

#define USART_REG_CR1_UART_WL                 		( (uint16)( 1 << 12	) )

#define USART_REG_CR1_TXE_INT_EN                 	( (uint16)( 1 << 7	) )
#define USART_REG_CR1_TCIE_INT_EN                	( (uint16)( 1 << 6	) )
#define USART_REG_CR1_RXNE_INT_EN                	( (uint16)( 1 << 5	) )
#define USART_REG_CR1_PEIE_INT_EN                	( (uint16)( 1 << 8	) )
#define USART_REG_CR1_TE                  			( (uint16)( 1 << 3	) )
#define USART_REG_CR1_RE                  			( (uint16)( 1 << 2	) )

/*******************  Bit definition for USART_CR2 register  ********************/
#define USART_REG_CR2_STOP_BITS                 	12

/*******************  Bit definition for USART_CR3 register  ********************/
#define USART_REG_CR3_ERR_INT_EN                  ( (uint16)( 1 << 0) )

#define UART_STOPBITS_1        						( (uint16)0x00 )
#define UART_STOPBITS_HALF     						( (uint16)0x01 )
#define UART_STOPBITS_2        						( (uint16)0x02 )
#define UART_STOPBITS_ONENHALF 						( (uint16)0x03 )

#define UART_PARITY_NONE                  			( (uint16)0x0000)
#define UART_HWCONTROL_NONE               			( (uint16)0x0000)

#define UART_MODE_TX_RX                     		( (uint16)(USART_REG_CR1_TE |USART_REG_CR1_RE))

#define UART_MODE_TX                      			( (uint16)(USART_REG_CR1_TE) )


#endif /* USART_REG_H_ */
