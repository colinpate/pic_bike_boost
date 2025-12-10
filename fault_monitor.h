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
    
#include "global_defs.h"
    
// This runs when PWM updates
    
uint16_t get_vo();
void setup_fault_monitor();
void update_fault_monitor(uint16_t filtered_current);
uint8_t is_fault_active(void);

#ifdef	__cplusplus
}
#endif

#endif	/* FAULT_MONITOR_H */

