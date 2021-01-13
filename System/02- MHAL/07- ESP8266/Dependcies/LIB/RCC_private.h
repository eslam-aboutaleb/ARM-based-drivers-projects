/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */


#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H
/************************************************************************************************************* */
/* RCC Errors checkers */
#define RCC_IS_VALID_ADC_PRESCALER(Prescaler)						((Prescaler == RCC_ADC_PRESCALER_2)|| \
																	(Prescaler == RCC_ADC_PRESCALER_4)|| \
																	(Prescaler == RCC_ADC_PRESCALER_6)|| \
																	(Prescaler == RCC_ADC_PRESCALER_4))

/************************************************************************************************************* */
/* Local functions prototypes */
/************************************************************************************************************* */

static void RCC_vClockSource(uint8 Copy_xClock);
static void RCC_vPLL_Clock_Source(uint8 Copy_xPLL_Source);
static void RCC_vPLL_Mul(uint8 Copy_xMul_Factor);
static void RCC_vBus_Prescaler(RCC_Config_t *Copy_RCC_Config);


#endif
