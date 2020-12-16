/* ***************************************************************************** */
/* Author 	: Eslam Ehab Aboutaleb                                               */
/* File		: ADC_interface.h	                                                 */
/* Version	: V01                                                                */
/* Date		: 16 - 12 - 2020                                                     */
/* ***************************************************************************** */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "ADC_reg.h"

/************************************************************************************************************* */
typedef unsigned char										ADC_State_t;
#define ADC_DISBLE											(0)
#define ADC_ENABLE											(1)
/************************************************************************************************************* */

/* ADC channels */
#define ADC_CHANNEL_0                               ((uint8)0x00)
#define ADC_CHANNEL_1                               ((uint8)0x01)
#define ADC_CHANNEL_2                               ((uint8)0x02)
#define ADC_CHANNEL_3                               ((uint8)0x03)
#define ADC_CHANNEL_4                               ((uint8)0x04)
#define ADC_CHANNEL_5                               ((uint8)0x05)
#define ADC_CHANNEL_6                               ((uint8)0x06)
#define ADC_CHANNEL_7                               ((uint8)0x07)
#define ADC_CHANNEL_8                               ((uint8)0x08)
#define ADC_CHANNEL_9                               ((uint8)0x09)
#define ADC_CHANNEL_10                              ((uint8)0x0A)
#define ADC_CHANNEL_11                              ((uint8)0x0B)
#define ADC_CHANNEL_12                              ((uint8)0x0C)
#define ADC_CHANNEL_13                              ((uint8)0x0D)
#define ADC_CHANNEL_14                              ((uint8)0x0E)
#define ADC_CHANNEL_15                              ((uint8)0x0F)
#define ADC_CHANNEL_16                              ((uint8)0x10)
#define ADC_CHANNEL_17                              ((uint8)0x11)

/************************************************************************************************************* */

/* ADC SAMPLING TIME */
#define ADC_SAMPLETIME_1CYCLES5                    ((uint8)0x00)
#define ADC_SAMPLETIME_7CYCLES5                    ((uint8)0x01)
#define ADC_SAMPLETIME_13CYCLES5                   ((uint8)0x02)
#define ADC_SAMPLETIME_28CYCLES5                   ((uint8)0x03)
#define ADC_SAMPLETIME_41CYCLES5                   ((uint8)0x04)
#define ADC_SAMPLETIME_55CYCLES5                   ((uint8)0x05)
#define ADC_SAMPLETIME_71CYCLES5                   ((uint8)0x06)
#define ADC_SAMPLETIME_239CYCLES5                  ((uint8)0x07)

/************************************************************************************************************* */

/* ADC Regular ranks */
#define ADC_REGULAR_RANK_1                 			0x00000001U
#define ADC_REGULAR_RANK_2         			        0x00000002U
#define ADC_REGULAR_RANK_3                 			0x00000003U
#define ADC_REGULAR_RANK_4                 			0x00000004U
#define ADC_REGULAR_RANK_5                 			0x00000005U
#define ADC_REGULAR_RANK_6                 			0x00000006U
#define ADC_REGULAR_RANK_7                			0x00000007U
#define ADC_REGULAR_RANK_8                			0x00000008U
#define ADC_REGULAR_RANK_9                 			0x00000009U
#define ADC_REGULAR_RANK_10                			0x0000000AU
#define ADC_REGULAR_RANK_11                			0x0000000BU
#define ADC_REGULAR_RANK_12               			0x0000000CU
#define ADC_REGULAR_RANK_13                			0x0000000DU
#define ADC_REGULAR_RANK_14                			0x0000000EU
#define ADC_REGULAR_RANK_15                			0x0000000FU
#define ADC_REGULAR_RANK_16            			    0x00000010U

/************************************************************************************************************* */

/* ADC modes */
#define ADC_MODE_INDEPENDENT                       ((uint32)0x00000000)
#define ADC_MODE_REGINJECSIMULT                    ((uint32)0x00010000)
#define ADC_MODE_REGSIMULT_ALTERTRIG               ((uint32)0x00020000)
#define ADC_MODE_INJECSIMULT_FASTINTERL            ((uint32)0x00030000)
#define ADC_MODE_INJECSIMULT_SLOWINTERL            ((uint32)0x00040000)
#define ADC_MODE_INJECSIMULT                       ((uint32)0x00050000)
#define ADC_MODE_REGSIMULT                         ((uint32)0x00060000)
#define ADC_MODE_FASTINTERL                        ((uint32)0x00070000)
#define ADC_MODE_SLOWINTERL                        ((uint32)0x00080000)
#define ADC_MODE_ALTERTRIG                         ((uint32)0x00090000)

/************************************************************************************************************* */

/* ADC flags */
#define ADC_FLAG_AWD                               ((uint8)0x01)
#define ADC_FLAG_EOC                               ((uint8)0x02)
#define ADC_FLAG_JEOC                              ((uint8)0x04)
#define ADC_FLAG_JSTRT                             ((uint8)0x08)
#define ADC_FLAG_STRT                              ((uint8)0x10)

/************************************************************************************************************* */

/* ADC Align modes */
#define ADC_DATA_ALIGN_RIGHT                        ((uint32)0x00000000)
#define ADC_DATA_ALIGN_LEFT                         ((uint32)0x00000800)

/************************************************************************************************************* */

