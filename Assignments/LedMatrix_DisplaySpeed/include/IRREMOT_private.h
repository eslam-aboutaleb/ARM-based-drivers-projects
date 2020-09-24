/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 1-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef IRREMOTE_PRIVATE_H
#define IRREMOTE_PRIVATE_H

/*Bits limits according to NEC protocol for IR*/

/*IR Remote Start bit time limits*/
#define IRREMOTE_START_BIT_LIMIT_1ST					10000
#define IRREMOTE_START_BIT_LIMIT_2ND					14000

/*IR Remote high bits time limits*/
#define IRREMOTE_HIGH_BIT_LIMIT_1ST						2000
#define IRREMOTE_HIGH_BIT_LIMIT_2ND						2300

/*IR Remote data macros*/
#define IRREMOTE_DATA_SIZE								8
#define IRREMOTE_DATA_START_INDEX						17

/************************************************************************************************************* */

/*Helper macros*/
/*Abstraction macro for external interrupt*/
#define IRREMOTE_EN_EX_INT()							 EXTI_vSetSignalLatch(IRREMOTE_EXTI_LINE,EXTI_TRIGGER_FALLING_EDGE)

/*Abstraction macros for timer functions*/
#define IRREMOTE_GET_ELAPSED_TIME()                      STK_u32GetElapsedTime(SYSTICK_TICKS_US)
#define IRREMOTE_SINGLE_INTERVAL(FRAME_T_MS,FRAME_TASK)	 STK_vSetIntervalSingle(FRAME_T_MS,SYSTICK_TICKS_MS,FRAME_TASK)

/*Check if is it valid start bit*/
#define IRREMOTE_CHECK_START_BIT(START_BIT)			    ((START_BIT >= IRREMOTE_START_BIT_LIMIT_1ST) && \
														(START_BIT <= IRREMOTE_START_BIT_LIMIT_2ND))

/*Check if bit time stamp is high or not*/
#define IRREMOTE_CHECK_BIT_STATE(BIT)                   ((BIT >= IRREMOTE_HIGH_BIT_LIMIT_1ST) && \
														(BIT <= IRREMOTE_HIGH_BIT_LIMIT_2ND))


/************************************************************************************************************* */

/*Local functions prototypes*/
static void IRREMOTE_u8TakeAction (void);
static uint8 IRREMOTE_u8CheckButton(uint8 Copy_u8Button);


#endif /*IRREMOTE_PRIVATE_H*/
