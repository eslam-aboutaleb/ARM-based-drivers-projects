/* ******************************************************************** */
/*	Name	:	Eslam Ehab Aboutaleb									*/
/*	Date	:	23/11/2020												*/
/*	File	:	SPI_interface.h											*/
/*	Version	:	V01														*/
/* ******************************************************************** */

#ifndef SPI_INTERFACE_H
#define	SPI_INTERFACE_H

/* ******************************************************************** */
#include "SPI_Reg.h"
/* ******************************************************************** */

typedef unsigned char								SPI_BidMode_t;
typedef unsigned char								SPI_CRCState_t;
typedef unsigned char								SPI_CRCPhase_t;
typedef unsigned char								SPI_DataFrame_t;
typedef unsigned char								SPI_TransDir_t;
typedef unsigned char								SPI_SlaveMng_t;
typedef unsigned char								SPI_SlavePinState_t;
typedef unsigned char								SPI_FrameFormat_t;
typedef unsigned char								SPI_State_t;
typedef unsigned char								SPI_MSTR_t;
typedef unsigned char								SPI_CPol_t;
typedef unsigned char								SPI_CPhase_t;
typedef unsigned char								SPI_Data_t;
typedef unsigned char								SPI_SlaveNum_t;

/* ******************************************************************** */

/* SPI Baud rate Pre-scalers */
#define SPI_BaudRatePrescaler_2										((uint16)0x0000)
#define SPI_BaudRatePrescaler_4										((uint16)0x0008)
#define SPI_BaudRatePrescaler_8										((uint16)0x0010)
#define SPI_BaudRatePrescaler_16 									((uint16)0x0018)
#define SPI_BaudRatePrescaler_32 									((uint16)0x0020)
#define SPI_BaudRatePrescaler_64 									((uint16)0x0028)
#define SPI_BaudRatePrescaler_128									((uint16)0x0030)
#define SPI_BaudRatePrescaler_256									((uint16)0x0038)

/* ******************************************************************** */

/* Direction modes */
#define SPI_TWO_LINES_UNIDIR_MODE									(0)
#define SPI_ONE_LINE_BIDIR_MODE_DISABLE_OUTPUT						(1)
#define SPI_ONE_LINE_BIDIR_MODE_ENAABLE_OUTPUT						(2)

/* ******************************************************************** */

/* SPI CRC states */
#define SPI_DISABLE_CRC												(0)
#define SPI_ENABLE_CRC												(1)

/* ******************************************************************** */

/* SPI CRC Phases */
#define SPI_NO_CRC_PHASE											(0)
#define SPI_CRC_PHASE												(1)

/* ******************************************************************** */

/* SPI Size of frame */
#define SPI_8_BIT_DATA_FRAME										(0)
#define SPI_16_BIT_DATA_FRAME										(1)

/* ******************************************************************** */

/* SPI data transfer modes */
#define SPI_FULL_DUPLEX												(0)
#define SPI_SIMPLEX_RECV											(1)

/* ******************************************************************** */

/* SPI Receiving states */
#define SPI_DISABLE_SLAVE_MNG										(0)
#define SPI_ENABLE_SLAVE_MNG										(1)

/* ******************************************************************** */

/* SPI slave select states */
#define SPI_SSI_LOW													(0)
#define SPI_SSI_HIGH												(1)

/* ******************************************************************** */

/* SPI Frame format */
#define	SPI_LSB_FIRST												(0)
#define	SPI_MSB_FIRST												(1)

/* ******************************************************************** */

/* SPI States */
#define SPI_DISABLE													(0)
#define	SPI_ENABLE													(1)

/* ******************************************************************** */

/* SPI master selection */
#define SPI_SLAVE													(0)
#define SPI_MASTER													(1)

/* ******************************************************************** */

/* SPI clock polarity states */
#define SPI_CPOL_LOW 												(0)
#define SPI_CPOL_HIGH												(1)

/* ******************************************************************** */

/* SPI clock phases */
#define SPI_CPHA_1Edge 												(0)
#define SPI_CPHA_2Edge												(1)

/* ******************************************************************** */

/* SPI errors */
#define SPI_SLAVE_NOT_FOUND											(2)
#define SPI_TRANSMIT_BUF_ISNOT_EMPTY								(3)
#define SPI_RECV_BUF_ISNOT_EMPTY									(4)

/* ******************************************************************** */

typedef struct
{
	SPI_BidMode_t		BIModeState;
	SPI_CRCState_t		CRC_State;
	SPI_CRCPhase_t		CRC_TransNextState;
	SPI_DataFrame_t		FrameSize;
	SPI_TransDir_t		TransMode;
	SPI_SlaveMng_t		SlaveMngState;
	SPI_SlavePinState_t	SlavePinState;
	SPI_FrameFormat_t 	FrameFormatState;
	SPI_State_t			SPI_State;
	SPI_MSTR_t			MasterSelection;
	SPI_CPol_t			ClockPolarity;
	SPI_CPhase_t		ClockPhase;
	uint16				BaudRate;
}SPI_Config_t;

/* ******************************************************************** */
						/* Functions prototypes */
/* ******************************************************************** */
Error_Status SPI_xInit(SPI_TypeDef* SPIx,const SPI_Config_t *SPIx_Cnfg);
Error_Status SPI_xSetState(SPI_TypeDef* SPIx,SPI_State_t Copy_xState);
Error_Status SPI_xSetSwSlavePin(SPI_TypeDef* SPIx,SPI_SlavePinState_t Copy_xSSI_State);
Error_Status SPI_xSendRecieveSynch(SPI_TypeDef* SPIx,SPI_SlaveNum_t Copy_xSlaveNum,SPI_Data_t Copy_xSendData,SPI_Data_t *pxRecvData);

#endif
