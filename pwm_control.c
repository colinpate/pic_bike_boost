
#include "pwm_control.h"
#include "current.h"

void setup_pwm(void){
    // Enable high drive current on RC4 and 5
    HIDRVC = 0x30;
    
    set_target_current(0);
    
    uint16_t pwm_period = PWM_PERIOD;
    PWM5_PeriodSet(pwm_period); // set_dc loads the buffer so we don't need to
    
    set_dc(0);
}

void set_dc(int16_t dc){
    pwm_dc = (uint16_t) dc;
    PWM5_DutyCycleSet(pwm_dc);
    PWM5_LoadBufferSet();
}

void set_target_current(uint16_t new_target_current){
    if (new_target_current > MAX_TARGET_CURRENT){
        pwm_target_current = MAX_TARGET_CURRENT;
    } else {
        pwm_target_current = new_target_current;
    }
}

void update_dc(uint16_t read_current){
    int16_t increment = 0;
    int16_t new_dc = pwm_dc;
    
    if (read_current < CURRENT_DEADBAND){ // prevent unsigned int underflow
        if (pwm_target_current > CURRENT_DEADBAND){
            increment = PWM_POS_INC;
        }
    } else {
        if ((read_current + CURRENT_DEADBAND) < pwm_target_current){
            increment = PWM_POS_INC;
        } else if ((read_current - CURRENT_DEADBAND) > pwm_target_current){
            increment = PWM_NEG_INC;
        }
    }
    
    if ((new_dc + increment) < 0){
        new_dc = 0;
    } else if ((new_dc + increment) > MAX_PWM_DC) {
        new_dc = MAX_PWM_DC;
    } else {
        new_dc += increment;
    }
    
    set_dc(new_dc);
}

void update_pwm(current_model_t *c_model){
    if (is_current_valid(c_model)){
        update_dc(get_latest_current(c_model));
    } else {
        set_dc(0);
    }
}