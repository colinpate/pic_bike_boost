/**
 * ADC Type Definitions Header File
 *
 * @file adc_types.h
 *
 * @defgroup adc ADC
 *
 * @brief This file provides type definitions for the Analog-to-Digital Converter (ADC) module.
 *
 * @version ADC Driver Version 3.0.0
 * 
 * @version ADC Package Version 4.0.0
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef ADC_TYPES_H
#define	ADC_TYPES_H

// Section: Macros

/**
 @ingroup adc
 @brief ADC resolution value.
*/
#define ADC_RESOLUTION 10U

/**
 @ingroup adc
 @brief ADC bit set value.
*/
#define ADC_BIT_SET 1U

/**
 @ingroup adc
 @brief ADC bit clear value.
*/
#define ADC_BIT_CLEAR 0U

// Section: Types

/**
 @ingroup adc
 @typedef adc_result_t
 @brief ADC conversion result type.
*/
typedef int16_t adc_result_t;

// Section: Enumerations

/**
 * @ingroup adc
 * @enum adc_channel_t
 * @brief Describes the available Analog-to-Digital Converter (ADC) channels.
*/
typedef enum
{
    ADC_CHANNEL_DAC3_OUTPUT =  0x1b, /**< DAC3_Output*/ 
    ADC_CHANNEL_TEMP =  0x1d, /**< Temp*/ 
    ADC_CHANNEL_DAC1_OUTPUT =  0x1e, /**< DAC1_Output*/ 
    ADC_CHANNEL_FVRBUFFER1 =  0x1f, /**< FVRBuffer1*/ 
    ADC_CHANNEL_AN6 =  0x6 /**< IO_R6: AN6*/ 
} adc_channel_t;

/**
 * @ingroup adc
 * @typedef adc_trigger_source_t 
 * @brief Lists the ADC auto-trigger sources.
 */
typedef enum
{
    ADC_TRIGGER_SOURCE_NO_AUTO_TRIGGER = 0x0, /**< No_auto_trigger*/  
    ADC_TRIGGER_SOURCE_TMR0_OVERFLOW = 0x1, /**< TMR0_overflow*/  
    ADC_TRIGGER_SOURCE_TMR1_OVERFLOW = 0x2, /**< TMR1_overflow*/  
    ADC_TRIGGER_SOURCE_TMR2_POSTSCALED = 0x3, /**< TMR2_postscaled*/  
    ADC_TRIGGER_SOURCE_TMR3_OVERFLOW = 0x4, /**< TMR3_overflow*/  
    ADC_TRIGGER_SOURCE_TMR4_POSTSCALED = 0x5, /**< TMR4_postscaled*/  
    ADC_TRIGGER_SOURCE_TMR5_OVERFLOW = 0x6, /**< TMR5_overflow*/  
    ADC_TRIGGER_SOURCE_TMR6_POSTSCALED = 0x7, /**< TMR6_postscaled*/  
    ADC_TRIGGER_SOURCE_C1OUT = 0x8, /**< C1OUT*/  
    ADC_TRIGGER_SOURCE_C2OUT = 0x9, /**< C2OUT*/  
    ADC_TRIGGER_SOURCE_CLC1 = 0xc, /**< CLC1*/  
    ADC_TRIGGER_SOURCE_CLC2 = 0xd, /**< CLC2*/  
    ADC_TRIGGER_SOURCE_CLC3 = 0xe, /**< CLC3*/  
    ADC_TRIGGER_SOURCE_CCP1 = 0xf, /**< CCP1*/  
    ADC_TRIGGER_SOURCE_PWM3OUT = 0x11, /**< PWM3OUT*/  
    ADC_TRIGGER_SOURCE_PWM5_DC5_MATCH = 0x13, /**< PWM5_DC5_match*/  
    ADC_TRIGGER_SOURCE_PWM5_PR5_MATCH = 0x14, /**< PWM5_PR5_match*/  
    ADC_TRIGGER_SOURCE_PWM5_PH5_MATCH = 0x15, /**< PWM5_PH5_match*/  
    ADC_TRIGGER_SOURCE_PWM5_OF5_MATCH = 0x16 /**< PWM5_OF5_match*/  
} adc_trigger_source_t ;

#endif // ADC_TYPES_H