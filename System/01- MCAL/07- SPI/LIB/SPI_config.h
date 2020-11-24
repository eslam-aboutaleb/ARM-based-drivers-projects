/* ******************************************************************** */
/*	Name	:	Eslam Ehab Aboutaleb									*/
/*	Date	:	23/11/2020												*/
/*	File	:	SPI_config.h											*/
/*	Version	:	V01														*/
/* ******************************************************************** */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/* ******************************************************************** */
/* Configure number of slaves */
#define SPI_N_SLAVES												(1)
static uint8 SPI_SlavesNum	=	SPI_N_SLAVES;
/* ******************************************************************** */
#define SPI_FRAME_SIZE_DATA_TYPE									uint8
/* ******************************************************************** */
#define SPI_CLK_PORT												GPIOA
#define SPI_CLK_PIN													GPIO_PIN_5

#define SPI_MISO_PORT												GPIOA
#define SPI_MISO_PIN												GPIO_PIN_6

#define SPI_MOSI_PORT												GPIOA
#define SPI_MOSI_PIN												GPIO_PIN_7

/* ******************************************************************** */
typedef struct{
	GPIO_pPORTx SlavePort;
	uint8		SlavePinNum;
}SPI_Map;
/* ******************************************************************** */

SPI_Map SPI_MapCnfg[SPI_N_SLAVES] ={
		{GPIOA,GPIO_PIN_0}
};

/* ******************************************************************** */

#endif /* SPI_CONFIG_H_ */
