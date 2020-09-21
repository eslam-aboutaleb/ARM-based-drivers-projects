/*////////////////////////////////////////////////////////////////////////////// */
/* Author:  Eslam Ehab Aboutaleb                                                 */
/* File:  	SYSTICK_private.h                                                    */
/* Version: V01                                                                  */
/* Date:    28-8-2020                                                            */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#define SYSTICK_BASE_ADDRESS			  (0xE000E010)
/************************************************************************************************************* */

/*Systick registers*/
typedef struct
{
  volatile uint32 CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  volatile uint32 LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  volatile uint32 VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  volatile uint32 CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_TypeDef;

/************************************************************************************************************* */

#define SYSTICK    				         ((SysTick_TypeDef *)	SYSTICK_BASE_ADDRESS	)

/************************************************************************************************************* */


/* Helper macros */
/*Systick Exception macros*/
#define STK_ENABLE_EXCEPTION()	             		SYSTICK->CTRL  |=  (1 << 1)
#define STK_DISABLE_EXCEPTION()            			SYSTICK->CTRL  &= ~(1 << 1)

/*Systick counter state macros*/
#define STK_START_COUNTER()               		 	SYSTICK->CTRL  |=  (1 << 0)
#define STK_STOP_COUNTER()                 			SYSTICK->CTRL  &= ~(1 << 0)

/* Syctick registers reset macro*/
#define STK_CLEAR_REGISTERS()                       SYSTICK->LOAD = 0;\
													SYSTICK->VAL  = 0

/* Systick update load register vlue macro*/
#define STK_UPDATE_LOAD_REGISTER(STK_TICKS)      	SYSTICK->LOAD = STK_TICKS

#define STK_BUSY_WAIT_FLAG()						while((GET_BIT(SYSTICK->CTRL,16))== 0)

#endif /*SYSTICK_PRIVATE_H*/
