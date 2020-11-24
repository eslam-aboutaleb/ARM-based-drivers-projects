#ifndef SPI_REG_H_
#define SPI_REG_H_

#define SPI1_BASE_ADDRESS								0x40013000
#define SPI2_BASE_ADDRESS								0x40013000
#define SPI3_BASE_ADDRESS								0x40013000

typedef struct
{
  volatile uint16 CR1;
  uint16  RESERVED0;
  volatile uint16 CR2;
  uint16  RESERVED1;
  volatile uint16 SR;
  uint16  RESERVED2;
  volatile uint16 DR;
  uint16  RESERVED3;
  volatile uint16 CRCPR;
  uint16  RESERVED4;
  volatile uint16 RXCRCR;
  uint16  RESERVED5;
  volatile uint16 TXCRCR;
  uint16  RESERVED6;
  volatile uint16 I2SCFGR;
  uint16  RESERVED7;
  volatile uint16 I2SPR;
  uint16  RESERVED8;
} SPI_TypeDef;


#define SPI1									((SPI_TypeDef*)  SPI1_BASE_ADDRESS)
#define SPI2                                    ((SPI_TypeDef*)  SPI1_BASE_ADDRESS)
#define SPI3                                    ((SPI_TypeDef*)  SPI1_BASE_ADDRESS)

#endif	/* SPI_REG_H_ */
