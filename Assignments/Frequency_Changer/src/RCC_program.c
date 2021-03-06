/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_private.h"
#include "RCC_interface.h"
#include "RCC_config.h"

/************************************************************************************************************* */
/* Local functions prototypes */
/************************************************************************************************************* */

static void RCC_vClockSource(uint8 Copy_xClock);
static void RCC_vPLL_Clock_Source(uint8 Copy_xPLL_Source);
static void RCC_vPLL_Mul(uint8 Copy_xMul_Factor);
static void RCC_vBus_Prescaler(RCC_Config_t *Copy_RCC_Config);

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

uint8 RCC_xGetClkSource(void)
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

	return -1; /*Failed*/
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
		CLEAR_BIT(RCC->CFGR,17);
		/*Select HSE as PLL source*/
		SET_BIT(RCC->CFGR,16);
		/*Wait until external clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,17));
		break;
	case PLL_SRC_HSE_DEVIDED_BY_2:
		SET_BIT(RCC->CFGR,17);
		/*Select HSE as PLL source*/
		SET_BIT(RCC->CFGR,16);
		/*Wait until external clock is stable*/
		while(BIT_IS_CLEAR(RCC->CR,17));
		break;
	case PLL_SRC_HSI_DEVIDED_BY_2:
		CLEAR_BIT(RCC->CFGR,16);
		break;
	default:
		CLEAR_BIT(RCC->CFGR,16);
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
	RCC->CFGR |= ((Copy_RCC_Config->Prescaler.AHB_Prescaler) << 4);
	RCC->CFGR |= ((Copy_RCC_Config->Prescaler.ABP1_Prescaler) << 8);
	RCC->CFGR |= ((Copy_RCC_Config->Prescaler.ABP1_Prescaler) << 11);

}


