/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V02                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"


/************************************************************************************************************* */
/* Local functions prototypes*/
/************************************************************************************************************* */

static void GPIO_vConfgPin_Mode(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Mode);
static void GPIO_vInit(GPIO_TypeDef *GPIOx ,GPIO_ConfigType *GPIOxConfig);



/************************************************************************************************************* */
/*Functions definitions*/
/************************************************************************************************************* */


void GPIO_vInitPortPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Mode)
{
	/*Check if the entered number more than the number of bins*/
	if(Copy_u8Pin > 15)
	{
		/*Returns error*/
		return;
	}
	GPIO_ConfigType GPIO_Pin_Conf;
	GPIO_Pin_Conf.GPIO_PinMode   = Copy_u8Mode;
	GPIO_Pin_Conf.GPIO_PinNumber = Copy_u8Pin;

	GPIO_vInit(GPIOx , &GPIO_Pin_Conf);
}


/************************************************************************************************************* */


uint8 GPIO_u8ReadPortPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin)
{
	/*Check if the entered number more than the number of bins*/
	if(Copy_u8Pin > 15)
	{
		/*Returns error*/
		return 0;
	}
	uint8 LOC_u8Ret_Val;

	/*Read the pin*/
	LOC_u8Ret_Val=GET_BIT(GPIOx->IDR , Copy_u8Pin);

	return LOC_u8Ret_Val;
}

/************************************************************************************************************* */


void GPIO_vWritePortPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Val)
{
	/*Check if the entered number more than the number of bins*/
	if(Copy_u8Pin > 15)
	{
		/*Returns error*/
		return;
	}
	if(Copy_u8Val == GPIO_HIGH)
	{
		GPIOx->BSRR = (1 << Copy_u8Pin);
	}
	else
	{
		GPIOx->BRR  = (1 << Copy_u8Pin);
	}
}
/************************************************************************************************************* */

void GPIO_vLockPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin,uint8 Copy_u8LockState)
{
	/*Initialize temporary uint32 variable and its bit 16 (LCK bit) is set*/
	uint32 LOC_u32Temp = 0x00010000;

	LOC_u32Temp |= Copy_u8Pin;
	/* Set LCKK bit */
	GPIOx->LCKR = LOC_u32Temp;
	/* Reset LCKK bit */
	GPIOx->LCKR =  Copy_u8Pin;
	/* Set LCKK bit */
	GPIOx->LCKR = LOC_u32Temp;
	/* Read LCKK bit*/
	LOC_u32Temp = GPIOx->LCKR;
	/* Read LCKK bit*/
	LOC_u32Temp = GPIOx->LCKR;

	if(Copy_u8LockState == GPIO_LCK)
	{
		SET_BIT(GPIOx->LCKR, Copy_u8Pin);
	}
	else
	{
		CLEAR_BIT(GPIOx->LCKR, Copy_u8Pin);
	}

}

/************************************************************************************************************* */

uint8 GPIO_u8ReadLockPinState(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin)
{
	if(GET_BIT(GPIOx->LCKR,Copy_u8Pin) == GPIO_LCK)
	{
		return GPIO_LCK;
	}
	else
	{
		return GPIO_UNLCK;
	}
}

/************************************************************************************************************* */
/*Local functions definitions*/
/************************************************************************************************************* */


static void GPIO_vInit(GPIO_TypeDef *GPIOx ,GPIO_ConfigType *GPIOxConfig)
{
	/*Configure GPIO pin mode*/
	GPIO_vConfgPin_Mode(GPIOx,GPIOxConfig->GPIO_PinNumber,GPIOxConfig->GPIO_PinMode);
}

/************************************************************************************************************* */

static void GPIO_vConfgPin_Mode(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Mode)
{
	/*Check if the entered number more than the number of bins*/
	if(Copy_u8Pin > 15)
	{
		/*Return with error*/
		return;
	}

	if (Copy_u8Pin <= 7)
	{
		/*clear bits*/
		GPIOx->CRL &= ~(0xF << Copy_u8Pin*4); /* multiplied *4 because every pin uses 4 bits*/
		/*Assign needed mode*/
		GPIOx->CRL |= (Copy_u8Mode << Copy_u8Pin*4);
	}
	else if(Copy_u8Pin <= 15)
	{
		//return pin index to be from p0 to p7
		Copy_u8Pin = Copy_u8Pin - 8;
		/*clear bits*/
		GPIOx->CRH &= ~(0xF << Copy_u8Pin*4);
		/*Assign needed mode*/
		GPIOx->CRH |= (Copy_u8Mode << Copy_u8Pin*4);
	}
}

