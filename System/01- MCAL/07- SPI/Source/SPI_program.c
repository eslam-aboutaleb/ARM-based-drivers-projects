/* ******************************************************************** */
/*	Name	:	Eslam Ehab Aboutaleb									*/
/*	Date	:	23/11/2020												*/
/*	File	:	SPI_program.c											*/
/*	Version	:	V01														*/
/* ******************************************************************** */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"

/* ******************************************************************** */
/* Current slave management state */
static SPI_SlaveMng_t SPI_SlaveMmg;
/* ******************************************************************** */

/* ******************************************************************** */
						/* Functions definitions */
/* ******************************************************************** */

Error_Status SPI_xInit(SPI_TypeDef* SPIx,const SPI_Config_t *SPIx_Cnfg)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	uint8 Local_u8Index				=	0;

	/* Set BI direction mode */
	Local_xErrorStatus	=	SPI_xSetBidMode(SPIx,SPIx_Cnfg->BIModeState);
	/* Set CRC */
	Local_xErrorStatus	=	SPI_xEnableCRC(SPIx,SPIx_Cnfg->CRC_State);
	/* Set CRC phase */
	Local_xErrorStatus	=	SPI_xSetCRCPhase(SPIx,SPIx_Cnfg->CRC_TransNextState);
	/* Set data frame size */
	Local_xErrorStatus	=	SPI_xSetDataFrameSize(SPIx,SPIx_Cnfg->FrameSize);
	/* Set transmission direction */
	Local_xErrorStatus	=	SPI_xSetTransferDir(SPIx,SPIx_Cnfg->TransMode);
	/* Set slave management state */
	Local_xErrorStatus	=	SPI_xSetSwSlaveMng(SPIx,SPIx_Cnfg->SlaveMngState);
	/* Set slave pin state */
	Local_xErrorStatus	=	SPI_xSetSwSlavePin(SPIx,SPIx_Cnfg->SlavePinState);
	/* Set frame format (MSB OR LSB) */
	Local_xErrorStatus	=	SPI_xSetFrameFormat(SPIx,SPIx_Cnfg->FrameFormatState);
	/* Set Baud rate */
	Local_xErrorStatus	=	SPI_xSetBaudRate(SPIx,SPIx_Cnfg->BaudRate);
	/* Set Master selection (Master or Slave) */
	Local_xErrorStatus	=	SPI_xSelectMaster(SPIx,SPIx_Cnfg->MasterSelection);
	/* Set clock polarity */
	Local_xErrorStatus	=	SPI_xSetClkPolarity(SPIx,SPIx_Cnfg->ClockPolarity);
	/* Set clock phase */
	Local_xErrorStatus	=	SPI_xSetClkPhase(SPIx,SPIx_Cnfg->ClockPhase);

	if(SPI_ENABLE_SLAVE_MNG	==	SPIx_Cnfg->SlaveMngState)
	{
		SPI_SlaveMmg	=	SPI_ENABLE_SLAVE_MNG;
		/* Initialize slave pins as output and make their ideal state is high */
		for(Local_u8Index = 0;Local_u8Index < SPI_SlavesNum;Local_u8Index++)
		{
			GPIO_vInitPortPin(SPI_MapCnfg[Local_u8Index].SlavePort,SPI_MapCnfg[Local_u8Index].SlavePinNum,GPIO_OUT);
			GPIO_vWritePortPin(SPI_MapCnfg[Local_u8Index].SlavePort,SPI_MapCnfg[Local_u8Index].SlavePinNum,GPIO_HIGH);
		}
	}

	/* Set SPI State (Disable / Enable) */
	Local_xErrorStatus	=	SPI_xSetState(SPIx,SPIx_Cnfg->SPI_State);

	/* Initialize SPI pins */
	GPIO_vInitPortPin(SPI_CLK_PORT,SPI_CLK_PIN,GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_10MHZ);
	GPIO_vInitPortPin(SPI_MOSI_PORT,SPI_MOSI_PIN,GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_10MHZ);
	GPIO_vInitPortPin(SPI_MISO_PORT,SPI_MISO_PIN,GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_10MHZ);

	return Local_xErrorStatus;
}

