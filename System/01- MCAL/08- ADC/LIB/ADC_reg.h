/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: ADC_reg.h			                                                 */
/* Version	: V01                                                                */
/* Date		: 16 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef ADC_REG_H_
#define ADC_REG_H_
/************************************************************************************************************* */

#define ADC1_BASE_ADDRESS								0x40012400
#define ADC2_BASE_ADDRESS								0x40012800
#define ADC3_BASE_ADDRESS								0x40013C00

/************************************************************************************************************* */

typedef struct
{
  volatile uint32 SR;
  volatile uint32 CR1;
  volatile uint32 CR2;
  volatile uint32 SMPR1;
  volatile uint32 SMPR2;
  volatile uint32 JOFR1;
  volatile uint32 JOFR2;
  volatile uint32 JOFR3;
  volatile uint32 JOFR4;
  volatile uint32 HTR;
  volatile uint32 LTR;
  volatile uint32 SQR1;
  volatile uint32 SQR2;
  volatile uint32 SQR3;
  volatile uint32 JSQR;
  volatile uint32 JDR1;
  volatile uint32 JDR2;
  volatile uint32 JDR3;
  volatile uint32 JDR4;
  volatile uint32 DR;
} ADC_TypeDef;

/************************************************************************************************************* */

#define ADC1												((ADC_TypeDef*)ADC1_BASE_ADDRESS)
#define ADC2												((ADC_TypeDef*)ADC2_BASE_ADDRESS)
#define ADC3												((ADC_TypeDef*)ADC3_BASE_ADDRESS)

#endif /* ADC_REG_H_ */

