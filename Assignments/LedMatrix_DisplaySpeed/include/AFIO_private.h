/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date	  : 31-8-2020                                                            */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef AFIO_Private_H
#define AFIO_Private_H

#define AFIO_BASE_ADDRESS						     0x40010000

typedef struct
{
  volatile uint32 EVCR;
  volatile uint32 MAPR;
  volatile uint32 EXTICR[4];
  volatile uint32 RESERVED0;
  volatile uint32  MAPR2;
} AFIO_TypeDef;

#define AFIO              						     ((AFIO_TypeDef*)AFIO_BASE_ADDRESS)

#endif /* AFIO_Private_H */