/* ******************************************************************** */

Error_Status SPI_xSetState(SPI_TypeDef* SPIx,SPI_State_t Copy_xState)
{
	switch(Copy_xState)
	{
	case SPI_DISABLE:
		CLEAR_BIT(SPIx->CR1,6);
		break;
	case SPI_ENABLE:
		SET_BIT(SPIx->CR1,6);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ******************************************************************** */

Error_Status SPI_xSetSwSlavePin(SPI_TypeDef* SPIx,SPI_SlavePinState_t Copy_xSSI_State)
{
	/* This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the
	NSS pin and the IO value of the NSS pin is ignored */
	switch(Copy_xSSI_State)
	{
	case SPI_SSI_LOW:
		CLEAR_BIT(SPIx->CR1,8);
		break;
	case SPI_SSI_HIGH:
		SET_BIT(SPIx->CR1,8);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ******************************************************************** */

Error_Status SPI_xSendRecieveSynch(SPI_TypeDef* SPIx,SPI_SlaveNum_t Copy_xSlaveNum,SPI_Data_t Copy_xSendData,SPI_Data_t *pxRecvData)
{
	Error_Status Local_xErrorStatus	=	E_NOK;

	if(SPI_IS_VALID_SLAVE(Copy_xSlaveNum)	==	E_NOK)
	{
		return SPI_SLAVE_NOT_FOUND;
	}

	/* Check if transmit buffer is empty */
	if(GET_BIT(SPIx->SR,1) == E_NOK)
	{
		Local_xErrorStatus	=	SPI_TRANSMIT_BUF_ISNOT_EMPTY;
	}

	if(SPI_ENABLE_SLAVE_MNG	==	SPI_SlaveMmg)
	{
		/* Set slave pin to low to start communication */
		GPIO_vWritePortPin(SPI_MapCnfg[Copy_xSlaveNum].SlavePort,SPI_MapCnfg[Copy_xSlaveNum].SlavePinNum,GPIO_HIGH);
	}
	/* Send data */
	SPIx->DR	=	Copy_xSendData;

	/* Wait until busy flag is cleared */
	while(GET_BIT(SPIx->SR,7) == E_OK);

	/* Check if receive buffer is empty */
	if(GET_BIT(SPIx->SR,0)	==	E_NOK)
	{
		Local_xErrorStatus	=	SPI_RECV_BUF_ISNOT_EMPTY;
	}

	*pxRecvData	=	SPIx->DR;

	if(SPI_ENABLE_SLAVE_MNG	==	SPI_SlaveMmg)
	{
		/* Set slave pin to high */
		GPIO_vWritePortPin(SPI_MapCnfg[Copy_xSlaveNum].SlavePort,SPI_MapCnfg[Copy_xSlaveNum].SlavePinNum,GPIO_HIGH);
	}
	return Local_xErrorStatus;
}

/* ******************************************************************** */

static Error_Status SPI_xSetBidMode( SPI_TypeDef* SPIx,SPI_BidMode_t Copy_xMode)
{
	switch(Copy_xMode)
	{
	case SPI_TWO_LINES_UNIDIR_MODE:
		CLEAR_BIT(SPIx->CR1,15);
		CLEAR_BIT(SPIx->CR1,14);
		break;
	case SPI_ONE_LINE_BIDIR_MODE_DISABLE_OUTPUT:
		SET_BIT(SPIx->CR1,15);
		CLEAR_BIT(SPIx->CR1,14);
		break;
	case SPI_ONE_LINE_BIDIR_MODE_ENAABLE_OUTPUT:
		SET_BIT(SPIx->CR1,15);
		SET_BIT(SPIx->CR1,14);
		break;
	default:
		return E_NOK;
	}
	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xEnableCRC( SPI_TypeDef* SPIx,SPI_CRCState_t Copy_xOutPutState)
{
	switch(Copy_xOutPutState)
	{
	case SPI_DISABLE_CRC:
		CLEAR_BIT(SPIx->CR1,13);
		break;
	case SPI_ENABLE_CRC:
		SET_BIT(SPIx->CR1,13);
		break;
	default:
		return E_NOK;
	}
	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xSetCRCPhase( SPI_TypeDef* SPIx,SPI_CRCPhase_t Copy_xCRCState)
{
	switch(Copy_xCRCState)
	{
	case SPI_NO_CRC_PHASE:
		CLEAR_BIT(SPIx->CR1,12);
		break;
	case SPI_CRC_PHASE:
		SET_BIT(SPIx->CR1,12);
		break;
	default:
		return E_NOK;
	}
	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xSetDataFrameSize( SPI_TypeDef* SPIx,SPI_DataFrame_t Copy_xDataLength)
{
	switch(Copy_xDataLength)
	{
	case SPI_8_BIT_DATA_FRAME:
		CLEAR_BIT(SPIx->CR1,11);
		break;
	case SPI_16_BIT_DATA_FRAME:
		SET_BIT(SPIx->CR1,11);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xSetTransferDir(SPI_TypeDef* SPIx,SPI_TransDir_t Copy_xDataLength)
{
	switch(Copy_xDataLength)
	{
	case SPI_FULL_DUPLEX:
		CLEAR_BIT(SPIx->CR1,10);
		break;
	case SPI_SIMPLEX_RECV:
		SET_BIT(SPIx->CR1,10);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xSetSwSlaveMng(SPI_TypeDef* SPIx,SPI_SlaveMng_t Copy_xDataLength)
{
	switch(Copy_xDataLength)
	{
	case SPI_DISABLE_SLAVE_MNG:
		CLEAR_BIT(SPIx->CR1,9);
		break;
	case SPI_ENABLE_SLAVE_MNG:
		SET_BIT(SPIx->CR1,9);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xSetFrameFormat(SPI_TypeDef* SPIx,SPI_FrameFormat_t Copy_xFormat)
{
	switch(Copy_xFormat)
	{
	case SPI_MSB_FIRST:
		CLEAR_BIT(SPIx->CR1,7);
		break;
	case SPI_LSB_FIRST:
		SET_BIT(SPIx->CR1,7);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xSetBaudRate(SPI_TypeDef* SPIx,uint16 Copy_u16BaudRate)
{
	/* check if is it valid baud rate */
	if(SPI_IS_VALID_PRESCALER(Copy_u16BaudRate)	==	E_NOK)
	{
		return E_NOK;
	}

	/* Clear selection bits */
	SPIx->CR1 &= 0xFFC7;

	/* Assign baud rate */
	SPIx->CR1 |= Copy_u16BaudRate;

	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xSelectMaster(SPI_TypeDef* SPIx,SPI_MSTR_t Copy_xState)
{
	switch(Copy_xState)
	{
	case SPI_SLAVE:
		CLEAR_BIT(SPIx->CR1,2);
		break;
	case SPI_MASTER:
		SET_BIT(SPIx->CR1,2);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xSetClkPolarity(SPI_TypeDef* SPIx,SPI_CPol_t Copy_xClockPolarityState)
{
	switch(Copy_xClockPolarityState)
	{
	case SPI_CPOL_LOW:
		CLEAR_BIT(SPIx->CR1,1);
		break;
	case SPI_CPOL_HIGH:
		SET_BIT(SPIx->CR1,1);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/* ******************************************************************** */

static Error_Status SPI_xSetClkPhase(SPI_TypeDef* SPIx,SPI_CPhase_t Copy_xClockPhaseState)
{
	switch(Copy_xClockPhaseState)
	{
	case SPI_CPHA_1Edge:
		CLEAR_BIT(SPIx->CR1,0);
		break;
	case SPI_CPHA_2Edge:
		SET_BIT(SPIx->CR1,0);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}
