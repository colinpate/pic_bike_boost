/* 
 * File:   fault_monitor.h
 * Author: Colin
 *
 * Created on December 5, 2025, 1:59 PM
 */

#ifndef FAULT_MONITOR_H
#define	FAULT_MONITOR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
// This runs when PWM updates
    
#define FAULT_CURRENT_THRESH 200 // 400mA
#define FAULT_CURRENT_DEBOUNCE 10 // pwm period is 8ms, so this would be 80ms
    
#define FAULT_VO_THRESH 1000 // 2V ADC reading
#define FAULT_VO_DEBOUNCE 10 // 80ms
    
void setup_fault_monitor();
void update_fault_monitor(uint16_t current, uint16_t v_out);
uint8_t is_fault_active(void);

#ifdef	__cplusplus
}
#endif

#endif	/* FAULT_MONITOR_H */

