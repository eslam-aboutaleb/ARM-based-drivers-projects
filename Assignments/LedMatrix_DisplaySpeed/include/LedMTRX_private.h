/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 1-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef LED_MTRX_PRIVATE_H
#define LED_MTRX_PRIVATE_H

#define LEDMTRX_DATA_BITSIZE						((sizeof(char) *8) - 1)

#define COLS_CATHODE                   0
#define COLS_ANODE                     1

#define ROWS_CATHODE				   0
#define ROWS_ANODE                     1

/*Abstract delay function*/
#define LedMtrx_vDelay(DelayUS)				TIM_vSetBusyWait(TIMER1,DelayUS, TIM_TICKS_US)


static void LedMtrx_vSetRowVals(uint8 Copy_u8Val);
static void LedMtrx_vSetCol(uint8 Copy_u8ColNum);

#endif
