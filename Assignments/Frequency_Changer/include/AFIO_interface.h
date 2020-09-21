/*////////////////////////////////////////////////////////////////////////////// */
/* Author:  Eslam Ehab Aboutaleb                                                 */
/* Version: V01                                                                  */
/* Date: 	31-8-2020                                                            */
/*////////////////////////////////////////////////////////////////////////////// */

#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

#define AFIO_PortSourceGPIOA        ((uint8)0x00)
#define AFIO_PortSourceGPIOB        ((uint8)0x01)
#define AFIO_PortSourceGPIOC        ((uint8)0x02)
#define AFIO_PortSourceGPIOD        ((uint8)0x03)
#define AFIO_PortSourceGPIOE        ((uint8)0x04)
#define AFIO_PortSourceGPIOF        ((uint8)0x05)
#define AFIO_PortSourceGPIOG        ((uint8)0x06)

/************************************************************************************************************* */

/*AFIO GPIO Re-Map*/
#define AFIO_Remap_SPI1             ((uint32)0x00000001)  /*!< SPI1 Alternate Function mapping */
#define AFIO_Remap_I2C1             ((uint32)0x00000002)  /*!< I2C1 Alternate Function mapping */
#define AFIO_Remap_USART1           ((uint32)0x00000004)  /*!< USART1 Alternate Function mapping */
#define AFIO_Remap_USART2           ((uint32)0x00000008)  /*!< USART2 Alternate Function mapping */
#define AFIO_PartialRemap_USART3    ((uint32)0x00140010)  /*!< USART3 Partial Alternate Function mapping */
#define AFIO_FullRemap_USART3       ((uint32)0x00140030)  /*!< USART3 Full Alternate Function mapping */
#define AFIO_PartialRemapIM1        ((uint32)0x00160040)  /*!< TIM1 Partial Alternate Function mapping */
#define AFIO_FullRemapIM1           ((uint32)0x001600C0)  /*!< TIM1 Full Alternate Function mapping */
#define AFIO_PartialRemap1IM2       ((uint32)0x00180100)  /*!< TIM2 Partial1 Alternate Function mapping */
#define AFIO_PartialRemap2IM2       ((uint32)0x00180200)  /*!< TIM2 Partial2 Alternate Function mapping */
#define AFIO_FullRemapIM2           ((uint32)0x00180300)  /*!< TIM2 Full Alternate Function mapping */
#define AFIO_PartialRemapIM3        ((uint32)0x001A0800)  /*!< TIM3 Partial Alternate Function mapping */
#define AFIO_FullRemapIM3           ((uint32)0x001A0C00)  /*!< TIM3 Full Alternate Function mapping */
#define AFIO_RemapIM4               ((uint32)0x00001000)  /*!< TIM4 Alternate Function mapping */
#define AFIO_Remap1_CAN1            ((uint32)0x001D4000)  /*!< CAN1 Alternate Function mapping */
#define AFIO_Remap2_CAN1            ((uint32)0x001D6000)  /*!< CAN1 Alternate Function mapping */
#define AFIO_Remap_PD01             ((uint32)0x00008000)  /*!< PD01 Alternate Function mapping */
#define AFIO_RemapIM5CH4_LSI        ((uint32)0x00200001)  /*!< LSI connected to TIM5 Channel4 input capture for calibration */
#define AFIO_Remap_ADC1_ETRGINJ     ((uint32)0x00200002)  /*!< ADC1 External Trigger Injected Conversion remapping */
#define AFIO_Remap_ADC1_ETRGREG     ((uint32)0x00200004)  /*!< ADC1 External Trigger Regular Conversion remapping */
#define AFIO_Remap_ADC2_ETRGINJ     ((uint32)0x00200008)  /*!< ADC2 External Trigger Injected Conversion remapping */
#define AFIO_Remap_ADC2_ETRGREG     ((uint32)0x00200010)  /*!< ADC2 External Trigger Regular Conversion remapping */
#define AFIO_Remap_ETH              ((uint32)0x00200020)  /*!< Ethernet remapping (only for Connectivity line devices) */
#define AFIO_Remap_CAN2             ((uint32)0x00200040)  /*!< CAN2 remapping (only for Connectivity line devices) */
#define AFIO_Remap_SWJ_NoJTRST      ((uint32)0x00300100)  /*!< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
#define AFIO_Remap_SWJ_JTAGDisable  ((uint32)0x00300200)  /*!< JTAG-DP Disabled and SW-DP Enabled */
#define AFIO_Remap_SWJ_Disable      ((uint32)0x00300400)  /*!< Full SWJ Disabled (JTAG-DP + SW-DP) */
#define AFIO_Remap_SPI3             ((uint32)0x00201100)  /*!< SPI3/I2S3 Alternate Function mapping (only for Connectivity line devices) */
#define AFIO_RemapIM2ITR1_PTP_SOF   ((uint32)0x00202000)  /*!< Ethernet PTP output or USB OTG SOF (Start of Frame) connected
                                                                 to TIM2 Internal Trigger 1 for calibration
                                                                 (only for Connectivity line devices) */
