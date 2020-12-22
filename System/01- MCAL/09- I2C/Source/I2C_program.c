/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: I2C_program.c		                                                 */
/* Version	: V01                                                                */
/* Date		: 18 - 12 - 2020                                                     */
/* ***************************************************************************** */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"

/************************************************************************************************************* */
									/* Public functions definitions */
/************************************************************************************************************* */

Error_Status I2C_xInit(I2C_TypeDef* I2Cx , I2C_InitTypeDef *pxI2C_Cnfg)
{
	Error_Status Local_xErrorStatus	=	E_NOK;

	/* Initialize I2C clock pin */
	GPIO_vInitPortPin(I2C_Pins[I2C_SCL].I2C_Port,I2C_Pins[I2C_SCL].I2C_Pin,GPIO_PIN_ALF_OUTPUT_OPENDRAIN_MODE_50MHZ);

	/* Initialize I2C SDA pin */
	GPIO_vInitPortPin(I2C_Pins[I2C_SDA].I2C_Port,I2C_Pins[I2C_SDA].I2C_Pin,GPIO_PIN_ALF_OUTPUT_OPENDRAIN_MODE_50MHZ);

	/* Make sure the I2C is disabled */
	I2C_xSetState(I2Cx,DISABLE);

	/* Configure I2C clock settings */
	Local_xErrorStatus	=	I2C_xSetClkSettings(I2Cx , pxI2C_Cnfg->I2C_ClockSpeed, pxI2C_Cnfg->I2C_DutyCycle);

	/* Configure I2C DMA requests state */
	Local_xErrorStatus	=	I2C_xCnfgDMA(I2Cx , pxI2C_Cnfg->I2C_DMA);

	/* Configure I2C Address 1 */
	Local_xErrorStatus	=	I2C_xSetAddress1(I2Cx, pxI2C_Cnfg->I2C_OwnAddress1,pxI2C_Cnfg->I2C_AddressLength);

	/* Configure I2C mode */
	Local_xErrorStatus	=	I2C_xSetMode(I2Cx , pxI2C_Cnfg->I2C_Mode);

	/* Configure I2C ACK state */
	Local_xErrorStatus	=	I2C_xSetACK(I2Cx , pxI2C_Cnfg->I2C_Ack);

	/* Configure I2C Address 2 */
	Local_xErrorStatus	=	I2C_xSetAddress2(I2Cx, pxI2C_Cnfg->I2C_OwnAddress2,pxI2C_Cnfg->I2C_DualAddressMode);

	/* Configure I2C general call */
	Local_xErrorStatus	=	I2C_xSetGenralCall(I2Cx,pxI2C_Cnfg->I2C_GeneralCall);

	/* Configure I2C Interrupts */
	Local_xErrorStatus	=	I2C_xCnfgInterrupts(I2Cx,&(pxI2C_Cnfg->I2C_Interrupts));

	/* Enable selected I2C */
	Local_xErrorStatus	=	I2C_xSetState(I2Cx , pxI2C_Cnfg->I2C_InitialState);

	return Local_xErrorStatus;
}

/************************************************************************************************************* */

Flag_Status I2C_xIsBusy(I2C_TypeDef *I2Cx)
{
	Flag_Status Local_xFlagStatus	=	E_NOK;
	Local_xFlagStatus	=	I2C_xGetFlagStatus(I2Cx,I2C_FLAG_BUSY);

	return Local_xFlagStatus;
}

/************************************************************************************************************* */