/* ADC external triggers for regular channels conversion */
#define ADC_EXTERNALTRIGCONV_T1_CC1                ((uint32)0x00000000) /*!< For ADC1 AND ADC2 */
#define ADC_EXTERNALTRIGCONV_T1_CC2                ((uint32)0x00020000) /*!< For ADC1 AND ADC2 */
#define ADC_EXTERNALTRIGCONV_T2_CC2                ((uint32)0x00060000) /*!< For ADC1 AND ADC2 */
#define ADC_EXTERNALTRIGCONV_T3_TRGO               ((uint32)0x00080000) /*!< For ADC1 AND ADC2 */
#define ADC_EXTERNALTRIGCONV_T4_CC4                ((uint32)0x000A0000) /*!< For ADC1 AND ADC2 */
#define ADC_EXTERNALTRIGCONV_EXT_IT11_TIM8_TRGO    ((uint32)0x000C0000) /*!< For ADC1 AND ADC2 */

#define ADC_EXTERNALTRIGCONV_T1_CC3                ((uint32)0x00040000) /*!< For ADC1, ADC2 AND ADC3 */
#define ADC_EXTERNALTRIGCONV_NONE                  ((uint32)0x000E0000) /*!< For ADC1, ADC2 AND ADC3 */

#define ADC_EXTERNALTRIGCONV_T3_CC1                ((uint32)0x00000000) /*!< For ADC3 ONLY */
#define ADC_EXTERNALTRIGCONV_T2_CC3                ((uint32)0x00020000) /*!< For ADC3 ONLY */
#define ADC_EXTERNALTRIGCONV_T8_CC1                ((uint32)0x00060000) /*!< For ADC3 ONLY */
#define ADC_EXTERNALTRIGCONV_T8_TRGO               ((uint32)0x00080000) /*!< For ADC3 ONLY */
#define ADC_EXTERNALTRIGCONV_T5_CC1                ((uint32)0x000A0000) /*!< For ADC3 ONLY */
#define ADC_EXTERNALTRIGCONV_T5_CC3                ((uint32)0x000C0000) /*!< For ADC3 only */

/************************************************************************************************************* */

typedef struct
{
	uint32 ADC_Mode;                      /*! Configures the ADC to operate in independent or
                                               dual mode. */

	FunctionalState ADC_ScanConvMode;       /*! Specifies whether the conversion is performed in
                                               Scan (multi-channels) or Single (one channel) mode.
                                               This parameter can be set to ENABLE or DISABLE */

	FunctionalState ADC_ContinuousConvMode; /*! Specifies whether the conversion is performed in
                                               Continuous or Single mode.
                                               This parameter can be set to ENABLE or DISABLE. */

	uint32 ADC_ExternalTrigConv;          /*! Defines the external trigger used to start the analog
                                               to digital conversion of regular channels. */

	uint32 ADC_DataAlign;                 /*! Specifies whether the ADC data alignment is left or right.*/


	uint8 ADC_NbrOfChannel;               /*! Specifies the number of ADC channels that will be converted
                                               using the sequencer for regular channel group.
                                               This parameter must range from 1 to 16. */
}ADC_InitTypeDef;

/************************************************************************************************************* */
										/* ADC Functions prototypes */
/************************************************************************************************************* */


Error_Status ADC_xInit(ADC_TypeDef* ADCx, const ADC_InitTypeDef *pxADC_Cnfg);
/************************************************************************************************************* */

void ADC_vInitStruct(ADC_InitTypeDef *pxADC_Cnfg);
/************************************************************************************************************* */

Error_Status ADC_xChannelCnfg(ADC_TypeDef *ADCx,uint8 Copy_u8ChNum,uint32 Copy_u32Rank,uint8 Copy_u8SampleTime);
/************************************************************************************************************* */

Error_Status ADC_xEnable(ADC_TypeDef* ADCx);
/************************************************************************************************************* */

Error_Status ADC_xSetADCState(ADC_TypeDef *ADCx, ADC_State_t Copy_xState);
/************************************************************************************************************* */

void ADC_vResetCalibration(ADC_TypeDef* ADCx);
/************************************************************************************************************* */

void ADC_vStartCalibration(ADC_TypeDef* ADCx);
/************************************************************************************************************* */

void ADC_vGetCalibrationStatus(ADC_TypeDef* ADCx ,Flag_Status *pxStatus);
/************************************************************************************************************* */

void ADC_vGetConversionValue(ADC_TypeDef* ADCx , uint16 *pu16ADC_Val);
/************************************************************************************************************* */

Error_Status ADC_xSoftwareStartConv(ADC_TypeDef* ADCx, FunctionalState Copy_xSwStartState);
/************************************************************************************************************* */

void ADC_vGetSoftwareConvStatus(ADC_TypeDef* ADCx,Flag_Status *pxSwStartStatus);
/************************************************************************************************************* */

Error_Status ADC_xSetDMA(ADC_TypeDef* ADCx, FunctionalState Copy_xDMA_State);
/************************************************************************************************************* */

Flag_Status ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8 Copy_u8FLAG);
/************************************************************************************************************* */

Error_Status ADC_ClearFlag(ADC_TypeDef* ADCx, uint8 Copy_u8FLAG);
/************************************************************************************************************* */

Error_Status ADC_xDisalbe(ADC_TypeDef* ADCx);
/************************************************************************************************************* */

Error_Status ADC_xStart(ADC_TypeDef *ADCx);
/************************************************************************************************************* */

Error_Status ADC_xPollForConv(ADC_TypeDef *ADCx);

#endif /* ADC_INTERFACE_H_ */
