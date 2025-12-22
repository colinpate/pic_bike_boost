/* 
 * File:   pwm_control.h
 * Author: Colin
 *
 * Created on December 4, 2025, 6:47 PM
 */
#include "mcc_generated_files/system/system.h"
#include "current.h"
#include "global_defs.h"

#ifndef PWM_CONTROL_H
#define	PWM_CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif
    
int16_t pwm_dc;

void setup_pwm(void);
void set_dc(int16_t dc);
void set_target_current(uint16_t new_target_current);
void update_dc(uint16_t read_current, uint16_t target_current);
void update_pwm(uint16_t current, uint16_t target_current, bool disable);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_CONTROL_H */

