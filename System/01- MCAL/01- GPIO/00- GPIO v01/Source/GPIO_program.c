/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
												/* Local functions prototypes*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

static void GPIO_vConfgPin_Mode(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Mode);
static void GPIO_vInit(GPIO_TypeDef *GPIOx ,GPIO_ConfigType *GPIOxConfig);



/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
											  /*Functions definitions*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


void GPIO_vInitPortPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Mode)
{
	GPIO_ConfigType GPIO_Pin_Conf;
	GPIO_Pin_Conf.GPIO_PinMode   = Copy_u8Mode;
	GPIO_Pin_Conf.GPIO_PinNumber = Copy_u8Pin;

	GPIO_vInit(GPIOx , &GPIO_Pin_Conf);
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


uint8 GPIO_u8ReadPortPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin)
{
	if(Copy_u8Pin > 15)
	{
		/*Returns error*/
		return 0;
	}
	uint8 LOC_u8Ret_Val;

	LOC_u8Ret_Val=GET_BIT(GPIOx->IDR , Copy_u8Pin);

	return LOC_u8Ret_Val;
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


void GPIO_vWritePortPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Val)
{
	if(Copy_u8Val == GPIO_HIGH)
	{
		SET_BIT(GPIOx->ODR , Copy_u8Pin);
	}
	else
	{
		CLEAR_BIT(GPIOx->ODR , Copy_u8Pin);
	}
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
											/*Local functions definitions*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


static void GPIO_vInit(GPIO_TypeDef *GPIOx ,GPIO_ConfigType *GPIOxConfig)
{
	/*Configure GPIO pin mode*/
	GPIO_vConfgPin_Mode(GPIOx,GPIOxConfig->GPIO_PinNumber,GPIOxConfig->GPIO_PinMode);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

static void GPIO_vConfgPin_Mode(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Mode)
{
	if(Copy_u8Pin > 15)
	{
		/*Return with error*/
		return;
	}

	if (Copy_u8Pin <= 7)
		{
			/*clear bits*/
			GPIOx->CRL &= ~(0xF<<Copy_u8Pin*4); /* multiplied *4 because every pin uses 4 bits*/
			/*Assign needed mode*/
			GPIOx->CRL |= (Copy_u8Mode << Copy_u8Pin*4);
	}
	else if(Copy_u8Pin <= 15)
	{
			//return pin index to be from p0 to p7
			Copy_u8Pin = Copy_u8Pin - 8;
			/*clear bits*/
			GPIOx->CRH &= ~(0xF<<Copy_u8Pin*4);
			/*Assign needed mode*/
			GPIOx->CRH |= (Copy_u8Mode << Copy_u8Pin*4);
	}
}

