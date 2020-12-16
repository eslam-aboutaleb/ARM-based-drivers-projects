/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: ADC_private.h		                                                 */
/* Version	: V01                                                                */
/* Date		: 16 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
/************************************************************************************************************* */

#include "ADC_reg.h"

/* ************************************************************************************************************ */
										/* ADC error checkers */
/* ************************************************************************************************************ */


#define ADC_IS_VALID_N_CHANNELS(Number)					((Number >= 1) && (Number <= 16))
/************************************************************************************************************* */

#define ADC_IS_VALID_CHANNEL(CHANNEL) 					(((CHANNEL) == ADC_CHANNEL_0) || ((CHANNEL) == ADC_CHANNEL_1) || \
														 ((CHANNEL) == ADC_CHANNEL_2) || ((CHANNEL) == ADC_CHANNEL_3) || \
														 ((CHANNEL) == ADC_CHANNEL_4) || ((CHANNEL) == ADC_CHANNEL_5) || \
														 ((CHANNEL) == ADC_CHANNEL_6) || ((CHANNEL) == ADC_CHANNEL_7) || \
														 ((CHANNEL) == ADC_CHANNEL_8) || ((CHANNEL) == ADC_CHANNEL_9) || \
														 ((CHANNEL) == ADC_CHANNEL_10) || ((CHANNEL) == ADC_CHANNEL_11) || \
														 ((CHANNEL) == ADC_CHANNEL_12) || ((CHANNEL) == ADC_CHANNEL_13) || \
														 ((CHANNEL) == ADC_CHANNEL_14) || ((CHANNEL) == ADC_CHANNEL_15) || \
														 ((CHANNEL) == ADC_CHANNEL_16) || ((CHANNEL) == ADC_CHANNEL_17))

/************************************************************************************************************* */

#define ADC_IS_VALID_SAMPLE_TIME(TIME) 					(((TIME) == ADC_SAMPLETIME_1CYCLES5) || \
														  ((TIME) == ADC_SAMPLETIME_7CYCLES5) || \
														  ((TIME) == ADC_SAMPLETIME_13CYCLES5) || \
														  ((TIME) == ADC_SAMPLETIME_28CYCLES5) || \
														  ((TIME) == ADC_SAMPLETIME_41CYCLES5) || \
														  ((TIME) == ADC_SAMPLETIME_55CYCLES5) || \
														  ((TIME) == ADC_SAMPLETIME_71CYCLES5) || \
														  ((TIME) == ADC_SAMPLETIME_239CYCLES5))

/************************************************************************************************************* */

#define ADC_IS_VALID_N_DISC_CHANNELS(Number)			(Number >= 1) && (Number <= 8)

/************************************************************************************************************* */

#define ADC_IS_VALID_RANK(Rank) (((Rank) == ADC_REGULAR_RANK_1 ) || \
                                      ((Rank) == ADC_REGULAR_RANK_2 ) || \
                                      ((Rank) == ADC_REGULAR_RANK_3 ) || \
                                      ((Rank) == ADC_REGULAR_RANK_4 ) || \
                                      ((Rank) == ADC_REGULAR_RANK_5 ) || \
                                      ((Rank) == ADC_REGULAR_RANK_6 ) || \
                                      ((Rank) == ADC_REGULAR_RANK_7 ) || \
                                      ((Rank) == ADC_REGULAR_RANK_8 ) || \
                                      ((Rank) == ADC_REGULAR_RANK_9 ) || \
                                      ((Rank) == ADC_REGULAR_RANK_10) || \
                                      ((Rank) == ADC_REGULAR_RANK_11) || \
                                      ((Rank) == ADC_REGULAR_RANK_12) || \
                                      ((Rank) == ADC_REGULAR_RANK_13) || \
                                      ((Rank) == ADC_REGULAR_RANK_14) || \
                                      ((Rank) == ADC_REGULAR_RANK_15) || \
                                      ((Rank) == ADC_REGULAR_RANK_16)   )

/************************************************************************************************************* */

