/* 
 * File:   global_defs.h
 * Author: Colin
 *
 * Created on December 10, 2025, 12:00 PM
 */

#ifndef GLOBAL_DEFS_H
#define	GLOBAL_DEFS_H

#ifdef	__cplusplus
extern "C" {
#endif

//
    
#define DEBUG false

// pwm_control

#define TICKS_PWM 64 // 125Hz
    
#define MAX_TARGET_CURRENT 200 // 400mV = 2A
#define PWM_PERIOD 213 // 150kHz
#define MAX_PWM_DC 128 // DC of 0.6 at 213 steps (150kHz)
#define PWM_POS_INC 1
#define PWM_NEG_INC -2
#define CURRENT_DEADBAND 4 // 40mA on either side
    
// ui

#define TICKS_UI 256 // 31Hz

#define BATT_V_ADC_CHANNEL 4 // AN4
    
#define BATT_UNDERVOLTAGE 555 // 6.4V
#define BATT_UNDERVOLTAGE_RELEASE 590 // 6.8V
#define BATT_EMPTY 590
#define BATT_FULL 710
    
#define BATT_UNDERVOLTAGE_MAX_CURRENT 0

#define BUTTON_PRESS_COUNT_POWER 30 // 31Hz

#define LED_BLINK_PERIOD 16 // 0.5s at 31Hz

// fault_monitor
    
#define VO_ADC_CHANNEL 5 // AN5
    
#define FAULT_CURRENT_THRESH 300 // 1.5A (0.2mV/mA)
#define FAULT_CURRENT_DEBOUNCE 10 // pwm period is 8ms, so this would be 80ms
    
#define FAULT_VO_THRESH 260 // 2V ADC reading (22Vo)
#define FAULT_VO_DEBOUNCE 10 // 80ms
    
// current
    
#define TICKS_CURRENT 4 // 2kHz
    
#define CURRENT_HISTORY_LENGTH (16)
#define CURRENT_HISTORY_SHIFT (4)
#define CURRENT_ADC_CHANNEL ADC_CHANNEL_AN6
    
//
    
#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_DEFS_H */

