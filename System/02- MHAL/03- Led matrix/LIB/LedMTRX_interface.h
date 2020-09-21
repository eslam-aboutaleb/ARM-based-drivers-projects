#ifndef LED_MTRX_INTERFACE_H
#define LED_MTRX_INTERFACE_H

/************************************************************************************************************* */
/* led matrix display states*/
#define LEDMTRX_STOP			0
#define LEDMTRX_RESUME			1

#define LEDMTRX_DECSPEED				  0
#define LEDMTRX_INCSPEED				  1

typedef enum
{
	LED_MTRX_A,
	LED_MTRX_B,
	LED_MTRX_C,
	LED_MTRX_D,
	LED_MTRX_E,
	LED_MTRX_F,
	LED_MTRX_G,
	LED_MTRX_H,
	LED_MTRX_I,
	LED_MTRX_J,
	LED_MTRX_K,
	LED_MTRX_L,
	LED_MTRX_M,
	LED_MTRX_N,
	LED_MTRX_O,
	LED_MTRX_P,
	LED_MTRX_Q,
	LED_MTRX_R,
	LED_MTRX_S,
	LED_MTRX_T,
	LED_MTRX_U,
	LED_MTRX_V,
	LED_MTRX_W,
	LED_MTRX_X,
	LED_MTRX_Y,
	LED_MTRX_Z,
	LED_MTRX_SPACE
}LedMtrx_Alphapet;

/************************************************************************************************************* */

void LedMtrx_vInit(void);
void LedMtrx_vDisplayAlphabet(LedMtrx_Alphapet Copy_xAlphabet);
void LedMtrx_vDisplayArr(uint8* Copy_pu8Arr);
void LedMtrx_vDisplayLine( uint8 *Copy_u8Line , uint8 Copy_u8ColsCount);
void LedMtrx_vSetSpeed(uint8 Copy_u8SpeedCmd);
void LedMtrx_VSetDispState(uint8 Copy_u8DispState);
void LedMtrx_vDisableAllCols(void);
void LedMtrx_vDisplayShapes( uint8 *Copy_u8ShapesArr , uint32 Copy_u32ColsCountDiv_8);

#endif

