
#include "mcc_generated_files/system/system.h"
#include "fault_monitor.h"

uint16_t fault_counter;

void setup_fault_monitor(){
    fault_counter = 0;
}

void update_fault_monitor(uint16_t current, uint16_t v_out){
    if (fault_counter > 0){
        fault_counter -= 1;
    }
    if (current > FAULT_CURRENT_THRESH){
        fault_counter = FAULT_CURRENT_DEBOUNCE;
    }
    if (v_out > FAULT_VO_THRESH){
        fault_counter = FAULT_VO_DEBOUNCE;
    }
}

uint8_t is_fault_active(void){
    return (fault_counter > 0);
}