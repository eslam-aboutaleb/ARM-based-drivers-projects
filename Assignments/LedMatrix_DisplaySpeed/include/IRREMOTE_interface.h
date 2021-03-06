/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 1-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef IRREMOTE_INTERFACE_H
#define IRREMOTE_INTERFACE_H

typedef enum
{
	IRREMOTE_POWER = 69,
	IRREMOTE_MODE = 70,
	IRREMOTE_MUTE = 71,
	IRREMOTE_PLAY = 68,
	IRREMOTE_BACKWARD = 64,
	IRREMOTE_FORWARD = 67,
	IRREMOTE_EQ = 7,
	IRREMOTE_VOLDOWN = 21,
	IRREMOTE_VOLUP = 9,
	IRREMOTE_0 = 45,
	IRREMOTE_RPT = 25,
	IRREMOTE_SCN = 13,
	IRREMOTE_1 = 12,
	IRREMOTE_2 = 24,
	IRREMOTE_3 = 94,
	IRREMOTE_4 = 8,
	IRREMOTE_5 = 28,
	IRREMOTE_6 = 90,
	IRREMOTE_7 = 66,
	IRREMOTE_8 = 82,
	IRREMOTE_9 = 74,
}IRREMOTE_Buttons;

/* Public functions prototypes*/
void IRREMOTE_vInit(void);
void IRREMOTE_vEnableExInt(void);
uint8 IRREMOTE_u8GetFrame(void);
void IRREMOTE_SetButtonFunc(IRREMOTE_Buttons Copy_xButton , void (*vpFunc)(void));


#endif /*IRREMOTE_INTERFACE_H*/
