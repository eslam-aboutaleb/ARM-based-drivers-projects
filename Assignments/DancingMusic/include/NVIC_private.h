/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 20-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

#define NVIC_BASE_ADDRESS 0xE000E100

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

/*NVIC registers*/
typedef struct
{
	volatile uint32 ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
	uint32 RESERVED0[24U];
	volatile uint32 ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
	uint32 RSERVED1[24U];
	volatile uint32 ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
	uint32 RESERVED2[24U];
	volatile uint32 ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
	uint32 RESERVED3[24U];
	volatile uint32 IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
	uint32 RESERVED4[56U];
	volatile uint8  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
	uint32 RESERVED5[644U];
	volatile  uint32 STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}NVIC_TypeDef;


#define NVIC                ((NVIC_TypeDef*)NVIC_BASE_ADDRESS)


#endif /*NVIC_PRIVATE_H*/
