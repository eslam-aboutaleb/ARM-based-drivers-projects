/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

/************************************************************************************************************* */
/*Ports base addresses*/
/************************************************************************************************************* */

#define GPIOA_BASE_ADDRESS       0x40010800
#define GPIOB_BASE_ADDRESS       0x40010C00
#define GPIOC_BASE_ADDRESS       0x40011000
#define GPIOD_BASE_ADDRESS       0x40011400
#define GPIOE_BASE_ADDRESS       0x40011800

/************************************************************************************************************* */
/*GPIO registers*/
/************************************************************************************************************* */


/* General Purpose I/O Registers */
typedef struct
{
	volatile uint32 CRL;
	volatile uint32 CRH;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 BRR;
	volatile uint32 LCKR;
} GPIO_TypeDef;

/************************************************************************************************************* */

/*PORTS*/
#define GPIOA_REG                ((GPIO_TypeDef   *) GPIOA_BASE_ADDRESS   )
#define GPIOB_REG                ((GPIO_TypeDef   *) GPIOB_BASE_ADDRESS   )
#define GPIOC_REG                ((GPIO_TypeDef   *) GPIOC_BASE_ADDRESS   )
#define GPIOD_REG                ((GPIO_TypeDef   *) GPIOD_BASE_ADDRESS   )
#define GPIOE_REG                ((GPIO_TypeDef   *) GPIOE_BASE_ADDRESS   )



#endif


