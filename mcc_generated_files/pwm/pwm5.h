/**
 * PWM5 Generated Driver API Header File
 * 
 * @file pwm5.h
 * 
 * @defgroup  pwm5 PWM5
 * 
 * @brief This is the generated header file for the PWM5 driver
 *
 * @version PWM5 Driver Version 1.0.0
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

#ifndef PWM5_H
#define PWM5_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>


/**
  Section: PWM5 APIs
*/

/**
 * @ingroup pwm5
 * @brief Initializes the PWM5 module. This routine is called only once during system initialization, before calling other APIs.
 * @param None.
 * @return None.
*/ 
void PWM5_Initialize(void);

/**
 * @ingroup pwm5
 * @brief Starts the PWM5 operation and must be called after the initialize routine is called.
 * @param None.
 * @return None.
*/ 
void PWM5_Start(void);

/**
 * @ingroup pwm5
 * @brief Stops the PWM5 operation and must be called after the start routine is called.
 * @param None.
 * @return None.
*/ 
void PWM5_Stop(void);

/**
 * @ingroup pwm5
 * @brief Check the output status of the PWM5 module and must be called after the start routine is called.
 * @param None.
 * @return True - Output High 
 * @return False - Output Low
*/ 
bool PWM5_CheckOutputStatus(void);

/**
 * @ingroup pwm5
 * @brief Loads the PWM5 buffer at the end of the period and must be called after the initialize routine is called.
 * @param None.
 * @return None.
*/ 
void PWM5_LoadBufferSet(void);

/**
 * @ingroup pwm5
 * @brief Sets the expected phase count for the PWM5 module.
 * @param phaseCount - 16-bit phase count
 * @return None.
*/ 
void PWM5_PhaseSet( uint16_t phaseCount);

/**
 * @ingroup pwm5
 * @brief Sets the expected duty cycle for the PWM5 module.
 * @param dutyCycleCount - 16-bit duty cycle count
 * @return None.
*/ 
void PWM5_DutyCycleSet(uint16_t dutyCycleCount);

/**
 * @ingroup pwm5
 * @brief Sets the expected period for the PWM5 module.
 * @param periodCount - 16-bit period count
 * @return None.
*/ 
void PWM5_PeriodSet(uint16_t periodCount);

/**
 * @ingroup pwm5
 * @brief Sets the required offset for the PWM5 module.
 * @param offsetCount - 16-bit offset count
 * @return None.
*/ 
void PWM5_OffsetSet(uint16_t offsetCount);

/**
 * @ingroup pwm5
 * @brief Reads the measured timer count of the PWM5 module.
 * @param None.
 * @return 16-bit timer count
*/ 
 uint16_t PWM5_timerCountGet(void);

/**
 * @ingroup pwm5
 * @brief Gets the status of the Offset Interrupt Flag bit (OFIF) of the PWM5 module.
 * @param None.
 * @return None.
*/ 
bool PWM5_IsOffsetMatchOccured(void);

/**
 * @ingroup pwm5
 * @brief Gets the status of the Phase Interrupt Flag bit (PHIF) of the PWM5 module.
 * @param None.
 * @return True - PWMTMR count is higher than or equal to the PWMPH value
 * @return False - PWMTMR count is lower than the PWMPH value
*/ 
bool PWM5_IsPhaseMatchOccured(void);

/**
 * @ingroup pwm5
 * @brief Gets the status of the Duty Cycle Interrupt Flag bit (DCIF) of the PWM5 module.
 * @param None.
 * @return True - PWMTMR count is higher than or equal to the PWMDC value
 * @return False - PWMTMR count is lower than the PWMDC value
*/ 
bool PWM5_IsDutyCycleMatchOccured(void);

/**
 * @ingroup pwm5
 * @brief Gets the status of the Period Interrupt Flag bit (PRIF) of the PWM5 module.
 * @param None.
 * @return True - PWMTMR count is higher than or equal to the PWMPR value
 * @return False - PWMTMR count is lower than the PWMPR value
*/ 
bool PWM5_IsPeriodMatchOccured(void);


#endif // PWM5_H
/**
 End of File
*/
