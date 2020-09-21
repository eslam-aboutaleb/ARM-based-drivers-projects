#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "DAC_interface.h"
#include "DAC_config.h"
void DAC_vInit(void)
{
	GPIO_vInitPortPin(DAC_PIN_0_CR_PORT,DAC_PIN_0,GPIO_OUT);
	GPIO_vInitPortPin(DAC_PIN_1_CR_PORT,DAC_PIN_1,GPIO_OUT);
	GPIO_vInitPortPin(DAC_PIN_2_CR_PORT,DAC_PIN_2,GPIO_OUT);
	GPIO_vInitPortPin(DAC_PIN_3_CR_PORT,DAC_PIN_3,GPIO_OUT);
	GPIO_vInitPortPin(DAC_PIN_4_CR_PORT,DAC_PIN_4,GPIO_OUT);
	GPIO_vInitPortPin(DAC_PIN_5_CR_PORT,DAC_PIN_5,GPIO_OUT);
	GPIO_vInitPortPin(DAC_PIN_6_CR_PORT,DAC_PIN_6,GPIO_OUT);
	GPIO_vInitPortPin(DAC_PIN_7_CR_PORT,DAC_PIN_7,GPIO_OUT);
}

void DAC_vConvert(const uint8 *Sound , uint16 SoundSize)
{
	static volatile uint16 Local_u8index = 0;
	GPIO_vWritePortPin(DAC_PIN_0_DR_PORT,DAC_PIN_0,GET_BIT(Sound[Local_u8index],0));
	GPIO_vWritePortPin(DAC_PIN_1_DR_PORT,DAC_PIN_1,GET_BIT(Sound[Local_u8index],1));
	GPIO_vWritePortPin(DAC_PIN_2_DR_PORT,DAC_PIN_2,GET_BIT(Sound[Local_u8index],2));
	GPIO_vWritePortPin(DAC_PIN_3_DR_PORT,DAC_PIN_3,GET_BIT(Sound[Local_u8index],3));
	GPIO_vWritePortPin(DAC_PIN_4_DR_PORT,DAC_PIN_4,GET_BIT(Sound[Local_u8index],4));
	GPIO_vWritePortPin(DAC_PIN_5_DR_PORT,DAC_PIN_5,GET_BIT(Sound[Local_u8index],5));
	GPIO_vWritePortPin(DAC_PIN_6_DR_PORT,DAC_PIN_6,GET_BIT(Sound[Local_u8index],6));
	GPIO_vWritePortPin(DAC_PIN_7_DR_PORT,DAC_PIN_7,GET_BIT(Sound[Local_u8index],7));

	Local_u8index++;
	if(Local_u8index == SoundSize)
	{
		Local_u8index = 0;
	}
	else
	{
		/* No Action*/
	}
}
