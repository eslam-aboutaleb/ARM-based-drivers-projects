/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: I2C_reg.h		    	                                             */
/* Version	: V01                                                                */
/* Date		: 18 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef I2C_REG_H_
#define I2C_REG_H_
/************************************************************************************************************* */

#define SPI1_ADDRESS_BASE											0x40005400
#define SPI2_ADDRESS_BASE											0x40005800
/************************************************************************************************************* */

typedef struct
{
  volatile uint16 CR1;
  uint16  RESERVED0;
  volatile uint16 CR2;
  uint16  RESERVED1;
  volatile uint16 OAR1;
  uint16  RESERVED2;
  volatile uint16 OAR2;
  uint16  RESERVED3;
  volatile uint16 DR;
  uint16  RESERVED4;
  volatile uint16 SR1;
  uint16  RESERVED5;
  volatile uint16 SR2;
  uint16  RESERVED6;
  volatile uint16 CCR;
  uint16  RESERVED7;
  volatile uint16 TRISE;
  uint16  RESERVED8;
} I2C_TypeDef;

/************************************************************************************************************* */

#define I2C1										(( I2C_TypeDef* ) SPI1_ADDRESS_BASE)
#define I2C2										(( I2C_TypeDef* ) SPI2_ADDRESS_BASE)

#endif /* I2C_REG_H_ */
