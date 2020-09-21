/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef __SDD_H__
#define __SDD_H__

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/*SSD data structures*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

/* Number of SSDs */
#define N_SSD           (2)

/*Names of SSDs*/
typedef enum
{
	SSD_One,
	SSD_Two
}tSSD;

/* SSD states */
typedef enum
{
	SSD_OFF = 0,
	SSD_ON = 1
}tSSD_State;


/*Type of SSDs*/
typedef enum
{
	SSD_Cathode,
	SSD_Anode
}tSSD_Type;


/* SSD symbols */
typedef enum
{
	SSD_0 = 0,
	SSD_1,
	SSD_2,
	SSD_3,
	SSD_4,
	SSD_5,
	SSD_6,
	SSD_7,
	SSD_8,
	SSD_9,
	SSD_NULL
}tSSD_Symbol;

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/* SSDs Puplic functions*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

void SSD_vInit(tSSD Copy_xSSD,tSSD_Type Copy_xSSD_type);
void SSD_vUpdate(void);
void SSD_vOut(tSSD Copy_xSSD,tSSD_Type Copy_SSD_xtype, tSSD_Symbol Copy_SSD_xSymbol);
/*If the user uses multiplexing these functions will be declared*/
#if(SSD_MULTIPLEXING_STATE == SSD_MULTIPLEXING_ON)
tSSD_State SSD_xGetState(tSSD Copy_xSSD);
void SSD_vSetState(tSSD Copy_xSSD,tSSD_Type Copy_xSSD_type ,tSSD_State Copy_SSD_xState);
#endif


#endif // __SDD_H__
