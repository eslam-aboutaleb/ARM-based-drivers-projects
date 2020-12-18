/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: I2C_interface.c		                                             */
/* Version	: V01                                                                */
/* Date		: 18 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef I2C_INTEFACE_H_
#define I2C_INTEFACE_H_

#include "I2C_reg.h"

/************************************************************************************************************* */

/* I2C duty cycle configuration parameters */
#define I2C_SM_NO_DUTY_CYCLE_CNFG			0				 /* No configuration for standard mode */
#define I2C_DUTY_CYCLE_16_9          	    ((uint16)0x4000) /* I2C fast mode Tlow/Thigh = 16/9 	*/
#define I2C_DUTY_CYCLE_2					((uint16)0xBFFF) /* I2C fast mode Tlow/Thigh = 2 	*/
/************************************************************************************************************* */

/* I2C modes configuration parameters */
#define I2C_MODE_I2C                   		((uint16)0x0000)
#define I2C_MODE_SM_BUS_DEVICE            	((uint16)0x0002)
#define I2C_MODE_SM_BUS_HOST              	((uint16)0x000A)
/************************************************************************************************************* */

#define I2C_ACK_ENABLE                  	((uint16)0x0400)
#define I2C_ACK_DISABLE                	 	((uint16)0x0000)
/************************************************************************************************************* */

#define I2C_ADDRESS_7BIT    				((uint16)0x4000)
#define I2C_ADDRESS_10BIT   				((uint16)0xC000)
/************************************************************************************************************* */

#define I2C_DUAL_ADDRESS_DISABLE        	((uint16)0x0000)
#define I2C_DUAL_ADDRESS_ENABLE         	((uint16)0x0001)
/************************************************************************************************************* */

#define  I2C_DIRECTION_TRANSMITTER      	((uint8)0x00)
#define  I2C_DIRECTION_RECEIVER         	((uint8)0x01)

/************************************************************************************************************* */

#define I2C_REGISTER_CR1                	((uint8)0x00)
#define I2C_REGISTER_CR2               		((uint8)0x04)
#define I2C_REGISTER_OAR1               	((uint8)0x08)
#define I2C_REGISTER_OAR2               	((uint8)0x0C)
#define I2C_REGISTER_DR               		((uint8)0x10)
#define I2C_REGISTER_SR1                	((uint8)0x14)
#define I2C_REGISTER_SR2                	((uint8)0x18)
#define I2C_REGISTER_CCR                	((uint8)0x1C)
#define I2C_REGISTER_TRISE              	((uint8)0x20)
/************************************************************************************************************* */

/* SR2 register flags*/

#define I2C_FLAG_DUALF                  ((uint32)0x00800000)
#define I2C_FLAG_SMBHOST                ((uint32)0x00400000)
#define I2C_FLAG_SMBDEFAULT             ((uint32)0x00200000)
#define I2C_FLAG_GENCALL                ((uint32)0x00100000)
#define I2C_FLAG_TRA                    ((uint32)0x00040000)
#define I2C_FLAG_BUSY                   ((uint32)0x00020000)
#define I2C_FLAG_MSL                    ((uint32)0x00010000)

/* SR1 register flags */

#define I2C_FLAG_SMBALERT               ((uint32)0x10008000)
#define I2C_FLAG_TIMEOUT                ((uint32)0x10004000)
#define I2C_FLAG_PECERR                 ((uint32)0x10001000)
#define I2C_FLAG_OVR                    ((uint32)0x10000800)
#define I2C_FLAG_AF                     ((uint32)0x10000400)
#define I2C_FLAG_ARLO                   ((uint32)0x10000200)
#define I2C_FLAG_BERR                   ((uint32)0x10000100)
#define I2C_FLAG_TXE                    ((uint32)0x10000080)
#define I2C_FLAG_RXNE                   ((uint32)0x10000040)
#define I2C_FLAG_STOPF                  ((uint32)0x10000010)
#define I2C_FLAG_ADD10                  ((uint32)0x10000008)
#define I2C_FLAG_BTF                    ((uint32)0x10000004)
#define I2C_FLAG_ADDR                   ((uint32)0x10000002)
#define I2C_FLAG_SB                     ((uint32)0x10000001)

/************************************************************************************************************* */

typedef struct
{
  uint32 I2C_ClockSpeed;          /* Specifies the clock frequency.
                                       This parameter must be set to a value lower than 400kHz */

  uint16 I2C_Mode;                /* Specifies the I2C mode. */
  uint16 I2C_DutyCycle;           /* Specifies the I2C fast mode duty cycle.*/

  uint16 I2C_AddressLength; 	  /* Specifies if 7-bit or 10-bit address is acknowledged. */

  uint16 I2C_OwnAddress1;         /* Specifies the first device own address.
                                       This parameter can be a 7-bit or 10-bit address. */

  uint16 I2C_DualAddressMode;		/* Configure dual mode */

  uint16 I2C_OwnAddress2;			 /* Specifies the second device own address.
                                       This parameter can be a 7-bits . */

  FunctionalState I2C_Ack;        /*!< Enables or disables the acknowledgement. */

}I2C_InitTypeDef;

/************************************************************************************************************* */
										/* I2C Functions prototypes */
/************************************************************************************************************* */

Error_Status I2C_xInit(I2C_TypeDef* I2Cx , I2C_InitTypeDef *pxI2C_Cnfg);
/************************************************************************************************************* */

Error_Status I2C_xSetState(I2C_TypeDef* I2Cx , FunctionalState Copy_xI2C_State);
/************************************************************************************************************* */

Error_Status I2C_xGenerateStart(I2C_TypeDef* I2Cx, FunctionalState Copy_xStartState);
/************************************************************************************************************* */

Error_Status I2C_xSetACK(I2C_TypeDef* I2Cx ,FunctionalState Copy_xACK_State);
/************************************************************************************************************* */

Error_Status I2C_xCnfgClockStretch(I2C_TypeDef* I2Cx, FunctionalState Copy_xClkStretchState);
/************************************************************************************************************* */

Error_Status I2C_xSetGenralCall(I2C_TypeDef* I2Cx, FunctionalState Copy_xGCallState);
/************************************************************************************************************* */

void I2C_vSendData(I2C_TypeDef* I2Cx, uint8 Data);
/************************************************************************************************************* */

uint8 I2C_u8ReceiveData(I2C_TypeDef* I2Cx);
/************************************************************************************************************* */

void I2C_vInitStruct(I2C_InitTypeDef *pxI2C_Cnfg , uint16 Copy_u16NodeAdd);
/************************************************************************************************************* */

Error_Status I2C_xReadRegister(I2C_TypeDef* I2Cx, uint8 Copy_u8Register ,uint16 *pu16RegVal);
/************************************************************************************************************* */

Error_Status I2C_xSend7BitAddress(I2C_TypeDef* I2Cx, uint8 Address, uint8 Copy_u8Direction);
/************************************************************************************************************* */

Error_Status I2C_xGenerateStop(I2C_TypeDef* I2Cx, FunctionalState Copy_xStartState);
/************************************************************************************************************* */

Flag_Status I2C_xGetFlagStatus(I2C_TypeDef* I2Cx, uint32 Copy_u32Flag);

#endif /* I2C_INTEFACE_H_ */
