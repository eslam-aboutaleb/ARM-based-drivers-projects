/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: I2C_private.h		                                                 */
/* Version	: V01                                                                */
/* Date		: 18 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

/************************************************************************************************************* */

#define I2C_IS_VALID_CLOCK_SPEED(ClockSpeed)				(((ClockSpeed) >= 0x1) && ((ClockSpeed) <= 400000))


#define I2C_IS_DUTY_CYCLE(CYCLE) 							(((CYCLE) == I2C_SM_NO_DUTY_CYCLE_CNFG)	|| \
															((CYCLE) == I2C_DUTY_CYCLE_16_9)		|| \
                                  	  	  	  	  	  	  	 ((CYCLE) == I2C_DUTY_CYCLE_2))

#define I2C_IS_MODE(MODE)									(((MODE) == I2C_MODE_I2C)			|| \
															((MODE) == I2C_MODE_SM_BUS_DEVICE)	|| \
															((MODE) == I2C_MODE_SM_BUS_HOST))

#define I2C_IS_ACK_STATE(STATE) 							(((STATE) == I2C_ACK_ENABLE) || \
															((STATE) == I2C_ACK_DISABLE))

#define I2C_IS_VALID_ADDRESS1(ADDRESS1) 					((ADDRESS1) <= 0x3FF)

#define I2C_IS_VALID_ADDRESS_LENGTH(ADDRESS)				(((ADDRESS) == I2C_ADDRESS_7BIT) || \
                                             	 	 	 	 ((ADDRESS) == I2C_ADDRESS_10BIT))
#define I2C_IS_VALID_ADDRESS2(ADDRESS2)						((ADDRESS2) <= 0x7F)

#define I2C_IS_DUAL_ADDRESS(MODE) 							(((MODE) == I2C_DUAL_ADDRESS_DISABLE) || \
                                      	  	  	  	  	  	 ((MODE) == I2C_DUAL_ADDRESS_ENABLE))

#define I2C_IS_VALID_DIRECTION(DIRECTION) 					(((DIRECTION) == I2C_DIRECTION_TRANSMITTER) || \
                                     	 	 	 	 	 	 ((DIRECTION) == I2C_DIRECTION_RECEIVER))

#define I2C_IS_VALID_REG(REGISTER) 							(((REGISTER) == I2C_REGISTER_CR1) || \
															   ((REGISTER) == I2C_REGISTER_CR2) || \
															   ((REGISTER) == I2C_REGISTER_OAR1) || \
															   ((REGISTER) == I2C_REGISTER_OAR2) || \
															   ((REGISTER) == I2C_REGISTER_DR) || \
															   ((REGISTER) == I2C_REGISTER_SR1) || \
															   ((REGISTER) == I2C_REGISTER_SR2) || \
															   ((REGISTER) == I2C_REGISTER_CCR) || \
															   ((REGISTER) == I2C_REGISTER_TRISE))

#define I2C_IS_VALID_FLAG(FLAG) (((FLAG) == I2C_FLAG_DUALF) || ((FLAG) == I2C_FLAG_SMBHOST) || \
                               ((FLAG) == I2C_FLAG_SMBDEFAULT) || ((FLAG) == I2C_FLAG_GENCALL) || \
                               ((FLAG) == I2C_FLAG_TRA) || ((FLAG) == I2C_FLAG_BUSY) || \
                               ((FLAG) == I2C_FLAG_MSL) || ((FLAG) == I2C_FLAG_SMBALERT) || \
                               ((FLAG) == I2C_FLAG_TIMEOUT) || ((FLAG) == I2C_FLAG_PECERR) || \
                               ((FLAG) == I2C_FLAG_OVR) || ((FLAG) == I2C_FLAG_AF) || \
                               ((FLAG) == I2C_FLAG_ARLO) || ((FLAG) == I2C_FLAG_BERR) || \
                               ((FLAG) == I2C_FLAG_TXE) || ((FLAG) == I2C_FLAG_RXNE) || \
                               ((FLAG) == I2C_FLAG_STOPF) || ((FLAG) == I2C_FLAG_ADD10) || \
                               ((FLAG) == I2C_FLAG_BTF) || ((FLAG) == I2C_FLAG_ADDR) || \
                               ((FLAG) == I2C_FLAG_SB))

/************************************************************************************************************* */

#define I2C_STANDARD_MODE_SPEED_MAX									100000
#define I2C_STANDARD_FAST_SPEED_MAX									400000

#define I2C_MIN_ALLOWED_CCR_SM										0x04
#define I2C_MIN_ALLOWED_CCR_FM										0x01

/* I2C F/S mask */
#define CCR_FS_SET              							((uint16)0x8000)

/* I2C CR1 register Mask */
#define CR1_CLEAR_MASK        							  	((uint16)0xFBF5)

/* I2C ADD mask */
#define OAR1_ADD_SET           								((uint16)0x0001)
#define OAR1_ADD_RESET	         							((uint16)0xFFFE)

#define I2C_FLAG_MASK              							((uint32)0x00FFFFFF)

/************************************************************************************************************* */
										/* I2C local Functions prototypes */
/************************************************************************************************************* */

static Error_Status I2C_xSetClkSettings(I2C_TypeDef* I2Cx , uint32 Copy_u32ClockSpeed ,uint16 Copy_u16DutyCycle);
static Error_Status I2C_xSetMode(I2C_TypeDef* I2Cx , uint16 Copy_u16Mode);
static Error_Status I2C_xSetAddress1(I2C_TypeDef* I2Cx , uint16 Copy_u16Address , uint16 Copy_u16AddressLength);
static Error_Status I2C_xSetAddress2(I2C_TypeDef* I2Cx , uint16 Copy_u16Address , uint16 Copy_u16DualMode);

#endif /* I2C_PRIVATE_H_ */
