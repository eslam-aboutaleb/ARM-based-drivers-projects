/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "SW_interface.h"
#include "SW_config.h"

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

	/* Initialize switches as inputs */

	GPIO_vInitPortPin(SW_Map[Copy_xSW].SW_Port, SW_Map[Copy_xSW].SW_Pin, GPIO_IN);
	if(Copy_xSW_Type == SW_PULL_UP)
	{
		GPIO_vWritePortPin(SW_Map[Copy_xSW].SW_Port, SW_Map[Copy_xSW].SW_Pin , GPIO_HIGH);
	}

	/* Initialize switch samples */
	SWs_Info[Copy_xSW].sw_samples[0] = SW_RELEASED_LEVEL;
	SWs_Info[Copy_xSW].sw_samples[1] = SW_RELEASED_LEVEL;

	/* Initialize switch state */
	SWs_Info[Copy_xSW].sw_state = SW_RELEASED;
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

		SWs_Info[LOC_Index].sw_samples[1] = GPIO_u8ReadPortPin(SW_Map[LOC_Index].SW_Port, SW_Map[LOC_Index].SW_Pin);


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