#define ADC_IS_VALID_FLAG(FLAG)							(((FLAG) == ADC_FLAG_AWD) || ((FLAG) == ADC_FLAG_EOC) || \
                               	   	   	   	   	   	   ((FLAG) == ADC_FLAG_JEOC) || ((FLAG)== ADC_FLAG_JSTRT) || \
													   ((FLAG) == ADC_FLAG_STRT))

/************************************************************************************************************* */

#define ADC_IS_VALID_GROUP_LENGTH(Length)				(((LENGTH) >= 0x1) && ((LENGTH) <= 0x10))
#define ADC_IS_VALID_ALIGN_MODE(ALIGN) 					(((ALIGN) == ADC_DATA_ALIGN_RIGHT) || \
														((ALIGN) == ADC_DATA_ALIGN_LEFT))

/************************************************************************************************************* */

#define ADC_IS_VALID_EX_TRIGGER(Trigger) 				(((Trigger) == ADC_EXTERNALTRIGCONV_T1_CC1) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T1_CC2) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T1_CC3) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T2_CC2) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T3_TRGO) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T4_CC4) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_EXT_IT11_TIM8_TRGO) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_NONE) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T3_CC1) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T2_CC3) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T8_CC1) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T8_TRGO) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T5_CC1) || \
														  ((Trigger) == ADC_EXTERNALTRIGCONV_T5_CC3))

/************************************************************************************************************* */


#define ADC_IS_VALID_MODE(MODE)							(((MODE) == ADC_MODE_INDEPENDENT) || \
													   ((MODE) == ADC_MODE_REGINJECSIMULT) || \
													   ((MODE) == ADC_MODE_REGSIMULT_ALTERTRIG) || \
													   ((MODE) == ADC_MODE_INJECSIMULT_FASTINTERL) || \
													   ((MODE) == ADC_MODE_INJECSIMULT_SLOWINTERL) || \
													   ((MODE) == ADC_MODE_INJECSIMULT) || \
													   ((MODE) == ADC_MODE_REGSIMULT) || \
													   ((MODE) == ADC_MODE_FASTINTERL) || \
													   ((MODE) == ADC_MODE_SLOWINTERL) || \
													   ((MODE) == ADC_MODE_ALTERTRIG))

/************************************************************************************************************* */
									/* ADC Masks macros */
/************************************************************************************************************* */

/* ADC Software start mask */
#define CR2_EXTTRIG_SWSTART_Set     ((uint32)0x00500000)
#define CR2_EXTTRIG_SWSTART_Reset   ((uint32)0xFFAFFFFF)

/* ADC DISCEN mask */
#define CR1_DISCEN_Set              ((uint32)0x00000800)
#define CR1_DISCEN_Reset            ((uint32)0xFFFFF7FF)

/* ADC DMA mask */
#define CR2_DMA_Set                 ((uint32)0x00000100)
#define CR2_DMA_Reset               ((uint32)0xFFFFFEFF)

/************************************************************************************************************* */
/* Delay step between two starts of the ADC peripheral */
#define ADC_START_DELAY_US               1U

/* ************************************************************************************************************ */
										/* Local function prototypes */
/* ************************************************************************************************************ */

static Error_Status ADC_xSetMode(ADC_TypeDef* ADCx , uint32 Copy_u32Mode);
/************************************************************************************************************* */

static Error_Status ADC_xSetScanMode(ADC_TypeDef* ADCx, FunctionalState Copy_xState);
/************************************************************************************************************* */

static Error_Status ADC_xSetDataAlignMode(ADC_TypeDef* ADCx, uint32 Copy_u8AlignMode);
/************************************************************************************************************* */

static Error_Status ADC_xExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState Copy_xExTriggerState);
/************************************************************************************************************* */

static Error_Status ADC_xSetContinuousMode(ADC_TypeDef* ADCx, FunctionalState Copy_xContState);
/************************************************************************************************************* */

static Error_Status ADC_xSetNumberOfChannels(ADC_TypeDef *ADCx, uint8 Copy_u8NChannels);

#endif /* ADC_PRIVATE_H_ */
