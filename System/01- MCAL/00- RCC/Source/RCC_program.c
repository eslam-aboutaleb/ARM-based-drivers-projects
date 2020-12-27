/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"

#include "RCC_interface.h"
#include "RCC_reg.h"
#include "RCC_private.h"
#include "RCC_config.h"

static uint32 APB1Prescaler;
static uint32 APB2Prescaler;
static uint32 AHBPrescaler;
/************************************************************************************************************* */
/*Functions definitions*/
/************************************************************************************************************* */


/*Function to initialize the clock*/
void RCC_vClockInit(RCC_Config_t *RCC_Config)
{
	/* Check first it isn't a null pointer */
	if(RCC_Config == (void*)0)
	{
		return;
	}
	/* Initialize clock source*/
	RCC_vClockSource(RCC_Config->ClockSource);

	if(RCC_Config->ClockSource == RCC_PLL)
	{
		RCC_vPLL_Clock_Source(RCC_Config->PLL_Config.PLL_Source);
		RCC_vPLL_Mul(RCC_Config->PLL_Config.PLL_Mul_Factor);
	}
	else if(RCC_Config->ClockSource == RCC_HSI)
	{
		/* HSI Trim function*/
	}
	else
	{
		/*No Action*/
	}

	/* Adjust prescaler */
	RCC_vBus_Prescaler(RCC_Config);
}

/************************************************************************************************************* */
/* Function to enable and disable peripheral clock*/
void RCC_vSetCLKPeripheral(uint8 Copy_xBus,RCC_Peripheral_t Copy_xPeripheral,uint8 Copy_xState)
{
	/* If the user entered number of peripheral more than 31 (No of register bits) returns with error*/
	if(Copy_xPeripheral > 31)
	{
		/* Return Error*/
		return;
	}
	else
	{
		/* No Action */
	}

	switch(Copy_xBus)
	{
	/*AHB Bus*/
	case RCC_AHB_BUS:
		if(Copy_xState == RCC_ENABLE_PERIPHERAL)
		{
			/*Enable peripheral*/
			SET_BIT(RCC->AHBENR,Copy_xPeripheral);
		}
		else
		{
			CLEAR_BIT(RCC->AHBENR,Copy_xPeripheral);
		}
		break;

		/*APB1 Bus*/
	case RCC_APB1_BUS:
		if(Copy_xState == RCC_ENABLE_PERIPHERAL)
		{
			SET_BIT(RCC->APB1ENR,Copy_xPeripheral);
		}
		else
		{
			CLEAR_BIT(RCC->APB1ENR,Copy_xPeripheral);
		}
		break;

		/*APB2 Bus*/
	case RCC_APB2_BUS:
		if(Copy_xState == RCC_ENABLE_PERIPHERAL)
		{
			SET_BIT(RCC->APB2ENR,Copy_xPeripheral);
		}
		else
		{
			CLEAR_BIT(RCC->APB2ENR,Copy_xPeripheral);
		}
		break;
	}

}

/************************************************************************************************************* */

void RCC_vMCO(uint8 Copy_xMCO_Source)
{
	/*Check which clock source that is used*/
	switch(Copy_xMCO_Source)
	{
	/*No Clock used -> no MCO */
	case MCO_No_CLK:
		CLEAR_BIT(RCC->CFGR,26);
		break;

		/*Current system clock*/
	case MCO_SYSCLK:
		SET_BIT(RCC->CFGR,26);
		CLEAR_BIT(RCC->CFGR,25);
		CLEAR_BIT(RCC->CFGR,24);
		break;

		/* Internal clock*/
	case MCO_HSI:
		SET_BIT(RCC->CFGR,26);
		CLEAR_BIT(RCC->CFGR,25);
		SET_BIT(RCC->CFGR,24);
		break;

		/*External clock*/
	case MCO_HSE:
		SET_BIT(RCC->CFGR,26);
		SET_BIT(RCC->CFGR,25);
		CLEAR_BIT(RCC->CFGR,24);
		break;

		/* PLL clock*/
	case MCO_PLL:
		SET_BIT(RCC->CFGR,26);
		SET_BIT(RCC->CFGR,25);
		SET_BIT(RCC->CFGR,24);
		break;
	}
}

/************************************************************************************************************* */

Error_Status RCC_xGetClkSource(void)
{
	if(GET_BIT( RCC->CFGR , 3) == 0 && GET_BIT( RCC->CFGR , 2) == 0)
	{
		return RCC_HSI;
	}
	else if(GET_BIT( RCC->CFGR , 3) == 0 && GET_BIT( RCC->CFGR , 2) == 1)
	{
		return RCC_HSE;
	}
	else if(GET_BIT( RCC->CFGR , 2) == 1 && GET_BIT( RCC->CFGR , 2) == 0)
	{
		return RCC_PLL;
	}
	else
	{
		/* No Action */
	}

	return ERROR; /*Failed*/
}

/************************************************************************************************************* */

Error_Status RCC_xGetAPB1_Freq(uint32 *pu32Freq)
{
	switch(APB1Prescaler)
	{
	case APB1_NOT_DEVIDED:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY;
		break;
	case APB1_DIVIDED_BY_2:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 2;
		break;
	case APB1_DIVIDED_BY_4:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 4;
		break;
	case APB1_DIVIDED_BY_8:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 8;
		break;
	case APB1_DIVIDED_BY_16:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 16;
		break;
	default:
		*pu32Freq	=	0;
		return E_NOK;
		break;
	}
	return E_OK;
}
/************************************************************************************************************* */
Error_Status RCC_xGetAPB2_Freq(uint32 *pu32Freq)
{
	switch(APB2Prescaler)
	{
	case APB2_NOT_DEVIDED:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY;
		break;
	case APB2_DIVIDED_BY_2:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 2;
		break;
	case APB2_DIVIDED_BY_4:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 4;
		break;
	case APB2_DIVIDED_BY_8:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 8;
		break;
	case APB2_DIVIDED_BY_16:
		*pu32Freq	=	SYSTEM_CLOCK_FREQUENCY / 16;
		break;
	default:
		*pu32Freq	=	0;
		return E_NOK;
		break;
	}
	return E_OK;
}
/************************************************************************************************************* */

