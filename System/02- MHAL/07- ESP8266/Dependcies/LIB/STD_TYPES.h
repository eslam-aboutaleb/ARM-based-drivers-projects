/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef STD_TYPES_H
#define STD_TYPES_H

/* ***************************************************************************** */

typedef unsigned char     	 	uint8;
typedef unsigned short int 		uint16;
typedef unsigned long int  		uint32;

typedef signed char        		sint8;
typedef signed short int   		sint16;
typedef signed long int    		sint32;

typedef float              		float32;
typedef double             		float64;

typedef char	   				Error_Status;
typedef char	   				Flag_Status;
typedef unsigned char			FunctionalState;
/* ***************************************************************************** */
#define E_NOK					(0)
#define E_OK					(1)
#define ERROR					(-1)

#define DISABLE					(0)
#define ENABLE					(1)
#define NULL					((void*)0)

/* ***************************************************************************** */
#define CHARSIZE				((sizeof(uint8)*8)-1)

#endif
