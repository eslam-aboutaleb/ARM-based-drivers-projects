/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: I2C_config.h		                                                 */
/* Version	: V01                                                                */
/* Date		: 18 - 12 - 2020                                                     */
/* ***************************************************************************** */


#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_
/************************************************************************************************************* */

typedef struct{
	GPIO_Port_t I2C_Port;
	uint8 I2C_Pin;
}I2C_PinMap;
/************************************************************************************************************* */
#define I2C_SCL												0
#define I2C_SDA												1

#define I2C_SCL_PORT										GPIOB
#define	I2C_SCL_PIN											GPIO_PIN_6

#define I2C_SDA_PORT										GPIOB
#define	I2C_SDA_PIN											GPIO_PIN_7
/************************************************************************************************************* */

I2C_PinMap I2C_Pins[2] = {
		{I2C_SCL_PORT,I2C_SCL_PIN},
		{I2C_SDA_PORT,I2C_SDA_PIN}
};

#endif
