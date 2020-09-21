/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "Switch_interface.h"
#include "Switch_config.h"

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/*Local data structures*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

/* SW info: samples, state */
typedef struct
{
	uint8 sw_samples[SW_N_SAMPLES];
	tSW_State sw_state;
}tSW_Info;

/* Switches info */
static tSW_Info SWs_Info[SW_N_SWITCHES];

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/*Functions definitions*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

void SW_vInit(tSW Copy_xSW,tSW_Type Copy_xSW_Type )
{
	uint8 LOC_Index = 0;

	/* Initialize switches as inputs */
	switch(Copy_xSW)
	{
	case SW_PLUS:
		GPIO_vInitPortPin(SW_PLUS_PORT_CR, SW_PLUS_PIN, GPIO_IN);
		if(Copy_xSW_Type == SW_PULLUP)
		{
			GPIO_vWritePortPin(SW_PLUS_PORT_DR , SW_PLUS_PIN , GPIO_HIGH);
		}
		else
		{
			/* No Action */
		}
		break;
	case SW_MINUS:
		GPIO_vInitPortPin(SW_MINUS_PORT_CR, SW_MINUS_PIN, GPIO_IN);
		if(Copy_xSW_Type == SW_PULLUP){
			GPIO_vWritePortPin(SW_MINUS_PORT_CR, SW_MINUS_PIN,GPIO_HIGH);
		}
		else
		{
			/* No Action */
		}
		break;
	default:
		/*No action*/
		break;
	}

	/* Initialize switches info */
	for (LOC_Index = 0; LOC_Index < SW_N_SWITCHES; LOC_Index++)
	{
		/* Initialize switch samples */
		SWs_Info[LOC_Index].sw_samples[0] = SW_RELEASED_LEVEL;
		SWs_Info[LOC_Index].sw_samples[1] = SW_RELEASED_LEVEL;

		/* Initialize switch state */
		SWs_Info[LOC_Index].sw_state = SW_RELEASED;

	}
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

tSW_State SW_xGetState(tSW sw)
{
	/* return sw state */
	return SWs_Info[sw].sw_state;
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

void SW_vUpdate(void)
{
	uint8 LOC_Index=0;
	/* Update switches states */
	for (LOC_Index = SW_PLUS; LOC_Index < SW_N_SWITCHES; LOC_Index++)
	{
		/* Update switch samples */
		SWs_Info[LOC_Index].sw_samples[0] = SWs_Info[LOC_Index].sw_samples[1];

		if (LOC_Index == SW_PLUS)
		{
			SWs_Info[LOC_Index].sw_samples[1] = GPIO_u8ReadPortPin(SW_PLUS_PORT_DR, SW_PLUS_PIN);
		} else if (LOC_Index == SW_MINUS)
		{
			SWs_Info[LOC_Index].sw_samples[1] = GPIO_u8ReadPortPin(SW_MINUS_PORT_DR, SW_MINUS_PIN);
		} else
		{
			/* Do nothing should not be here !! */
		}

		/* Update switch state */
		switch(SWs_Info[LOC_Index].sw_state)
		{

		case SW_RELEASED:
			/* Go to pre-pressed state if needed */
			if ((SWs_Info[LOC_Index].sw_samples[0] == SW_PRESSED_LEVEL) &&
					(SWs_Info[LOC_Index].sw_samples[1] == SW_PRESSED_LEVEL))
			{
				SWs_Info[LOC_Index].sw_state = SW_PRE_PRESSED;
			} else
			{
				/* Do nothing */
			}
			break;
		case SW_PRE_PRESSED:
			/* Go to pressed state if needed  */
			if (SWs_Info[LOC_Index].sw_samples[1] == SW_PRESSED_LEVEL)
			{
				SWs_Info[LOC_Index].sw_state = SW_PRESSED;
			} else
			{
				/* Do nothing */
			}
			break;
		case SW_PRESSED:
			/* Go to pre-released state if needed */
			if ((SWs_Info[LOC_Index].sw_samples[0] == SW_RELEASED_LEVEL) &&
					(SWs_Info[LOC_Index].sw_samples[1] == SW_RELEASED_LEVEL))
			{
				SWs_Info[LOC_Index].sw_state = SW_PRE_RELEASED;
			}
			else
			{
				/* Do nothing */
			}
			break;
		case SW_PRE_RELEASED:
			/* Go to released state if needed */
			if (SWs_Info[LOC_Index].sw_samples[1] == SW_RELEASED_LEVEL)
			{
				SWs_Info[LOC_Index].sw_state = SW_RELEASED;
			} else
			{
				/* Do nothing */
			}
			break;
			/* Should not be here */
		default:
			break;
		}
	}

}
