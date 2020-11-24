/* ******************************************************************** */
/*	Name	:	Eslam Ehab Aboutaleb									*/
/*	Date	:	23/11/2020												*/
/*	File	:	SPI_private.h											*/
/*	Version	:	V01														*/
/* ******************************************************************** */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/* ******************************************************************** */

/* SPI error checkers */
#define SPI_IS_VALID_PRESCALER(PRESCALER)	 (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_256))

#define SPI_IS_VALID_SLAVE(SlaveNum)		(SlaveNum < SPI_N_SLAVES)

/* ******************************************************************** */

/* Local functions prototypes */
static Error_Status SPI_xSetBidMode( SPI_TypeDef* SPIx,SPI_BidMode_t Copy_xMode);
static Error_Status SPI_xEnableCRC( SPI_TypeDef* SPIx,SPI_CRCState_t Copy_xOutPutState);
static Error_Status SPI_xSetCRCPhase( SPI_TypeDef* SPIx,SPI_CRCPhase_t Copy_xCRCState);
static Error_Status SPI_xSetDataFrameSize( SPI_TypeDef* SPIx,SPI_DataFrame_t Copy_xDataLength);
static Error_Status SPI_xSetTransferDir(SPI_TypeDef* SPIx,SPI_TransDir_t Copy_xDataLength);
static Error_Status SPI_xSetSwSlaveMng(SPI_TypeDef* SPIx,SPI_SlaveMng_t Copy_xDataLength);
static Error_Status SPI_xSetFrameFormat(SPI_TypeDef* SPIx,SPI_FrameFormat_t Copy_xFormat);
static Error_Status SPI_xSetBaudRate(SPI_TypeDef* SPIx,uint16 Copy_u16BaudRate);
static Error_Status SPI_xSelectMaster(SPI_TypeDef* SPIx,SPI_MSTR_t Copy_xState);
static Error_Status SPI_xSetClkPolarity(SPI_TypeDef* SPIx,SPI_CPol_t Copy_xClockPolarityState);
static Error_Status SPI_xSetClkPhase(SPI_TypeDef* SPIx,SPI_CPhase_t Copy_xClockPhaseState);

#endif /* SPI_PRIVATE_H_ */

