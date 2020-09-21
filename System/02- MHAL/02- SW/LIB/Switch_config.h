/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef SWITCH_CONFIG_H
#define SWITCH_CONFIG_H

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/*SW configuration macros*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


/* SW voltage level */
#define SW_PRESSED_LEVEL        (0)
#define SW_RELEASED_LEVEL       (1)

/* Number of samples per SW */
#define SW_N_SAMPLES      (2)


#define SW_N_SWITCHES     (2)

#define SW_MINUS_PORT_DR        (GPIOA)
#define SW_MINUS_PORT_CR        (GPIOA)
#define SW_MINUS_PIN            (GPIO_PIN_9)

#define SW_PLUS_PORT_DR         (GPIOA)
#define SW_PLUS_PORT_CR         (GPIOA)
#define SW_PLUS_PIN             (GPIO_PIN_8)


#endif
