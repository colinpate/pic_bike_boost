
#include "mcc_generated_files/system/system.h"
#include "fault_monitor.h"

uint16_t fault_counter;

uint16_t get_vo(){
    return ADC_ChannelSelectAndConvert(VO_ADC_CHANNEL);
}

void setup_fault_monitor(){
    fault_counter = 0;
}

void update_fault_monitor(uint16_t filtered_current){
    if (fault_counter > 0){
        fault_counter -= 1;
    }
    if (filtered_current > FAULT_CURRENT_THRESH){
        fault_counter = FAULT_CURRENT_DEBOUNCE;
    }
    if (get_vo() > FAULT_VO_THRESH){
        fault_counter = FAULT_VO_DEBOUNCE;
    }
}

uint8_t is_fault_active(void){
    return (fault_counter > 0);
}