#define AFIO_Remap_PTP_PPS          ((uint32)0x00204000)  /*!< Ethernet MAC PPS_PTS output on PB05 (only for Connectivity line devices) */

#define AFIO_RemapIM15              ((uint32)0x80000001)  /*!< TIM15 Alternate Function mapping (only for Value line devices) */
#define AFIO_RemapIM16              ((uint32)0x80000002)  /*!< TIM16 Alternate Function mapping (only for Value line devices) */
#define AFIO_RemapIM17              ((uint32)0x80000004)  /*!< TIM17 Alternate Function mapping (only for Value line devices) */
#define AFIO_Remap_CEC              ((uint32)0x80000008)  /*!< CEC Alternate Function mapping (only for Value line devices) */
#define AFIO_RemapIM1_DMA           ((uint32)0x80000010)  /*!< TIM1 DMA requests mapping (only for Value line devices) */

#define AFIO_RemapIM9               ((uint32)0x80000020)  /*!< TIM9 Alternate Function mapping (only for XL-density devices) */
#define AFIO_RemapIM10              ((uint32)0x80000040)  /*!< TIM10 Alternate Function mapping (only for XL-density devices) */
#define AFIO_RemapIM11              ((uint32)0x80000080)  /*!< TIM11 Alternate Function mapping (only for XL-density devices) */
#define AFIO_RemapIM13              ((uint32)0x80000100)  /*!< TIM13 Alternate Function mapping (only for High density Value line and XL-density devices) */
#define AFIO_RemapIM14              ((uint32)0x80000200)  /*!< TIM14 Alternate Function mapping (only for High density Value line and XL-density devices) */
#define AFIO_Remap_FSMC_NADV        ((uint32)0x80000400)  /*!< FSMC_NADV Alternate Function mapping (only for High density Value line and XL-density devices) */

#define AFIO_RemapIM67_DAC_DMA      ((uint32)0x80000800)  /*!< TIM6/TIM7 and DAC DMA requests remapping (only for High density Value line devices) */
#define AFIO_RemapIM12              ((uint32)0x80001000)  /*!< TIM12 Alternate Function mapping (only for High density Value line devices) */
#define AFIO_Remap_MISC             ((uint32)0x80002000)  /*!< Miscellaneous Remap (DMA2 Channel5 Position and DAC Trigger remapping,
                                                                 only for High density Value line devices) */

/************************************************************************************************************* */
/*AFIO Re-map states*/
#define AFIO_REMAP_DISABLE							  0
#define AFIO_REMAP_ENABLE							  1

/************************************************************************************************************* */
void AFIO_vReMap(uint32 Copy_u32GPIO_Remap ,uint8 Copy_u8RemapState);
void AFIO_vEXTILineConfig(uint8 Copy_u8EXTI_Line, uint8 Copy_u8PortNum);

#endif /* AFIO_INTERFACE_H */
