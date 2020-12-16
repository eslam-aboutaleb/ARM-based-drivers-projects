/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: ADC_program.c		                                                 */
/* Version	: V01                                                                */
/* Date		: 16 - 12 - 2020                                                     */
/* ***************************************************************************** */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"

#include "ADC_interface.h"
#include "ADC_private.h"


/************************************************************************************************************* */
										/* Public functions definitions */
/************************************************************************************************************* */

/* Initializes ADC settings */
Error_Status ADC_xInit(ADC_TypeDef* ADCx, const ADC_InitTypeDef *pxADC_Cnfg)
{
	/* Check if the pointer to struct is valid */
	if(pxADC_Cnfg == NULL)
	{
		return E_NOK;
	}

	Error_Status Local_xErrorStatus	=	E_NOK;
	/* Configure ADC mode */
	Local_xErrorStatus	=	ADC_xSetMode(ADCx,pxADC_Cnfg->ADC_Mode);
	/* Configure ADC scan mode */
	Local_xErrorStatus	=	ADC_xSetScanMode(ADCx,pxADC_Cnfg->ADC_ScanConvMode);
	/* Configure ADC Data align mode */
	Local_xErrorStatus	=	ADC_xSetDataAlignMode(ADCx,pxADC_Cnfg->ADC_DataAlign);
	/* Configure ADC external trigger for regular group */
	Local_xErrorStatus	=	ADC_xExternalTrigConvCmd(ADCx,pxADC_Cnfg->ADC_ExternalTrigConv);
	/* Configure ADC continuous mode */
	Local_xErrorStatus	=	ADC_xSetContinuousMode(ADCx,pxADC_Cnfg->ADC_ScanConvMode);
	/* Configure ADC number of channels */
	Local_xErrorStatus	=	ADC_xSetNumberOfChannels(ADCx,pxADC_Cnfg->ADC_NbrOfChannel);

	return Local_xErrorStatus;
}

/************************************************************************************************************* */
/* Initializes ADC configuration structure with custom setting for the ease of use */
void ADC_vInitStruct(ADC_InitTypeDef *pxADC_Cnfg)
{
	/* Initialize the ADC_DataAlign member */
	pxADC_Cnfg->ADC_DataAlign			= ADC_DATA_ALIGN_RIGHT;
	/* Initialize the ADC mode member */
	pxADC_Cnfg->ADC_Mode				= ADC_MODE_INDEPENDENT;
	/* Initialize the ADC number of channels member */
	pxADC_Cnfg->ADC_NbrOfChannel		= 1;
	/* Initialize the ADC external trigger member */
	pxADC_Cnfg->ADC_ExternalTrigConv	= ADC_EXTERNALTRIGCONV_NONE;
	/* Initialize the continuous mode member */
	pxADC_Cnfg->ADC_ContinuousConvMode	= DISABLE;
	/* Initialize the scan mode member */
	pxADC_Cnfg->ADC_ScanConvMode		= DISABLE;
}

/************************************************************************************************************* */
/* Sets number of channels to be used: Single channel or multi-channels */
static Error_Status ADC_xSetNumberOfChannels(ADC_TypeDef *ADCx, uint8 Copy_u8NChannels)
{
	if(ADC_IS_VALID_N_CHANNELS(Copy_u8NChannels) != E_OK)
	{
		return E_NOK;
	}

	/* Assign the number of channels in sequence register */
	ADCx->SQR1 |= ((Copy_u8NChannels - (uint8) 1) << 20);

	return E_OK;
}

