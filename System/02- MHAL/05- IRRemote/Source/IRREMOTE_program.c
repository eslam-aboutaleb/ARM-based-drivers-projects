#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "utils.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"
#include "EXTI_interface.h"

#include "IRREMOTE_interface.h"
#include "IRREMOTE_config.h"
#include "IRREMOT_private.h"

/************************************************************************************************************* */

/* Remote frame */
static uint32 u32IRREMOTE_Frame[50]	   = {0};

/* Start flag to indicate receiving a new frame */
static volatile uint8 u8StartFlag	   = 0;
/* Edge counter used as remote frame index */
static volatile uint8 u8EdgeCounter    = 0;
/* Error state */
static volatile uint8 u8IRREMOTE_Error = 0;
/* Array of structures index */
static volatile uint8 u8ButtonsIndex   = 0;

/************************************************************************************************************* */
/* Private macros*/
#define IR_START_FLAG_SET_VAL(VAL)                          u8StartFlag   = VAL

#define IR_EDGE_COUNTER_SET_VAL(VAL)						u8EdgeCounter = VAL

#define IR_SET_ERROR()									   	u8IRREMOTE_Error = E_NOK
#define IR_CLR_ERROR()										u8IRREMOTE_Error = E_OK
#define IR_GET_ERROR_STATE()							   (u8IRREMOTE_Error & 1)

typedef struct
{
	IRREMOTE_Buttons Button;
	void (*IRREMOTE_CallBack)(void);
}IRREMOTEButton_TypeDef;

IRREMOTEButton_TypeDef RemoteButtons[IRREMOTE_N_BUTTONS];

/************************************************************************************************************* */

void IRREMOTE_vInit(void)
{
	/*Initialize IR remote pin as floating input*/
	GPIO_vInitPortPin(IRREMOTE_CR_PORT,IRREMOTE_CR_PIN,GPIO_PIN_INPUT_FLOATING_MODE);
}

/************************************************************************************************************* */

void IRREMOTE_vEnableExInt(void)
{
	IRREMOTE_EN_EX_INT();
}

/************************************************************************************************************* */

void IRREMOTE_SetButtonFunc(IRREMOTE_Buttons Copy_xButton , void (*vpFunc)(void))
{
	/* Assign button informations to its opposite in remote buttons structure */
	RemoteButtons[u8ButtonsIndex].Button = Copy_xButton;
	RemoteButtons[u8ButtonsIndex].IRREMOTE_CallBack = vpFunc;
	/* Increase the index */
	u8ButtonsIndex++;
}

/************************************************************************************************************* */

uint8 IRREMOTE_u8GetFrame(void)
{
	/*Check if is it the first time to receive a frame*/
	if (u8StartFlag == 0)
	{
		/* Start Timer */
		IRREMOTE_SINGLE_INTERVAL(IRREMOTE_FRAM_WAITING_MS,IRREMOTE_u8TakeAction);
		/*Set the start flag*/
		IR_START_FLAG_SET_VAL(1);
	}

	else
	{
		/*Get stamp of elapsed time into frame array*/
		u32IRREMOTE_Frame[u8EdgeCounter] = IRREMOTE_GET_ELAPSED_TIME();
		/*Start timer again*/
		IRREMOTE_SINGLE_INTERVAL(IRREMOTE_FRAM_WAITING_MS,IRREMOTE_u8TakeAction);
		/*Increase Edge counter*/
		u8EdgeCounter++;
	}

	/*Check if there any error occurred while the process*/
	if(IR_GET_ERROR_STATE() == E_NOK)
	{
		return E_NOK;
	}
	else
	{
		return E_OK;
	}
}

/************************************************************************************************************* */

static void IRREMOTE_u8TakeAction (void)
{
	/*If start bit of the frame not valid return an error*/
	if(IRREMOTE_CHECK_START_BIT(u32IRREMOTE_Frame[0]) != E_OK)
	{
		IR_SET_ERROR();
		return;
	}
	else
	{
		IR_CLR_ERROR();
	}

	uint8 u8Local_DataIndex = 0;
	volatile uint8 u8FrameData	= 0;

	/*Set data according to frame bits state*/
	for(u8Local_DataIndex = 0; u8Local_DataIndex < IRREMOTE_DATA_SIZE; u8Local_DataIndex++)
	{
		/*If the frame bit time stamp is high set the opposite bit in frame data*/
		if(IRREMOTE_CHECK_BIT_STATE(u32IRREMOTE_Frame[IRREMOTE_DATA_START_INDEX+u8Local_DataIndex]) == E_OK)
		{
			SET_BIT(u8FrameData,u8Local_DataIndex);
		}
		else
		{
			CLEAR_BIT(u8FrameData,u8Local_DataIndex);
		}
	}
	/*Check the button*/
	if(IRREMOTE_u8CheckButton(u8FrameData) != E_OK)
	{
		IR_SET_ERROR();
	}
	else
	{
		IR_CLR_ERROR();
	}

	/*Clear start flag to receive new frame*/
	IR_START_FLAG_SET_VAL(0);
	/*Clear edge counter*/
	IR_EDGE_COUNTER_SET_VAL(0);
	/*Clear frame start bit*/
	u32IRREMOTE_Frame[0] = 0;

}

/************************************************************************************************************* */

static uint8 IRREMOTE_u8CheckButton(uint8 Copy_u8Button)
{
	uint8 Local_u8ErrorState = E_NOK;
	uint8 Local_u8Index = 0;

	/*Check if the button matches the assigned buttons or not*/
	for(Local_u8Index = 0; Local_u8Index < IRREMOTE_N_BUTTONS; Local_u8Index++)
	{
		/*Break the loop if the current index is more than the assigned buttons number*/
		if(Local_u8Index > u8ButtonsIndex)
		{
			break;
		}

		if(RemoteButtons[Local_u8Index].Button == Copy_u8Button)
		{
			/* Execute the button function*/
			RemoteButtons[Local_u8Index].IRREMOTE_CallBack();
			Local_u8ErrorState = E_OK;
		}
		else
		{
			/* No Action*/
		}
	}
	return Local_u8ErrorState;
}


