/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 1-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */
#include <string.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "SYSTICK_interface.h"
#include "EXTI_interface.h"
#include "NVIC_interface.h"
#include "AFIO_interface.h"
#include "LED_interface.h"
#include "IRREMOTE_interface.h"
#include "Timer_interface.h"
#include "LedMTRX_interface.h"

void ECUM_vTimInit(void)
{
	NVIC_u8EnableInterrupt(TIM1_UP_IRQnum);
	TIM_ConfigType Timer;
	memset(&Timer,0,sizeof(Timer));
	/*Enable Timer*/
	Timer.Counter_State=Enable_CNT;
	/*Initialize prescaler*/
	Timer.PrescalerVal = 8;
	/*Initialize Timer as Down counter*/
	Timer.Direction_State = UpCounter;
	/*Enable Timer interrupt*/
	/*Initialize Timer*/
	TIM_vInit(TIMER1,&Timer);
}
void ECUM_vRCC_Init(void)
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
	RCC_vSetCLKPeripheral(RCC_APB2_BUS,RCC_AFIO_CLOCK,RCC_ENABLE_PERIPHERAL);
}

void ECUM_vIRRemote_Init(void)
{
	GPIO_vInitPortPin(GPIOA,GPIO_PIN_0,GPIO_PIN_INPUT_FLOATING_MODE);
	EXTI_vSetCallBack(EXTI_LINE0,(void*)IRREMOTE_u8GetFrame);
	AFIO_vEXTILineConfig(EXTI_LINE0,AFIO_PortSourceGPIOA);
	NVIC_u8EnableInterrupt(EXTI0_IRQnum);
	EXTI_vSetSignalLatch(EXTI_LINE0,EXTI_TRIGGER_FALLING_EDGE);
}

void ECUM_vIR_ForwardFunc(void)
{
	LedMtrx_vSetSpeed(LEDMTRX_INCSPEED);
}

void ECUM_vIR_BackwardFunc(void)
{
	LedMtrx_vSetSpeed(LEDMTRX_DECSPEED);
}