/************************************************************************************************************* */
/* Configures ADC channel rank and sampling time */
Error_Status ADC_xChannelCnfg(ADC_TypeDef *ADCx,uint8 Copy_u8ChNum,uint32 Copy_u32Rank,uint8 Copy_u8SampleTime)
{
	/* Check if is it valid channel */
	if(ADC_IS_VALID_CHANNEL(Copy_u8ChNum) != E_OK)
	{
		return E_NOK;
	}
	/* Check if is it valid rank */
	if(ADC_IS_VALID_RANK(Copy_u32Rank) != E_OK)
	{
		return E_NOK;
	}
	/* Check if is it valid sampling time */
	if(ADC_IS_VALID_SAMPLE_TIME(Copy_u8SampleTime) != E_OK)
	{
		return E_NOK;
	}

	/* Regular sequence configuration */
	/* For Rank 1 to 6 */
	if (Copy_u32Rank < 7U)
	{
		ADCx->SQR3 &= ~((0x1F)<<(5*(Copy_u32Rank-1)));
		ADCx->SQR3 |= (((uint32)Copy_u8ChNum)<<(5*(Copy_u32Rank-1)));
	}
	/* For Rank 7 to 12 */
	else if (Copy_u32Rank < 13U)
	{
		ADCx->SQR2 &= ~((0x1F)<<(5*(Copy_u32Rank-7)));
		ADCx->SQR2 |= (((uint32)Copy_u8ChNum)<<(5*(Copy_u32Rank-7)));
	}
	/* For Rank 13 to 16 */
	else
	{
		ADCx->SQR1 &= ~((0x1F)<<(5*(Copy_u32Rank-13)));
		ADCx->SQR1 |= (((uint32)Copy_u8ChNum)<<(5*(Copy_u32Rank-13)));
	}

	/* if ADC_Channel_10 ... ADC_Channel_17 is selected */
	if (Copy_u8ChNum > ADC_CHANNEL_9)
	{
		/* Clear the old channel sample time */
		ADCx->SMPR1 &= 0x7 << (3 * (Copy_u8ChNum - 10));
		/* Set the new channel sample time */
		ADCx->SMPR1 |= (uint32)Copy_u8SampleTime << (3 * (Copy_u8ChNum - 10));
	}
	else /* ADC_Channel include in ADC_Channel_[0..9] */
	{
		/* Clear the old channel sample time */
		ADCx->SMPR2 &= 0x7 << (3 * Copy_u8ChNum);
		/* Set the new channel sample time */
		ADCx->SMPR2 |= (uint32)Copy_u8SampleTime << (3 * Copy_u8ChNum);
	}

	return E_OK;
}

/************************************************************************************************************* */
/* Gets single conversion value with custom setting for the ease of use */
uint16 ADC_u16GetSingleConv(ADC_TypeDef *ADCx,uint8 Copy_u8Channel,uint8 Copy_u8SamplingTime)
{
	uint16 Local_u16RecvData	=	0;
	/* Configures the channel */
	ADC_xChannelCnfg(ADCx,Copy_u8Channel,ADC_REGULAR_RANK_1,Copy_u8SamplingTime);
	/* Starts ADC */
	ADC_xStart(ADCx);
	/* loop until End of conversion flag is set */
	while(ADC_xPollForConv(ADCx)!=E_OK)
	{
		asm("NOP");
	}
	/* Get conversion value */
	ADC_vGetConversionValue(ADCx,&Local_u16RecvData);

	/* Disable ADC */
	ADC_xDisalbe(ADCx);

	return Local_u16RecvData;
}

/************************************************************************************************************* */
/* Enables ADC and start conversion */
Error_Status ADC_xStart(ADC_TypeDef *ADCx)
{
	Error_Status Local_xErrorStatus	=	E_NOK;
	/* Clear ADC flags */
	Local_xErrorStatus	=	ADC_ClearFlag(ADCx,ADC_FLAG_EOC);
	Local_xErrorStatus	=	ADC_ClearFlag(ADCx,ADC_FLAG_AWD);
	Local_xErrorStatus	=	ADC_ClearFlag(ADCx,ADC_FLAG_JEOC);
	Local_xErrorStatus	=	ADC_ClearFlag(ADCx,ADC_FLAG_JSTRT);
	Local_xErrorStatus	=	ADC_ClearFlag(ADCx,ADC_FLAG_STRT);

	/* Enable ADC */
	Local_xErrorStatus	=	ADC_xEnable(ADCx);
	/* Enable calibration */
	ADC_vStartCalibration(ADCx);
	/* Start ADC conversion */
	Local_xErrorStatus	=	ADC_xSoftwareStartConv(ADCx,ENABLE);

	return Local_xErrorStatus;
}

/************************************************************************************************************* */
/* Polling on End of conversion flag */
Error_Status ADC_xPollForConv(ADC_TypeDef *ADCx)
{
	Error_Status Local_xErrorStatus	=	E_NOK;

	while(ADC_GetFlagStatus(ADCx,ADC_FLAG_EOC)	!=	E_OK)
	{
		asm("NOP");
	}
	/* Clear ADC flags */
	Local_xErrorStatus	=	ADC_ClearFlag(ADCx,ADC_FLAG_EOC);
	Local_xErrorStatus	=	ADC_ClearFlag(ADCx,ADC_FLAG_STRT);

	return Local_xErrorStatus;
}