/* Function to ease initialization of I2C struct with basic requirements */
void I2C_vInitStruct(I2C_InitTypeDef *pxI2C_Cnfg, uint8 Copy_u8MasterSlave , uint16 Copy_u16NodeAdd)
{
	/*---------------- Reset I2C init structure parameters values ----------------*/
	/* initialize the I2C_ClockSpeed member */
	pxI2C_Cnfg->I2C_ClockSpeed							=	100000;
	/* Initialize the I2C_Mode member */
	pxI2C_Cnfg->I2C_Mode								=	I2C_MODE_I2C;
	/* Initialize the I2C_DutyCycle member */
	pxI2C_Cnfg->I2C_DutyCycle							=	I2C_DUTY_CYCLE_2;
	/* Initialize the I2C_OwnAddress1 member */
	pxI2C_Cnfg->I2C_OwnAddress1							=	Copy_u16NodeAdd;

	/* Initialize the I2C_Ack member */
	if(Copy_u8MasterSlave == I2C_SLAVE)
	{
		pxI2C_Cnfg->I2C_Ack								=	ENABLE;
		pxI2C_Cnfg->I2C_Interrupts.I2C_EventIntState	=	ENABLE;
	}
	else if(Copy_u8MasterSlave == I2C_MASTER)
	{
		pxI2C_Cnfg->I2C_Ack								=	DISABLE;
	}
	else
	{
		/* No Action */
	}

	/* Initialize the I2C_AcknowledgedAddress member */
	pxI2C_Cnfg->I2C_AddressLength						=	I2C_ADDRESS_7BIT;
	/* Initialize GCALL */
	pxI2C_Cnfg->I2C_GeneralCall							=	DISABLE;
	/* initial state for I2C */
	pxI2C_Cnfg->I2C_InitialState						=	ENABLE;
}

/************************************************************************************************************* */

