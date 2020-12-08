/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 28-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "LED_interface.h"
#include "SYSTICK_interface.h"
#include "LedAnim_interface.h"


int main()
{
	/*Configure system clock*/
	RCC_Config_t RCC_Copy;
	RCC_Copy.ClockSource = RCC_HSE;
	RCC_Copy.Prescaler.ABP1_Prescaler = APB1_NOT_DEVIDED;
	RCC_Copy.Prescaler.ABP2_Prescaler = APB2_NOT_DEVIDED;
	RCC_Copy.Prescaler.AHB_Prescaler  = AHB_NOT_DEVIDED;
	RCC_vClockInit(&RCC_Copy);

	/*Initialize GPIOA peripheral*/
	RCC_vSetCLKPeripheral(RCC_APB2_BUS,RCC_GPIOA_CLOCK,RCC_ENABLE_PERIPHERAL);
	/*Initialize Sysyick*/
	STK_vInit(STK_CLK_SRC_AHB_DIVIDED_BY_8);

	/*Initialize LEDS*/
	LED_vInit(LED_1,LED_OFF);
	LED_vInit(LED_2,LED_OFF);
	LED_vInit(LED_3,LED_OFF);
	LED_vInit(LED_4,LED_OFF);
	LED_vInit(LED_5,LED_OFF);
	LED_vInit(LED_6,LED_OFF);
	LED_vInit(LED_7,LED_OFF);
	LED_vInit(LED_8,LED_OFF);

	/*Start application periodic task with Systick every 100 ms */
	STK_vSetIntervalPeriodic(100 ,SYSTICK_TICKS_MS, LedAnim_vUpdate);



	while(1)
	{
		/*No action*/
	}
	return 0 ;
}