/************************************************************************************************************* */
/* Configure ADC peripheral state */
Error_Status ADC_xSetADCState(ADC_TypeDef *ADCx, ADC_State_t Copy_xState)
{
	/* Check state */
	switch(Copy_xState)
	{
	case ADC_DISBLE:
		CLEAR_BIT(ADCx->CR2,0);
		break;
	case ADC_ENABLE:
		SET_BIT(ADCx->CR2,0);
		break;
	default:
		/* Wrong choice */
		return E_NOK;
		break;
	}
	return E_OK;
}

/************************************************************************************************************* */
/* Configures DMA state */
Error_Status ADC_xSetDMA(ADC_TypeDef* ADCx, FunctionalState Copy_xDMA_State)
{
	switch(Copy_xDMA_State)
	{
	case ENABLE:
		/* Enable the selected ADC DMA request */
		ADCx->CR2 |= CR2_DMA_Set;
		break;
	case DISABLE:
		/* Disable the selected ADC DMA request */
		ADCx->CR2 &= CR2_DMA_Reset;
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/************************************************************************************************************* */
/* Resets calibration registers */
void ADC_vResetCalibration(ADC_TypeDef* ADCx)
{
	/* Resets the selected ADC calibration registers */
	SET_BIT(ADCx->CR2,3);
}

/************************************************************************************************************* */
/*Starts calibration */
void ADC_vStartCalibration(ADC_TypeDef* ADCx)
{
	/* Enable the selected ADC calibration process */
	SET_BIT(ADCx->CR2,2);
}

/************************************************************************************************************* */

/* Gets calibration status */
void ADC_vGetCalibrationStatus(ADC_TypeDef* ADCx ,Flag_Status *pxStatus)
{
	/* Get the selected ADC calibration status */
	*pxStatus = GET_BIT(ADCx->CR2,2);
}

/************************************************************************************************************* */
/* Configures ADC software conversion */
Error_Status ADC_xSoftwareStartConv(ADC_TypeDef* ADCx, FunctionalState Copy_xSwStartState)
{

	if (Copy_xSwStartState == ENABLE)
	{
		/* Enable the selected ADC conversion on external event and start the selected
       ADC conversion */
		ADCx->CR2 |= CR2_EXTTRIG_SWSTART_Set;
	}
	else if(Copy_xSwStartState == DISABLE)
	{
		/* Disable the selected ADC conversion on external event and stop the selected
       ADC conversion */
		ADCx->CR2 &= CR2_EXTTRIG_SWSTART_Reset;
	}
	else
	{
		return E_NOK;
	}

	return E_OK;
}

/************************************************************************************************************* */
/* Gets ADC software conversion status */
void ADC_vGetSoftwareConvStatus(ADC_TypeDef* ADCx,Flag_Status *pxSwStartStatus)
{
	/* the SWSTART bit status */
	*pxSwStartStatus = GET_BIT(ADCx->CR2,22);
}

/************************************************************************************************************* */
/* Gets ADC conversion value */
void ADC_vGetConversionValue(ADC_TypeDef* ADCx , uint16 *pu16ADC_Val)
{
	/* Set the selected ADC conversion value */
	*pu16ADC_Val = (uint16)ADCx->DR;
}


/************************************************************************************************************* */
/* Configures discontinuous mode number of channels */
Error_Status ADC_xDiscModeChannelCountCnfg(ADC_TypeDef* ADCx, uint8 Copy_u8N_Channels)
{
	if(ADC_IS_VALID_N_DISC_CHANNELS(Copy_u8N_Channels) != E_OK)
	{
		return E_NOK;
	}

	/* Clear the old discontinuous mode channel count */
	ADCx->CR1 &= 0xFFFF1FFF;
	/* Set the discontinuous mode channel count */
	ADCx->CR1 |= (Copy_u8N_Channels - 1) << 13;

	return E_OK;
}

/************************************************************************************************************* */
/* Gets ADC flags status */
Flag_Status ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8 Copy_u8FLAG)
{
	if(ADC_IS_VALID_FLAG(Copy_u8FLAG) != E_OK)
	{
		return E_NOK;
	}

	Flag_Status Locla_xFlagStatus = E_NOK;

	/* Check the status of the specified ADC flag */
	if ((ADCx->SR & Copy_u8FLAG) != (uint8)E_NOK)
	{
		/* ADC_FLAG is set */
		Locla_xFlagStatus = E_OK;
	}
	else
	{
		/* ADC_FLAG is reset */
		Locla_xFlagStatus = E_NOK;
	}
	/* Return the ADC_FLAG status */
	return  Locla_xFlagStatus;
}

/************************************************************************************************************* */
/* Clears ADC flags */
Error_Status ADC_ClearFlag(ADC_TypeDef* ADCx, uint8 Copy_u8FLAG)
{
	if(ADC_IS_VALID_FLAG(Copy_u8FLAG) != E_OK)
	{
		return E_NOK;
	}

	/* Clear the selected ADC flags */
	ADCx->SR = ~(uint32)Copy_u8FLAG;

	return E_OK;
}

/************************************************************************************************************* */
/* Enables ADC */
Error_Status ADC_xEnable(ADC_TypeDef* ADCx)
{
	/* Check if ADC is off */
	if(GET_BIT(ADCx->CR2,0) != E_NOK)
	{
		return E_NOK;
	}

	volatile uint32 ADC_StartPauseTime	=	0;
	/* First time to start ADC must enable ADC twice because it is by default in sleep mode */
	/* Enabling ADC sequence */
	SET_BIT(ADCx->CR2,0);

	/* Delay between two starts */
	ADC_StartPauseTime	=	(ADC_START_DELAY_US * (SYSTEM_CLOCK_FREQUENCY/1000000));

	while(ADC_StartPauseTime > 0)
	{
		ADC_StartPauseTime--;
	}

	/* Enable ADC again */
	SET_BIT(ADCx->CR2,0);

	while(GET_BIT(ADCx->CR2,0) == E_NOK)
	{
		/* Wait until ADC is enabled */
	}

	return E_OK;
}

/************************************************************************************************************* */
/* Disables ADC and stops conversions */
Error_Status ADC_xDisalbe(ADC_TypeDef* ADCx)
{
	/* Check if ADC is on */
	if(GET_BIT(ADCx->CR2,0) != E_OK)
	{
		return E_NOK;
	}
	/* Disable ADC */
	CLEAR_BIT(ADCx->CR2,0);

	return E_OK;
}




/************************************************************************************************************* */
										/* Local functions definitions */
/************************************************************************************************************* */
static Error_Status ADC_xSetContinuousMode(ADC_TypeDef* ADCx, FunctionalState Copy_xContState)
{
	switch(Copy_xContState)
	{
	case DISABLE:
		/* Disable continuous mode */
		CLEAR_BIT(ADCx->CR2,1);
		break;
	case ENABLE:
		/* Enable continuous mode */
		SET_BIT(ADCx->CR2,1);
		break;
	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/************************************************************************************************************* */

static Error_Status ADC_xExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState Copy_xExTriggerState)
{
	switch(Copy_xExTriggerState)
	{
	case DISABLE:
		/* Disable the selected ADC conversion on external event */
		CLEAR_BIT(ADCx->CR2,20);
		break;
	case ENABLE:
		/* Enable the selected ADC conversion on external event */
		SET_BIT(ADCx->CR2,20);
		break;
	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/************************************************************************************************************* */

/* Configures data aligning mode */
static Error_Status ADC_xSetDataAlignMode(ADC_TypeDef* ADCx, uint32 Copy_u8AlignMode)
{
	/* Check if is it valid ADC data align mode */
	if(ADC_IS_VALID_ALIGN_MODE(Copy_u8AlignMode) != E_OK)
	{
		return E_NOK;
	}

	ADCx->CR2 |= Copy_u8AlignMode;
	return E_OK;
}

/************************************************************************************************************* */

/* Sets scan mode for ADC */
static Error_Status ADC_xSetScanMode(ADC_TypeDef* ADCx, FunctionalState Copy_xState)
{
	switch(Copy_xState)
	{
	case DISABLE:
		CLEAR_BIT(ADCx->CR1,8);
		break;
	case ENABLE:
		SET_BIT(ADCx->CR1,8);
		break;
	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/************************************************************************************************************* */

/* Sets mode for ADC : Dual mode or independant mode */
static Error_Status ADC_xSetMode(ADC_TypeDef* ADCx , uint32 Copy_u32Mode)
{
	if(ADC_IS_VALID_MODE(Copy_u32Mode) != E_OK)
	{
		return E_NOK;
	}

	/* Assign the mode */
	ADCx->CR1 |= Copy_u32Mode;

	return E_OK;
}

