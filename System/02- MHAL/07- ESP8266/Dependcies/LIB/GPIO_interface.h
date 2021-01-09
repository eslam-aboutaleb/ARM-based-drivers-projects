/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "GPIO_private.h"

/************************************************************************************************************* */
/*GPIO Macros*/
/************************************************************************************************************* */

/*GPIO Mode settings values*/
#define GPIO_PIN_INPUT_ANALOG_MODE                        (0x0)
#define GPIO_PIN_INPUT_FLOATING_MODE                      (0x4)
#define GPIO_PIN_INPUT_PULLUP_DOWN_MODE                   (0x8)

/*For speed 10 MHZ*/
#define GPIO_PIN_GP_OUTPUT_PUSHPULL_MODE_10MHZ            (0x1)
#define GPIO_PIN_OUTPUT_OPENDRAIN_MODE_10MHZ              (0x5)
#define GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_10MHZ           (0x9)
#define GPIO_PIN_ALF_OUTPUT_OPENDRAIN_MODE_10MHZ          (0xD)

/*For speed 2 MHZ*/
#define GPIO_PIN_GP_OUTPUT_PUSHPULL_MODE_2MHZ             (0x2)
#define GPIO_PIN_OUTPUT_OPENDRAIN_MODE_2MHZ               (0x6)
#define GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_2MHZ            (0xA)
#define GPIO_PIN_ALF_OUTPUT_OPENDRAIN_MODE_2MHZ           (0xE)

/*For speed 50 MHZ*/
#define GPIO_PIN_GP_OUTPUT_PUSHPULL_MODE_50MHZ            (0x3)
#define GPIO_PIN_OUTPUT_OPENDRAIN_MODE_50MHZ              (0x7)
#define GPIO_PIN_ALF_OUTPUT_PUSHPULL_MODE_50MHZ           (0xB)
#define GPIO_PIN_ALF_OUTPUT_OPENDRAIN_MODE_50MHZ          (0xF)



/*GPIO Pins*/

#define GPIO_PIN_0                                        (0)
#define GPIO_PIN_1                                        (1)
#define GPIO_PIN_2                                        (2)
#define GPIO_PIN_3                                        (3)
#define GPIO_PIN_4                                        (4)
#define GPIO_PIN_5                                        (5)
#define GPIO_PIN_6                                        (6)
#define GPIO_PIN_7                                        (7)
#define GPIO_PIN_8                                        (8)
#define GPIO_PIN_9                                        (9)
#define GPIO_PIN_10                                       (10)
#define GPIO_PIN_11                                       (11)
#define GPIO_PIN_12                                       (12)
#define GPIO_PIN_13                                       (13)
#define GPIO_PIN_14                                       (14)
#define GPIO_PIN_15                                       (15)


/*GPIO Direction values*/
#define GPIO_OUT                                          (GPIO_PIN_GP_OUTPUT_PUSHPULL_MODE_10MHZ)
#define GPIO_IN                                           (GPIO_PIN_INPUT_PULLUP_DOWN_MODE)

/*GPIO Level values*/
#define GPIO_HIGH                                         (1)
#define GPIO_LOW                                          (0)

/*GPIO Lock options*/
#define GPIO_UNLCK                                        (0)
#define GPIO_LCK                                          (1)

typedef unsigned char										GPIO_Pin_t;
/************************************************************************************************************* */
/*GPIO shortcuts*/
/************************************************************************************************************* */

#define GPIO_Port_t										   GPIO_TypeDef*

/*GPIO ports*/
#define GPIOA                	                           GPIOA_REG
#define GPIOB                                              GPIOB_REG
#define GPIOC                                              GPIOC_REG
#define GPIOD                                              GPIOD_REG
#define GPIOE                 	                           GPIOE_REG

/* Shortcuts for direct using*/
#define GPIO_PORTA                                        (GPIOA->ODR)
#define GPIO_PINA                                         (GPIOA->IDR)

#define GPIO_PORTB                                        (GPIOB->ODR)
#define GPIO_PINB                                         (GPIOB->IDR)

#define GPIO_PORTC                                        (GPIOC->ODR)
#define GPIO_PINC                                         (GPIOC->IDR)

#define GPIO_PORTD                                        (GPIOD->ODR)
#define GPIO_PIND                                         (GPIOD->IDR)

#define GPIO_PORTE                                        (GPIOE->ODR)
#define GPIO_PINE                                         (GPIOE->IDR)


/************************************************************************************************************* */
/*GPIO data structure*/
/************************************************************************************************************* */

/* Data structure of initialization function */
typedef struct
{
	uint8 GPIO_PinNumber;
	uint32 GPIO_PinMode;
	uint32 GPIO_PinAltFuncMode;
}GPIO_ConfigType;

/************************************************************************************************************* */
/*Functions prototype*/
/************************************************************************************************************* */
void GPIO_vInitPortPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Mode);
void GPIO_vWritePortPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin ,uint8 Copy_u8Val);
uint8 GPIO_u8ReadPortPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin);
void GPIO_vLockPin(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin,uint8 Copy_u8LockState);
uint8 GPIO_u8ReadLockPinState(GPIO_TypeDef *GPIOx ,uint8 Copy_u8Pin);

#endif

