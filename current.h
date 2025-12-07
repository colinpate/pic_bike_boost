/* 
 * File:   current.h
 * Author: Colin
 *
 * Created on December 4, 2025, 6:35 PM
 */
#include "mcc_generated_files/system/system.h"

#ifndef CURRENT_H
#define	CURRENT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TICKS_CURRENT 4 // 2kHz
    
#define CURRENT_HISTORY_LENGTH (16)
#define CURRENT_HISTORY_SHIFT (4)
#define CURRENT_ADC_CHANNEL ADC_CHANNEL_AN6
    
typedef struct {
    uint16_t filtered_current;
    uint16_t history[CURRENT_HISTORY_LENGTH];
    uint16_t history_pos;
    uint32_t history_sum;
    uint16_t valid_count;
    uint8_t is_valid;
} current_model_t;

void setup_current(current_model_t *c_model);

uint8_t is_current_valid(current_model_t *c_model);

uint16_t update_current(current_model_t *c_model);

uint16_t get_latest_current(current_model_t *c_model);

#ifdef	__cplusplus
}
#endif

#endif	/* CURRENT_H */