Error_Status I2C_xSetState(I2C_TypeDef* I2Cx , FunctionalState Copy_xI2C_State)
{
	switch(Copy_xI2C_State)
	{
	case DISABLE:
		CLEAR_BIT(I2Cx->CR1,0);
		break;
	case ENABLE:
		SET_BIT(I2Cx->CR1,0);
		break;
	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/************************************************************************************************************* */

Error_Status I2C_xMasterWrite(I2C_TypeDef* I2Cx,uint16 Copy_u16SlaveAddress,uint8 *pu8Data,uint8 Copy_u8Size)
{
	Error_Status Local_xErrorStatus =	E_NOK;
	uint8 u8DataIndex				=	0;

	/* Make sure the I2C is enabled */
	Local_xErrorStatus	=	I2C_xSetState(I2Cx,ENABLE);

	/* Send start bit */
	Local_xErrorStatus	=	I2C_xGenerateStart(I2Cx,ENABLE);

	/* Send the slave address */
	Local_xErrorStatus	=	I2C_xSend7BitAddress(I2Cx,Copy_u16SlaveAddress,I2C_DIRECTION_TRANSMITTER);

	/* Send the data */
	for(u8DataIndex = 0;u8DataIndex < Copy_u8Size;u8DataIndex++)
	{
		I2C_vSendData(I2Cx,pu8Data[u8DataIndex]);
	}

	/* Send stop bit */
	Local_xErrorStatus	=	I2C_xGenerateStop(I2Cx,ENABLE);

	return Local_xErrorStatus;
}

/************************************************************************************************************* */

Error_Status I2C_xMasterRead(I2C_TypeDef* I2Cx,uint16 Copy_u16SlaveAddress,uint8 *pu8RecvData,uint8 Copy_u8Size)
{
	Error_Status Local_xErrorStatus =	E_NOK;
	uint8 u8DataIndex				=	0;

	/* Make sure the I2C is enabled */
	Local_xErrorStatus	=	I2C_xSetState(I2Cx,ENABLE);

	/* Send start bit */
	Local_xErrorStatus	=	I2C_xGenerateStart(I2Cx,ENABLE);

	/* Send the slave address */
	Local_xErrorStatus	=	I2C_xSend7BitAddress(I2Cx,Copy_u16SlaveAddress,I2C_DIRECTION_TRANSMITTER);

	/* Send the data */
	for(u8DataIndex = 0;u8DataIndex < Copy_u8Size;u8DataIndex++)
	{
		pu8RecvData[u8DataIndex]	=	I2C_u8ReceiveData(I2Cx);
	}

	/* Send stop bit */
	Local_xErrorStatus	=	I2C_xGenerateStop(I2Cx,ENABLE);

	return Local_xErrorStatus;
}

/************************************************************************************************************* */

Flag_Status I2C_xSlaveCheckAddressMatch(I2C_TypeDef* I2Cx)
{
	/* Wait till the address flag is SET */
	while(I2C_xGetFlagStatus(I2Cx,I2C_FLAG_ADDR) != E_OK)
	{
		asm("NOP");
	}

	return E_OK;
}

/************************************************************************************************************* */

Error_Status I2C_xSlaveWrite(I2C_TypeDef* I2Cx,uint8 *pu8Data,uint8 Copy_u8Size)
{
	Error_Status Local_xErrorStatus =	E_NOK;
	uint8 u8DataIndex				=	0;

	/* Make sure the I2C is enabled */
	Local_xErrorStatus	=	I2C_xSetState(I2Cx,ENABLE);

	/* Send start bit */
	Local_xErrorStatus	=	I2C_xGenerateStart(I2Cx,ENABLE);

	/* Send the data */
	for(u8DataIndex = 0;u8DataIndex < Copy_u8Size;u8DataIndex++)
	{
		I2C_vSendData(I2Cx,pu8Data[u8DataIndex]);
	}

	/* Send stop bit */
	Local_xErrorStatus	=	I2C_xGenerateStop(I2Cx,ENABLE);

	return Local_xErrorStatus;
}

/************************************************************************************************************* */

Error_Status I2C_xSlaveRead(I2C_TypeDef* I2Cx,uint8 *pu8RecvData,uint8 Copy_u8Size)
{
	Error_Status Local_xErrorStatus =	E_NOK;
	uint8 u8DataIndex				=	0;

	/* Make sure the I2C is enabled */
	Local_xErrorStatus	=	I2C_xSetState(I2Cx,ENABLE);

	/* Send start bit */
	Local_xErrorStatus	=	I2C_xGenerateStart(I2Cx,ENABLE);


	/* Send the data */
	for(u8DataIndex = 0;u8DataIndex < Copy_u8Size;u8DataIndex++)
	{
		pu8RecvData[u8DataIndex]	=	I2C_u8ReceiveData(I2Cx);
	}

	/* Send stop bit */
	Local_xErrorStatus	=	I2C_xGenerateStop(I2Cx,ENABLE);

	return Local_xErrorStatus;
}

/************************************************************************************************************* */

Error_Status I2C_xGenerateStart(I2C_TypeDef* I2Cx, FunctionalState Copy_xStartState)
{
	/* The bit is set and cleared by software, cleared by hardware when a Stop condition is
		detected, set by hardware when a timeout error is detected. */

	uint16 StatusRegisterVal = 0;
	switch(Copy_xStartState)
	{
	case DISABLE:
		CLEAR_BIT(I2Cx->CR1 , 8);
		break;
	case ENABLE:
		SET_BIT(I2Cx->CR1 , 8);

		/* Wait till the start bit flag is SET */
		while(I2C_xGetFlagStatus(I2Cx,I2C_FLAG_SB) != E_OK)
		{
			asm("NOP");
		}
		/* Read the status register to clear start bit flag */
		I2C_xReadRegister(I2Cx,I2C_REGISTER_SR1,&StatusRegisterVal);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/************************************************************************************************************* */

Error_Status I2C_xGenerateStop(I2C_TypeDef* I2Cx, FunctionalState Copy_xStartState)
{
	/* This bit is set and cleared by software and cleared by hardware when start is sent or PE=0. */
	switch(Copy_xStartState)
	{
	case DISABLE:
		CLEAR_BIT(I2Cx->CR1 , 9);
		break;
	case ENABLE:
		SET_BIT(I2Cx->CR1 , 9);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/************************************************************************************************************* */

Error_Status I2C_xSetACK(I2C_TypeDef* I2Cx ,FunctionalState Copy_xACK_State)
{
	switch(Copy_xACK_State)
	{
	case DISABLE:
		I2Cx->CR1 &= I2C_ACK_DISABLE;
		break;

	case ENABLE:
		I2Cx->CR1 |= I2C_ACK_ENABLE;
		break;

	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/************************************************************************************************************* */

Error_Status I2C_xCnfgClockStretch(I2C_TypeDef* I2Cx, FunctionalState Copy_xClkStretchState)
{
	switch(Copy_xClkStretchState)
	{
	case DISABLE:
		SET_BIT(I2Cx->CR1 , 7);
		break;

	case ENABLE:
		CLEAR_BIT(I2Cx->CR1 , 7);
		break;

	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/************************************************************************************************************* */

Flag_Status I2C_xGetFlagStatus(I2C_TypeDef* I2Cx, uint32 Copy_u32Flag)
{
	if(I2C_IS_VALID_FLAG(Copy_u32Flag) != E_OK)
	{
		return E_NOK;
	}
	volatile uint32 I2C_BaseAddress = (uint32)I2Cx;
	uint32 I2C_DetectSR = 0;
	Flag_Status Local_xFlagStatus	=	E_NOK;

	/* Read flag register index */
	I2C_DetectSR = Copy_u32Flag >> 28;

	/* Get bit[23:0] of the flag */
	Copy_u32Flag &= I2C_FLAG_MASK;

	if(I2C_DetectSR != 0)
	{
		/* Get the I2Cx SR1 register address */
		I2C_BaseAddress += I2C_REGISTER_SR1;
	}
	else
	{
		/* Flag in I2Cx SR2 Register */
		Copy_u32Flag = (uint32)(Copy_u32Flag >> 16);
		/* Get the I2Cx SR2 register address */
		I2C_BaseAddress += I2C_REGISTER_SR2;
	}

	if(((*(volatile uint32 *)I2C_BaseAddress) & Copy_u32Flag) != (uint32)E_NOK)
	{
		/* I2C_FLAG is set */
		Local_xFlagStatus = E_OK;
	}
	else
	{
		/* I2C_FLAG is clear */
		Local_xFlagStatus = E_NOK;
	}

	/* Return the I2C_FLAG status */
	return  Local_xFlagStatus;

}

/************************************************************************************************************* */

Error_Status I2C_xSetGenralCall(I2C_TypeDef* I2Cx, FunctionalState Copy_xGCallState)
{
	switch(Copy_xGCallState)
	{
	case DISABLE:
		CLEAR_BIT(I2Cx->CR1 , 6);
		break;

	case ENABLE:
		SET_BIT(I2Cx->CR1 , 6);
		break;

	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/************************************************************************************************************* */

void I2C_vSendData(I2C_TypeDef* I2Cx, uint8 Data)
{
	uint16 StatusRegVal		=	0;

	while(I2C_xGetFlagStatus(I2Cx,I2C_FLAG_TXE) != E_OK)
	{
		asm("NOP");
	}

	I2C_xReadRegister(I2Cx,I2C_REGISTER_SR1,&StatusRegVal);

	/* Write in the DR register the data to be sent */
	I2Cx->DR = Data;
}

/************************************************************************************************************* */

uint8 I2C_u8ReceiveData(I2C_TypeDef* I2Cx)
{
	uint8 Local_u8RecvData	=	0;
	uint16 StatusRegVal		=	0;

	while(I2C_xGetFlagStatus(I2Cx,I2C_FLAG_RXNE) != E_OK)
	{
		asm("NOP");
	}
	/* Return the data in the DR register */
	Local_u8RecvData = (uint8)I2Cx->DR;

	I2C_xReadRegister(I2Cx,I2C_REGISTER_SR1,&StatusRegVal);

	return Local_u8RecvData;
}

/************************************************************************************************************* */

Error_Status I2C_xSend7BitAddress(I2C_TypeDef* I2Cx, uint8 Address, uint8 Copy_u8Direction)
{
	if(I2C_IS_VALID_DIRECTION(Copy_u8Direction)	!= E_OK)
	{
		return E_NOK;
	}

	uint16 StatusRegisterVal = 0;
	/* Test on the direction to set/reset the read/write bit */
	if (Copy_u8Direction != I2C_DIRECTION_TRANSMITTER)
	{
		/* Set the address bit0 for read */
		Address |= OAR1_ADD_SET;

	}
	else
	{
		Address &= OAR1_ADD_RESET;
	}

	/* Send the address */
	I2Cx->DR = Address;

	/* Wait till the address flag is SET */
	while(I2C_xGetFlagStatus(I2Cx,I2C_FLAG_ADDR) != E_OK)
	{
		asm("NOP");
	}

	/* Read the two status registers to clear the flag */
	I2C_xReadRegister(I2Cx,I2C_REGISTER_SR1,&StatusRegisterVal);
	I2C_xReadRegister(I2Cx,I2C_REGISTER_SR2,&StatusRegisterVal);

	return E_OK;
}

/************************************************************************************************************* */

Error_Status I2C_xReadRegister(I2C_TypeDef* I2Cx, uint8 Copy_u8Register ,uint16 *pu16RegVal)
{
	if(I2C_IS_VALID_REG(Copy_u8Register) != E_OK)
	{
		return E_NOK;
	}

	volatile uint32 Local_u32Value = 0;

	Local_u32Value = (uint32) I2Cx;
	Local_u32Value += Copy_u8Register;

	/* Assign the selected register value */
	*pu16RegVal	=	(*(volatile uint16 *) Local_u32Value);

	return E_OK;
}

/************************************************************************************************************* */

Error_Status I2C_xCnfgInterrupts(I2C_TypeDef *I2Cx, I2C_IntState_t *I2C_IntState)
{
	Error_Status Local_xErrorStatus	=	E_OK;

	switch (I2C_IntState->I2C_BufferIntState)
	{
	case DISABLE:
		CLEAR_BIT(I2Cx->CR2,10);
		break;
	case ENABLE:
		SET_BIT(I2Cx->CR2,10);
		break;
	default:
		Local_xErrorStatus	=	E_NOK;
		break;
	}

	switch (I2C_IntState->I2C_EventIntState)
	{
	case DISABLE:
		CLEAR_BIT(I2Cx->CR2,9);
		break;
	case ENABLE:
		SET_BIT(I2Cx->CR2,9);
		break;
	default:
		Local_xErrorStatus	=	E_NOK;
		break;
	}

	switch (I2C_IntState->I2C_ErrorIntState)
	{
	case DISABLE:
		CLEAR_BIT(I2Cx->CR2,8);
		break;
	case ENABLE:
		SET_BIT(I2Cx->CR2,8);
		break;
	default:
		Local_xErrorStatus	=	E_NOK;
		break;
	}

	return Local_xErrorStatus;
}
/************************************************************************************************************* */
/* Local functions definitions */
/************************************************************************************************************* */

static Error_Status I2C_xSetClkSettings(I2C_TypeDef* I2Cx , uint32 Copy_u32ClockSpeed ,uint16 Copy_u16DutyCycle)
{
	if(I2C_IS_VALID_CLOCK_SPEED(Copy_u32ClockSpeed) != E_OK)
	{
		return E_NOK;
	}
	if(I2C_IS_DUTY_CYCLE(Copy_u16DutyCycle) != E_OK)
	{
		return E_NOK;
	}

	Error_Status Local_xErrorStatus	=	E_NOK;
	uint16 Local_u16I2C_Freq		=	0;
	uint16 Local_u16Reseult			=	0;
	uint32 Local_APB1Freq			=	0;

	/* Set I2C clock frequency as APB1 bus frequency */
	/* Clear clock frequency bits */
	I2Cx->CR2 &= 0xFFC0;
	Local_xErrorStatus	=	RCC_xGetAPB1_Freq(&Local_APB1Freq);
	/* Set the I2C frequency */
	Local_u16I2C_Freq = (uint16) (Local_APB1Freq/1000000);
	I2Cx->CR2 |= Local_u16I2C_Freq;


	/* Disable the selected I2C to be able to modify CCR and TRISE registers */
	CLEAR_BIT(I2Cx->CR1 , 0);

	if(Copy_u32ClockSpeed <= I2C_STANDARD_MODE_SPEED_MAX)
	{
		/* Duty cycle won't be configured in standard mode */
		UN_USED(Copy_u16DutyCycle);

		/* TRISE Register must be programmed with the maximum SCL rise time given in the I2C bus
		specification, incremented by 1. */
		I2Cx->TRISE	=	Local_u16I2C_Freq + 1;

		/* T = 2 * CCR *PCLCK */
		/* Standard mode speed calculate */
		Local_u16Reseult = (uint16)(Local_APB1Freq / (Copy_u32ClockSpeed * 2));
		/* If the result less than the allowed CCR for standard mode */
		if(Local_u16Reseult < I2C_MIN_ALLOWED_CCR_SM)
		{
			/* Set the result as minimum allowed CCR value */
			Local_u16Reseult = I2C_MIN_ALLOWED_CCR_SM;
		}
	}
	else /* Less than standard fast speed I2C_STANDARD_FAST_SPEED_MAX = 400 KHZ */
	{
		/* Set Maximum Rise Time for fast mode */
		I2Cx->TRISE = (uint16)(((Local_u16I2C_Freq * (uint16)300) / (uint16)1000) + (uint16)1);

		if (Copy_u16DutyCycle == I2C_DUTY_CYCLE_2)
		{
			/* Fast mode speed calculate: Tlow/Thigh = 2 */
			Local_u16Reseult = (uint16)(Local_APB1Freq / (Copy_u32ClockSpeed * 3));
		}
		else /* I2C_DutyCycle_16_9 */
		{
			/* Fast mode speed calculate: Tlow/Thigh = 16/9 */
			Local_u16Reseult = (uint16)(Local_APB1Freq / (Copy_u32ClockSpeed * 25));
			/* Set DUTY bit */
			Local_u16Reseult |= I2C_DUTY_CYCLE_16_9;
		}

		/* If the result less than the allowed CCR for fast mode */
		if(Local_u16Reseult < I2C_MIN_ALLOWED_CCR_FM)
		{
			/* Set the result as minimum allowed CCR value */
			Local_u16Reseult	|=	I2C_MIN_ALLOWED_CCR_FM;
		}

		/* Selcet fast mode */
		Local_u16Reseult |= CCR_FS_SET;
	}

	/* Assign the result to clock control register */
	I2Cx->CCR = Local_u16Reseult;

	return Local_xErrorStatus;
}

/************************************************************************************************************* */

static Error_Status I2C_xSetMode(I2C_TypeDef* I2Cx , uint16 Copy_u16Mode)
{
	if(I2C_IS_MODE(Copy_u16Mode) != E_OK)
	{
		return E_NOK;
	}

	I2Cx->CR1 |= Copy_u16Mode;

	return E_OK;
}

/************************************************************************************************************* */

static Error_Status I2C_xSetAddress1(I2C_TypeDef* I2Cx , uint16 Copy_u16Address , uint16 Copy_u16AddressLength)
{
	/* Check that the address isn't more than 10 bits */
	if(I2C_IS_VALID_ADDRESS1(Copy_u16Address) != E_OK)
	{
		return E_NOK;
	}

	if(I2C_IS_VALID_ADDRESS_LENGTH(Copy_u16AddressLength) != E_OK)
	{
		return E_NOK;
	}

	/* Clear Address bits */
	I2Cx->OAR1 &= 0xFF01 ;
	switch(Copy_u16AddressLength)
	{
	case I2C_ADDRESS_7BIT:
		I2Cx->OAR1 |= (Copy_u16Address << 1) | Copy_u16AddressLength;
		break;
	case I2C_ADDRESS_10BIT:
		I2Cx->OAR1 |= Copy_u16Address | Copy_u16AddressLength;
		break;
	default:
		/* No Action */
		break;
	}

	return E_OK;
}

/************************************************************************************************************* */

static Error_Status I2C_xSetAddress2(I2C_TypeDef* I2Cx , uint16 Copy_u16Address , uint16 Copy_u16DualMode)
{
	/* Check that the address isn't more than 10 bits */
	if(I2C_IS_VALID_ADDRESS2(Copy_u16Address) != E_NOK)
	{
		return E_NOK;
	}

	if(I2C_IS_DUAL_ADDRESS(Copy_u16DualMode) != E_NOK)
	{
		return E_NOK;
	}

	if(Copy_u16DualMode == I2C_DUAL_ADDRESS_ENABLE)
	{
		I2Cx->OAR2 |= (Copy_u16Address << 1) | Copy_u16DualMode;
	}

	return E_OK;
}

/************************************************************************************************************* */

static Error_Status I2C_xCnfgDMA(I2C_TypeDef* I2Cx , FunctionalState Copy_xDMA_State)
{
	switch(Copy_xDMA_State)
	{
	case DISABLE:
		CLEAR_BIT(I2Cx->CR2,11);
		break;
	case ENABLE:
		SET_BIT(I2Cx->CR2,11);
		break;
	default:
		return E_NOK;
		break;
	}

	return E_OK;
}

/************************************************************************************************************* */
/* I2C ISRs */
/************************************************************************************************************* */
void I2C1_EV_IRQHandler(void)
{
	uint16 StatusRegVal	=	E_NOK;
	if(I2C_xGetFlagStatus(I2C1,I2C_FLAG_ADDR)	==	E_OK)
	{
		I2C_xReadRegister(I2C1,I2C_REGISTER_SR1,&StatusRegVal);

		UN_USED(StatusRegVal);
	}
}
