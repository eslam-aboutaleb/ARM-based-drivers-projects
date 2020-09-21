/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 21-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef SOUNDM_INTERFACE_H
#define SOUNDM_INTERFACE_H

#define SOUNDM_DEC_FREQ									0
#define SOUNDM_INC_FREQ									1

/************************************************************************************************************* */

uint8 SoundM_u8Init(const uint8 *Copy_pu8Sound ,uint16 Copy_u16SoundLength ,uint32 Copy_u32Frequs);
void SoundM_vDecFreq(void);
void SoundM_vIncFreq(void);
void SoundM_vUpdate(void);
#if SOUNDM_REMOTE_STATE == SOUNDM_REMOTE_ON
void SoundM_RemoteCtrlInit(void);
#endif

#endif
