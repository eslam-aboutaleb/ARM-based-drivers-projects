/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef BIT_MATH_H
#define BIT_MATH_H

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#define SET_BIT(VAR,BIT)          VAR |=  (1 << (BIT))
#define CLEAR_BIT(VAR,BIT)          VAR &= ~(1 << (BIT))

#define GET_BIT(VAR,BIT)          ((VAR >> BIT) & 1  )
#define TOG_BIT(VAR,BIT)          VAR ^=  (1 << (BIT))

/*check if a specified Bit is Set*/
#define BIT_IS_SET(REG,BIT)      ((REG>>BIT)&1)
/*Check if a specified BIT is Clear*/
#define BIT_IS_CLEAR(REG,BIT)  (!((REG>>BIT)&1))

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


#endif 
