#include "current.h"

void setup_current(current_model_t *c_model){
    // Disable weak pull-ups on port C
    WPUC = 0;
    c_model->filtered_current = 0;
    for (int i=0; i<CURRENT_HISTORY_LENGTH; i++){
        c_model->history[i] = 0;
    }
    c_model->history_pos = 0;
    c_model->history_sum = 0;
    c_model->is_valid = 0;
}

uint8_t is_current_valid(current_model_t *c_model){
    return c_model->is_valid;
}

uint16_t read_current_adc(){
    uint16_t adc_result = ADC_ChannelSelectAndConvert(CURRENT_ADC_CHANNEL);
    return adc_result;
}

uint16_t update_current(current_model_t *c_model){
    uint16_t adc_reading = read_current_adc();
    // update the filter (boxcar FIR)
    c_model->history_sum += adc_reading;
    uint8_t next_pos;
    if (c_model->history_pos == (CURRENT_HISTORY_LENGTH - 1)){
        next_pos = 0;
        c_model->is_valid = 1;
    } else {
        next_pos = c_model->history_pos + 1;
    }
    c_model->history_sum -= c_model->history[next_pos];
    c_model->history_pos = next_pos;
    c_model->history[c_model->history_pos] = adc_reading;
    
    return c_model->history_sum >> CURRENT_HISTORY_SHIFT;
}

uint16_t get_latest_current(current_model_t *c_model){
    return c_model->history_sum >> CURRENT_HISTORY_SHIFT;
}