/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef SSD_PORT_H
#define SSD_PORT_H

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/*SSD macros*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

/* Multiplexing states of SSDs*/
#define SSD_MULTIPLEXING_OFF    (0)
#define SSD_MULTIPLEXING_ON     (1)

/* To choose Multiplexing state:
 *
 * Options:
 * 1- SSD_Multiplexing_OFF
 * 2- SSD_Multiplexing_ON
 */
#define SSD_MULTIPLEXING_STATE        SSD_MULTIPLEXING_OFF

/* SSD Data port*/
#define SSD_DATA_PIN_1_PORT_DR        (GPIOA)
#define SSD_DATA_PIN_1_PORT_CR        (GPIOA)
#define SSD_DATA_PIN_2_PORT_DR        (GPIOA)
#define SSD_DATA_PIN_2_PORT_CR        (GPIOA)
#define SSD_DATA_PIN_3_PORT_DR        (GPIOA)
#define SSD_DATA_PIN_3_PORT_CR        (GPIOA)
#define SSD_DATA_PIN_4_PORT_DR        (GPIOA)
#define SSD_DATA_PIN_4_PORT_CR        (GPIOA)
#define SSD_DATA_PIN_5_PORT_DR        (GPIOA)
#define SSD_DATA_PIN_5_PORT_CR        (GPIOA)
#define SSD_DATA_PIN_6_PORT_DR        (GPIOA)
#define SSD_DATA_PIN_6_PORT_CR        (GPIOA)
#define SSD_DATA_PIN_7_PORT_DR        (GPIOA)
#define SSD_DATA_PIN_7_PORT_CR        (GPIOA)
#define SSD_DATA_PIN_8_PORT_DR        (GPIOA)
#define SSD_DATA_PIN_8_PORT_CR        (GPIOA)


/*SSD Data pins*/
#define SSD_PIN_1               (GPIO_PIN_0)
#define SSD_PIN_2               (GPIO_PIN_1)
#define SSD_PIN_3               (GPIO_PIN_2)
#define SSD_PIN_4               (GPIO_PIN_3)
#define SSD_PIN_5               (GPIO_PIN_4)
#define SSD_PIN_6               (GPIO_PIN_5)
#define SSD_PIN_7               (GPIO_PIN_6)
#define SSD_PIN_8               (GPIO_PIN_7)


/*Only use this configurations if SSD Multiplexing state is on = SSD_Multiplexing_ON*/
#if(SSD_MULTIPLEXING_STATE == SSD_MULTIPLEXING_ON)

/*SSD Control Configuration */
#define SSD_CONTROL_ONE_PORT_DR        (GPIOB)
#define SSD_CONTROL_ONE_PORT_CR        (GPIOB)
#define SSD_CONTROL_ONE_PORT_PIN       (GPIO_PIN_7)

#define SSD_CONTROL_TWO_PORT_DR        (GPIOB)
#define SSD_CONTROL_TWO_PORT_CR        (GPIOB)
#define SSD_CONTROL_TWO_PORT_PIN       (GPIO_PIN_6)

#endif

/* Number of SSD symbols */
#define N_SSD_SYMBOLS   (11)


/* SSD Symbols port data values */
static uint8 SSD_Data[N_SSD_SYMBOLS] =
{
		0b00111111, /* SSD_0 */
		0b00000110, /* SSD_1 */
		0b01011011, /* SSD_2 */
		0b01001111, /* SSD_3 */
		0b01100110, /* SSD_4 */
		0b01101101, /* SSD_5 */
		0b01111101, /* SSD_6 */
		0b00000111, /* SSD_7 */
		0b01111111, /* SSD_8 */
		0b01101111, /* SSD_9 */
		0b00000000, /* SSD_NULL */
};

#endif
