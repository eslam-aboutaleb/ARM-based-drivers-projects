/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 1-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

/************************************************************************************************************* */
/*LED data structures*/
/************************************************************************************************************* */

typedef enum
{
	LED_1 = 0,
	LED_2,
	LED_3,
	LED_4,
	LED_5,
	LED_6,
	LED_7,
	LED_8
}tLED;

typedef enum
{
	LED_OFF = 0,
	LED_ON  = 1
}tLED_State;

/************************************************************************************************************* */
/*Functions prototypes**/
/************************************************************************************************************* */

void LED_vInit(tLED Copy_xLed, tLED_State Copy_xState);
void LED_vSetState(tLED Copy_xLed, tLED_State Copy_xState);
void LED_vToggle(tLED Copy_xLed);
tLED_State LED_xGetState(tLED Copy_xLed);




#endif /* LED_INTERFACE_H */
