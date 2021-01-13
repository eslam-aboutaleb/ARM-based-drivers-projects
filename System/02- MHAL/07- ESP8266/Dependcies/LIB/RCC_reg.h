/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef RCC_REG_H_
#define RCC_REG_H_

/*RCC base address*/
#define RCC_BASE_ADDRESS    0x40021000

/*RCC registers*/
typedef struct
{
  volatile uint32 CR;
  volatile uint32 CFGR;
  volatile uint32 CIR;
  volatile uint32 APB2RSTR;
  volatile uint32 APB1RSTR;
  volatile uint32 AHBENR;
  volatile uint32 APB2ENR;
  volatile uint32 APB1ENR;
  volatile uint32 BDCR;
  volatile uint32 CSR;

} RCC_TypeDef;


#define RCC ((RCC_TypeDef*) RCC_BASE_ADDRESS)


#endif /* RCC_REG_H_ */
