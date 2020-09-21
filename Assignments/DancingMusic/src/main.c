#include <string.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "DAC_interface.h"
#include "Timer_interface.h"
#include "LedMTRX_interface.h"
#include "NVIC_interface.h"

#include "SYSTICK_interface.h"
#include "abyusif.h"


void Func(void)
{
	DAC_vConvert(ab_raw,ab_raw_len);
}
void RCC_Init(void)
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
	RCC_vSetCLKPeripheral(RCC_APB2_BUS,RCC_GPIOB_CLOCK,RCC_ENABLE_PERIPHERAL);
	RCC_vSetCLKPeripheral(RCC_APB2_BUS,RCC_TIM1_CLOCK,RCC_ENABLE_PERIPHERAL);
}

void TimInit(void)
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
	/*Initialize Timer*/
	TIM_vInit(TIMER1,&Timer);
}

uint8 Dance[] = {24, 150, 126, 150, 48, 0, 0, 0, 48, 150, 126, 150, 24, 0, 0, 0, 16, 150, 126, 150, 16, 0, 0, 0, 152, 86, 62, 86, 152, 0, 0, 0};

int main()
{
	RCC_Init();

	/*Initialize Sysyick*/
	STK_vInit(STK_CLK_SRC_AHB_DIVIDED_BY_8);
	DAC_vInit();
	TimInit();
	LedMtrx_vInit();
	STK_vSetIntervalPeriodic(125,SYSTICK_TICKS_US,Func);

	while(1)
	{
		LedMtrx_vDisplayShapes(Dance,3);
	}
}
