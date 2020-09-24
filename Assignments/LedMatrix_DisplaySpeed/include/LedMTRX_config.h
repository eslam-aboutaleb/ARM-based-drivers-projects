/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 1-9-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef LED_MTRX_CONFIG_H
#define LED_MTRX_CONFIG_H

/************************************************************************************************************* */

#define LED_MATRIX_DELAY_US               2500

#define LED_MATRX_ROWS_N                  8
#define LED_MATRX_COLUMNS_N               8

#define LED_MATRX_COLS_STATE              COLS_CATHODE
#define LED_MATRX_ROWS_STATE 			  ROWS_ANODE

#define LEDMTRX_INITDISPSPEED			  20
#define LEDMTRX_SPEEDSTEP				  5
#define LEDMTRX_SPEEDLIMIT1ST			  5
#define LEDMTRX_SPEEDLIMIT2ND			  50


/************************************************************************************************************* */

typedef struct{
	GPIO_pPORTx *LedMtrx_Port;
	uint8       LedMtrx_Pin;
}LedMtrx_Map;

/************************************************************************************************************* */

LedMtrx_Map LedMtrxRows_Map[LED_MATRX_ROWS_N]={
		{GPIOA,GPIO_PIN_1},
		{GPIOA,GPIO_PIN_2},
		{GPIOA,GPIO_PIN_3},
		{GPIOA,GPIO_PIN_4},
		{GPIOA,GPIO_PIN_5},
		{GPIOA,GPIO_PIN_6},
		{GPIOA,GPIO_PIN_7},
		{GPIOA,GPIO_PIN_8}
};

LedMtrx_Map LedMtrxCols_Map[LED_MATRX_ROWS_N]=
{
		{GPIOB,GPIO_PIN_0},
		{GPIOB,GPIO_PIN_1},
		{GPIOB,GPIO_PIN_5},
		{GPIOB,GPIO_PIN_6},
		{GPIOB,GPIO_PIN_7},
		{GPIOB,GPIO_PIN_8},
		{GPIOB,GPIO_PIN_9},
		{GPIOB,GPIO_PIN_10}
};

/************************************************************************************************************* */

#endif

