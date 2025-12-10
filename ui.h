/* 
 * File:   ui.h
 * Author: Colin
 *
 * Created on December 7, 2025, 10:49 PM
 */

#ifndef UI_H
#define	UI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/system/system.h"

#define TICKS_UI 256 // 31Hz

#define BATT_V_ADC_CHANNEL 4 // AN4
#define BATT_UNDERVOLTAGE 100
#define BATT_UNDERVOLTAGE_RELEASE 110
#define BATT_UNDERVOLTAGE_MAX_CURRENT 0

#define BUTTON_PRESS_COUNT_POWER 20 // 0.7s at 31Hz

#define LED_BLINK_PERIOD 16 // 0.5s at 31Hz

typedef enum
{
    BRIGHTNESS_SLEEP = 0,
    BRIGHTNESS_25 = 25,
    BRIGHTNESS_50 = 50,
    BRIGHTNESS_100 = 100,
} brightness_mode_t;

typedef struct {
    brightness_mode_t brightness;
    uint8_t button_press_count;
    uint8_t led_count;
    uint16_t filtered_battery_voltage;
    uint8_t battery_undervoltage;
    uint8_t overtemperature;
} ui_model_t;

void setup_ui(ui_model_t* ui_model);
void update_battery_voltage(ui_model_t* ui_model);
uint8_t get_max_current (ui_model_t* ui_model);
uint8_t update_ui(ui_model_t* ui_model);
uint8_t update_state_from_button(ui_model_t* ui_model);

#ifdef	__cplusplus
}
#endif

#endif	/* UI_H */

