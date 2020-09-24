/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Date: 1-9-2020                                                                */
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

#include "ECUM.h"

uint8 MyName[] = {127, 73, 73, 0, 79, 73, 121, 0, 127, 64, 64, 64, 0, 127, 17, 17, 127, 0, 127, 1, 127, 1, 127, 0, 0, 0, 0, 0, 0, 0};

int main()
{
	/* Initialize RCC */
	ECUM_vRCC_Init();
	/* Initialize Timer */
	ECUM_vTimInit();
	/* Assign remote buttons tasks */
	IRREMOTE_SetButtonFunc(IRREMOTE_FORWARD , ECUM_vIR_ForwardFunc);
	IRREMOTE_SetButtonFunc(IRREMOTE_BACKWARD , ECUM_vIR_BackwardFunc);
	/* Initialize Remote */
	ECUM_vIRRemote_Init();
	/* Initialize Led matrix */
	LedMtrx_vInit();
	/* Initialize SysTick */
	STK_vInit(STK_CLK_SRC_AHB_DIVIDED_BY_8);
	while(1)
	{
		LedMtrx_vDisplayLine(MyName,30);
	}
	return 0 ;
}


