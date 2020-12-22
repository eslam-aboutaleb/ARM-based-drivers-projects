/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: CRC_private.h		                                                 */
/* Version	: V01                                                                */
/* Date		: 23 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef CRC_PRIVATE_H_
#define CRC_PRIVATE_H_

/*******************  Bit definition for CRC_DR register  *********************/
#define  CRC_DR_DR                           ((uint32)0xFFFFFFFF) /*! Data register bits */


/*******************  Bit definition for CRC_IDR register  ********************/
#define  CRC_IDR_IDR                         ((uint8)0xFF)        /* General-purpose 8-bit data register bits */


/********************  Bit definition for CRC_CR register  ********************/
#define  CRC_CR_RESET                        ((uint8)0x01)        /* RESET bit */


#endif
