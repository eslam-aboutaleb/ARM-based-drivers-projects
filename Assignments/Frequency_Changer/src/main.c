/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 21-9-2020                                                               */
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
#include "IRREMOTE_interface.h"
#include "Timer_interface.h"
#include "DAC_interface.h"

#include "SoundM_interface.h"
#include "abyusif.h"

void Main_RCC_Init(void);
void Main_TimInit(void);
void Main_IRRemote_Init(void);

int main()
{
	/*Initialize RCC*/
	Main_RCC_Init();
	/*Initialize Timer*/
	Main_TimInit();
	/*Initialize remote buttons*/
	IRREMOTE_SetButtonFunc(IRREMOTE_FORWARD , SoundM_vIncFreq);
	IRREMOTE_SetButtonFunc(IRREMOTE_BACKWARD , SoundM_vDecFreq);
	/*Initialize Remote*/
	Main_IRRemote_Init();
	/*Initialize sound*/
	SoundM_u8Init(ab_raw,ab_raw_len,125);
	/*Initialize Systick*/
	STK_vInit(STK_CLK_SRC_AHB_DIVIDED_BY_8);
	while(1)
	{
		/*Check any changes in frequency*/
		SoundM_vUpdate();
	}
	return 0 ;
}


/*Init functions*/
void Main_TimInit(void)
{
	NVIC_u8EnableInterrupt(TIM1_UP_IRQnum);
	TIM_ConfigType Timer;
	memset(&Timer,0,sizeof(Timer));
	/*Enable Timer*/
	Timer.Counter_State=Enable_CNT;
	/*Initialize prescaler*/
	Timer.PrescalerVal = 8000;
	/*Initialize Timer as Down counter*/
	Timer.Direction_State = UpCounter;
	/*Enable Timer interrupt*/
	/*Initialize Timer*/
	TIM_vInit(TIMER1,&Timer);
}
void Main_RCC_Init(void)
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

void Main_IRRemote_Init(void)
{
	GPIO_vInitPortPin(GPIOA,GPIO_PIN_0,GPIO_PIN_INPUT_FLOATING_MODE);
	EXTI_vSetCallBack(EXTI_LINE0,(void*)IRREMOTE_u8GetFrame);
	AFIO_vEXTILineConfig(EXTI_LINE0,AFIO_PortSourceGPIOA);
	NVIC_u8EnableInterrupt(EXTI0_IRQnum);
	EXTI_vSetSignalLatch(EXTI_LINE0,EXTI_TRIGGER_FALLING_EDGE);
}