static void RCC_vClockSource(uint8 Copy_xClock)
{
	/*First clear configuration bits*/
	CLEAR_BIT(RCC->CFGR,0);
	CLEAR_BIT(RCC->CFGR,1);

	/*Choose clock source*/
	switch(Copy_xClock)
	{
	/* Internal clock*/
	case RCC_HSI:
		/*Set HSION BIT*/
		SET_BIT(RCC->CR,0);

		/*Wait until the clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,1));

		/* Select HSI as clock source */
		CLEAR_BIT(RCC->CFGR,0);
		CLEAR_BIT(RCC->CFGR,1);
		break;

		/*External clock*/
	case RCC_HSE:
		/* Set HSEON BIT */
		SET_BIT(RCC->CR,16);
		/* Check if Bypass is on */
#if RCC_HSE_BYPASS == HSE_BYPASS_OFF_CRYSTAL
		CLEAR_BIT(RCC->CR,18);
#elif RCC_HSE_BYPASS == HSE_BYPASS_ON_RC
		SET_BIT(RCC->CR,18);
#endif

		/*Wait until external clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,17));

		/* Select HSE as clock source */
		SET_BIT(RCC->CFGR,0);
		CLEAR_BIT(RCC->CFGR,1);
		break;

		/*PLL clock*/
	case RCC_PLL:
		SET_BIT(RCC->CR,24);

		/*Wait until PLL clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,25));

		CLEAR_BIT(RCC->CFGR,0);
		SET_BIT(RCC->CFGR,1);
		break;

		/*Wrong choice -> HSI will be used */
	default:
		/*Set HSION BIT*/
		SET_BIT(RCC->CR,0);

		/*Wait until the clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,1));

		/* Select HSI as clock source */
		CLEAR_BIT(RCC->CFGR,0);
		CLEAR_BIT(RCC->CFGR,1);
		break;

	}
}

/************************************************************************************************************* */
Error_Status RCC_xSetADC_PreScaler(uint32 Copy_u32Prescaler)
{
	if(RCC_IS_VALID_ADC_PRESCALER(Copy_u32Prescaler) != E_OK)
	{
		return E_NOK;
	}
	RCC->CFGR |= Copy_u32Prescaler;

	return E_OK;
}

/************************************************************************************************************* */
/*Local functions*/
/************************************************************************************************************* */

static void RCC_vPLL_Clock_Source(uint8 Copy_xPLL_Source)
{
	/* First Clear selection Bits */
	CLEAR_BIT(RCC->CFGR,17);
	CLEAR_BIT(RCC->CFGR,16);

	switch(Copy_xPLL_Source)
	{
	case PLL_SRC_HSE_NOT_DEVIDED:
		/* Set HSEON BIT */
		SET_BIT(RCC->CR,16);
		/*Wait until external clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,17));

		/*Select HSE as PLL source*/
		CLEAR_BIT(RCC->CFGR,17);
		SET_BIT(RCC->CFGR,16);
		/*Wait until external clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,17));
		break;
	case PLL_SRC_HSE_DEVIDED_BY_2:
		/* Set HSEON BIT */
		SET_BIT(RCC->CR,16);
		/*Wait until external clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,17));

		/*Select HSE as PLL source*/
		SET_BIT(RCC->CFGR,17);
		SET_BIT(RCC->CFGR,16);
		/*Wait until external clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,17));
		break;
	case PLL_SRC_HSI_DEVIDED_BY_2:
		/*Set HSION BIT*/
		SET_BIT(RCC->CR,0);

		/*Wait until the clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,1));

		CLEAR_BIT(RCC->CFGR,16);
		break;
	default:
		/* In case of errors make the default clock source for PLL is internal clock */
		/*Set HSION BIT*/
		SET_BIT(RCC->CR,0);

		/*Wait until the clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,1));

		break;


	}
}

/************************************************************************************************************* */

static void RCC_vPLL_Mul(uint8 Copy_xMul_Factor)
{
	RCC->CFGR |= (Copy_xMul_Factor << 18);
}

/************************************************************************************************************* */
static void RCC_vBus_Prescaler(RCC_Config_t *Copy_RCC_Config)
{
	if(Copy_RCC_Config == (void*)0)
	{
		return;
	}
	/* Save the APB1 prescaler */
	APB1Prescaler	=	Copy_RCC_Config->Prescaler.ABP1_Prescaler;
	APB2Prescaler	=	Copy_RCC_Config->Prescaler.ABP2_Prescaler;
	AHBPrescaler	=	Copy_RCC_Config->Prescaler.AHB_Prescaler;

	RCC->CFGR |= ((Copy_RCC_Config->Prescaler.AHB_Prescaler) << 4);
	RCC->CFGR |= ((Copy_RCC_Config->Prescaler.ABP1_Prescaler) << 8);
	RCC->CFGR |= ((Copy_RCC_Config->Prescaler.ABP2_Prescaler) << 11);

}


