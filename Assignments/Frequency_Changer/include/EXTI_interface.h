#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H


/*EXTI LINEs*/
#define EXTI_LINE0     								   0   /*!< External interrupt LINE 0 */
#define EXTI_LINE1                                     1   /*!< External interrupt LINE 1 */
#define EXTI_LINE2                                     2   /*!< External interrupt LINE 2 */
#define EXTI_LINE3                                     3   /*!< External interrupt LINE 3 */
#define EXTI_LINE4                                     4   /*!< External interrupt LINE 4 */
#define EXTI_LINE5                                     5   /*!< External interrupt LINE 5 */
#define EXTI_LINE6                                     6   /*!< External interrupt LINE 6 */
#define EXTI_LINE7                                     7   /*!< External interrupt LINE 7 */
#define EXTI_LINE8                                     8   /*!< External interrupt LINE 8 */
#define EXTI_LINE9                                     9   /*!< External interrupt LINE 9 */
#define EXTI_LINE10                                    10  /*!< External interrupt LINE 10 */
#define EXTI_LINE11                                    11  /*!< External interrupt LINE 11 */
#define EXTI_LINE12                                    12  /*!< External interrupt LINE 12 */
#define EXTI_LINE13                                    13  /*!< External interrupt LINE 13 */
#define EXTI_LINE14                                    14  /*!< External interrupt LINE 14 */
#define EXTI_LINE15                                    15  /*!< External interrupt LINE 15 */
#define EXTI_LINE16                                    16  /*!< External interrupt LINE 16 Connected to the PVD Output */
#define EXTI_LINE17                                    17  /*!< External interrupt LINE 17 Connected to the RTC Alarm event */
#define EXTI_LINE18                                    18  /*!< External interrupt LINE 18 Connected to the USB Device/USB OTG FS
                                                                                  Wakeup from suspend event */
#define EXTI_LINE19                                    19  /*!< External interrupt LINE 19 Connected to the Ethernet Wakeup event */

#define EXTI_TRIGGER_FALLING_EDGE          				0
#define EXTI_TRIGGER_RISING_EDGE						1
#define EXTI_TRIGGER_ON_CHANGE							2

void EXTI_vSetSignalLatch(uint8 Copy_u8EXTI_Line , uint8 Copy_u8EXTI_TrigerMode);
void EXTI_vDeInit(void);
void EXTI_vEnableEXTI(uint8 Copy_u8EXTI_Line);

void EXTI_vSetCallBack(uint8 Copy_u8EXTI_Line, void(*Copy_vFuncPtr)(void));
#endif
