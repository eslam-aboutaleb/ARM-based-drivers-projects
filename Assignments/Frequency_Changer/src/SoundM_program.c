/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 21-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"

#include "DAC_interface.h"
#include "IRREMOTE_interface.h"

#include "SoundM_interface.h"
#include "SoundM_config.h"
#include "SoundM_private.h"
/************************************************************************************************************* */

static uint32 u32SoundM_Freq 	 = 0;
static uint32 u32SoundM_LastFreq = 0;
static uint16 u16SoundLength     = 0;
static const uint8 *Sound				 = Null;
/************************************************************************************************************* */


uint8 SoundM_u8Init(const uint8 *Copy_pu8Sound ,uint16 Copy_u16SoundLength ,uint32 Copy_u32Frequs)
{
	/*Check if there is sound or not*/
	if(Copy_pu8Sound == Null)
	{
		return E_NOK;
	}
	else
	{
		/*No Action*/
	}

	u32SoundM_Freq = Copy_u32Frequs;
	Sound		   = Copy_pu8Sound;
	u16SoundLength = Copy_u16SoundLength;
	/*Start the sound*/
	SoundM_SetIntervalPeriodic(u32SoundM_Freq,SoundM_vOut);

	u32SoundM_LastFreq = Copy_u32Frequs;
	return E_OK;
}
/************************************************************************************************************* */

#if SOUNDM_REMOTE_STATE == SOUNDM_REMOTE_ON
void SoundM_RemoteCtrlInit(void)
{
	IRREMOTE_SetButtonFunc(IRREMOTE_BACKWARD , SoundM_vDecFreq);
	IRREMOTE_SetButtonFunc(IRREMOTE_FORWARD  , SoundM_vIncFreq);
}
#endif
/************************************************************************************************************* */

void SoundM_vDecFreq(void)
{
	u32SoundM_Freq -= 10;
}
/************************************************************************************************************* */

void SoundM_vIncFreq(void)
{
	u32SoundM_Freq += 10;
}
/************************************************************************************************************* */

void SoundM_vUpdate(void)
{
	/*If there is no change in frequency or sound wasn't initialized return*/
	if((u32SoundM_LastFreq == u32SoundM_Freq) || (Sound == Null) )
	{
		return;
	}
	else
	{
		/*No Action*/
	}

	SoundM_SetIntervalPeriodic(u32SoundM_Freq,SoundM_vOut);
	/*Set the new frequency*/
	u32SoundM_LastFreq = u32SoundM_Freq;
}
/************************************************************************************************************* */

static void SoundM_vOut(void)
{
	DAC_vConvert(Sound,u16SoundLength);
}
