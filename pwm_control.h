/* 
 * File:   pwm_control.h
 * Author: Colin
 *
 * Created on December 4, 2025, 6:47 PM
 */
#include "mcc_generated_files/system/system.h"
#include "current.h"

#ifndef PWM_CONTROL_H
#define	PWM_CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TICKS_PWM 100 // 100Hz at 10kHz tick
    
#define MAX_TARGET_CURRENT 100 // 200mV at 2.048mV per ADC step
#define PWM_PERIOD 2000 // 213 // 150kHz
#define MAX_PWM_DC 128 // DC of 0.6 at 213 steps (150kHz)
#define PWM_POS_INC 1 // 0 to 100% DC in 2.13s at 100Hz update
#define PWM_NEG_INC -2 // 100 to 0% DC in 1.07s at 100Hz update
#define CURRENT_DEADBAND 10 // 20mV
    
int16_t pwm_dc;
uint16_t pwm_target_current;

void setup_pwm(void);
void set_dc(int16_t dc);
void set_target_current(uint16_t new_target_current);
void update_dc(uint16_t read_current);
void update_pwm(current_model_t *c_model);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_CONTROL_H */

