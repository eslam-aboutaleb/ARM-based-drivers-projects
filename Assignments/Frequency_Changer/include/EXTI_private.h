#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

#define EXTI_BASE_ADDRESS										0x40010400

typedef struct
{
  volatile uint32 IMR;
  volatile uint32 EMR;
  volatile uint32 RTSR;
  volatile uint32 FTSR;
  volatile uint32 SWIER;
  volatile uint32 PR;
}EXTI_TypeDef;

#define EXTI          				  	 ((EXTI_TypeDef*)EXTI_BASE_ADDRESS)



#endif /* EXTI_PRIVATE_H */ 
