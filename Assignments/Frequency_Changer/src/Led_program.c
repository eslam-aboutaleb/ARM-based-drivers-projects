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

/************************************************************************************************************* */
/*Functions definitions*/
/************************************************************************************************************* */

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
	case LED_3:
		GPIO_vInitPortPin(LED_3_PORT_CR, LED_3_PIN, GPIO_OUT);
		break;
	case LED_4:
		GPIO_vInitPortPin(LED_4_PORT_CR, LED_4_PIN, GPIO_OUT);
		break;
	case LED_5:
		GPIO_vInitPortPin(LED_5_PORT_CR, LED_5_PIN, GPIO_OUT);
		break;
	case LED_6:
		GPIO_vInitPortPin(LED_6_PORT_CR, LED_6_PIN, GPIO_OUT);
		break;
	case LED_7:
		GPIO_vInitPortPin(LED_7_PORT_CR, LED_7_PIN, GPIO_OUT);
		break;
	case LED_8:
		GPIO_vInitPortPin(LED_8_PORT_CR, LED_8_PIN, GPIO_OUT);
		break;
	default:
		/* No Thing */
		break;
	}
	/* Set led state */
	LED_vSetState(Copy_xLed, Copy_xState);
}

/************************************************************************************************************* */

void LED_vToggle(tLED Copy_xLed)
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

/************************************************************************************************************* */


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
	case LED_3:
		GPIO_vWritePortPin(LED_3_PORT_DR, LED_3_PIN, Copy_xState);
		break;
	case LED_4:
		GPIO_vWritePortPin(LED_4_PORT_DR, LED_4_PIN, Copy_xState);
		break;
	case LED_5:
		GPIO_vWritePortPin(LED_5_PORT_DR, LED_5_PIN, Copy_xState);
		break;
	case LED_6:
		GPIO_vWritePortPin(LED_6_PORT_DR, LED_6_PIN, Copy_xState);
		break;
	case LED_7:
		GPIO_vWritePortPin(LED_7_PORT_DR, LED_7_PIN, Copy_xState);
		break;
	case LED_8:
		GPIO_vWritePortPin(LED_8_PORT_DR, LED_8_PIN, Copy_xState);
		break;

	default:
		/* No Thing */
		break;
	}
}

/************************************************************************************************************* */


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
	case LED_3:
		ret = GPIO_u8ReadPortPin(LED_3_PORT_DR, LED_3_PIN);
		break;
	case LED_4:
		ret = GPIO_u8ReadPortPin(LED_4_PORT_DR, LED_4_PIN);
		break;
	case LED_5:
		ret = GPIO_u8ReadPortPin(LED_5_PORT_DR, LED_5_PIN);
		break;
	case LED_6:
		ret = GPIO_u8ReadPortPin(LED_6_PORT_DR, LED_6_PIN);
		break;
	case LED_7:
		ret = GPIO_u8ReadPortPin(LED_7_PORT_DR, LED_7_PIN);
		break;
	case LED_8:
		ret = GPIO_u8ReadPortPin(LED_8_PORT_DR, LED_8_PIN);
		break;

	default:
		/* No Thing */
		break;
	}
	return ret;
}
