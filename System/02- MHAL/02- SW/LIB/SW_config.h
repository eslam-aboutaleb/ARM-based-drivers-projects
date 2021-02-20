/*////////////////////////////////////////////////////////////////////////////// */
/* Author : Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 19-8-2020                                                               */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef SWITCH_CONFIG_H
#define SWITCH_CONFIG_H

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/*SW configuration macros*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////// */


/* SW voltage level */
#define SW_PRESSED_LEVEL        (0)
#define SW_RELEASED_LEVEL       (1)

/* Number of samples per SW */
#define SW_N_SAMPLES      (2)


#define SW_N_SWITCHES     (1)

typedef struct{
	GPIO_Port_t SW_Port;
	GPIO_Pin_t SW_Pin;
}SW_MapCnfg;

SW_MapCnfg SW_Map[SW_N_SWITCHES]= {
		{GPIOB,GPIO_PIN_0}
};


#endif
