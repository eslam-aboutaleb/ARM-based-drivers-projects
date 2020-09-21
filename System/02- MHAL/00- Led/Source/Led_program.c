/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "LED_interface.h"
#include "LED_config.h"

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/*Functions definitions*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


void LED_vInit(tLED Copy_xLed, tLED_State Copy_xState)
{/* Configure led pins as output */
	switch (Copy_xLed)
	{
	case LED_1:
		GPIO_vInitPortPin(LED_1_PORT_CR, LED_1_PIN, GPIO_OUT);
		break;
	case LED_2:
		GPIO_vInitPortPin(LED_2_PORT_CR, LED_2_PIN, GPIO_OUT);
		break;
	default:
		/* No Thing */
		break;
	}
	/* Set led state */
	LED_vSetState(Copy_xLed, Copy_xState);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

void LED_Toggle(tLED Copy_xLed)
{
	/* Toggle led */
	if (LED_xGetState(Copy_xLed) == LED_ON)
	{
		LED_vSetState(Copy_xLed, LED_OFF);
	} else
	{
		LED_vSetState(Copy_xLed, LED_ON);
	}

}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


void LED_vSetState(tLED Copy_xLed, tLED_State Copy_xState)
{
	/* Set led state */
	switch (Copy_xLed)
	{
	case LED_1:
		GPIO_vWritePortPin(LED_1_PORT_DR, LED_1_PIN, Copy_xState);
		break;
	case LED_2:
		GPIO_vWritePortPin(LED_2_PORT_DR, LED_2_PIN, Copy_xState);
		break;
	default:
		/* No Thing */
		break;
	}
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


tLED_State LED_xGetState(tLED Copy_xLed)
{
	tLED_State ret = LED_OFF;

	/* Set led state */
	switch (Copy_xLed)
	{
	case LED_1:
		ret = GPIO_u8ReadPortPin(LED_1_PORT_DR, LED_1_PIN);
		break;
	case LED_2:
		ret = GPIO_u8ReadPortPin(LED_2_PORT_DR, LED_2_PIN);
		break;
	default:
		/* No Thing */
		break;
	}
	return ret;
}
