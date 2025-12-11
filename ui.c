
#include "mcc_generated_files/system/system.h"
#include "pwm_control.h"
#include "ui.h"

void setup_ui(ui_model_t* ui_model){
    ui_model->brightness = BRIGHTNESS_25;
    ui_model->button_press_count = 0;
    ui_model->filtered_battery_voltage = BATT_UNDERVOLTAGE_RELEASE;
    ui_model->led_count = 0;
    ui_model->battery_undervoltage = 0;
    ui_model->overtemperature = 0;
}

void update_battery_voltage(ui_model_t* ui_model){
    uint16_t raw_battery_voltage = ADC_ChannelSelectAndConvert(BATT_V_ADC_CHANNEL);
    ui_model->filtered_battery_voltage -= (ui_model->filtered_battery_voltage >> 3);
    ui_model->filtered_battery_voltage += raw_battery_voltage >> 3;
}

uint8_t get_max_current (ui_model_t* ui_model){
    uint8_t max_current = 255;
    update_battery_voltage(ui_model);
    if (ui_model->filtered_battery_voltage < BATT_UNDERVOLTAGE){
        ui_model->battery_undervoltage = 1;
        max_current = BATT_UNDERVOLTAGE_MAX_CURRENT;
    } else if (ui_model->battery_undervoltage) {
        if (ui_model->filtered_battery_voltage >= BATT_UNDERVOLTAGE_RELEASE){
            ui_model->battery_undervoltage = 0;
        } else {
            max_current = BATT_UNDERVOLTAGE_MAX_CURRENT;
        }
    }
    return max_current;
}

uint8_t update_state_from_button(ui_model_t* ui_model){
    uint8_t go_to_sleep = 0;

    uint8_t button_notpressed = IO_RA5_GetValue();

    if (!button_notpressed){
        if (ui_model->button_press_count > 0){
            if (ui_model->button_press_count > BUTTON_PRESS_COUNT_POWER){
                // button was held for long enough that we should toggle power
                if (ui_model->brightness == BRIGHTNESS_SLEEP){
                    ui_model->brightness = BRIGHTNESS_25;
                } else {
                    ui_model->brightness = BRIGHTNESS_SLEEP;
                    go_to_sleep = 1; // break the outer loop
                }
                ui_model->button_press_count = 0;
            } else {
                ui_model->button_press_count += 1;
            }
        } else {
            ui_model->button_press_count = 1;
        }
    } else {
        if (ui_model->button_press_count > 0){
            // short press - cycle brightness
            switch (ui_model->brightness){
                case BRIGHTNESS_25:
                    ui_model->brightness = BRIGHTNESS_50;
                    break;
                case BRIGHTNESS_50:
                    ui_model->brightness = BRIGHTNESS_100;
                    break;
                case BRIGHTNESS_100:
                    ui_model->brightness = BRIGHTNESS_25;
                    break;
                default:
                    ui_model->brightness = BRIGHTNESS_SLEEP;
                    go_to_sleep = 1;
                    break;
            }
        } else if (ui_model->brightness == BRIGHTNESS_SLEEP){
            go_to_sleep = 1;
        }
        ui_model->button_press_count = 0;
    }

    return go_to_sleep;
}

void set_status_leds(uint16_t red_pwm_level, bool off){
    if (off){
        IO_RA1_SetDigitalInput();
        IO_RA2_SetDigitalInput();
    } else {
        if (!DEBUG){
            IO_RA1_SetDigitalOutput(); // Set the PGCLK pin to input if debugging
        }
        IO_RA2_SetDigitalOutput();
        
        PWM3_LoadDutyValue(red_pwm_level);
    }
}

uint16_t batt_level_to_pwm(uint16_t batt_level){
    uint16_t pwm_out = 0;
    if (batt_level <= BATT_EMPTY){
        pwm_out = 0;
    } else if (batt_level >= BATT_FULL){
        pwm_out = 1023;
    } else {
        batt_level -= BATT_EMPTY;
        uint32_t batt_scaled = ((uint32_t) batt_level) << 10;
        pwm_out = batt_scaled / (BATT_FULL - BATT_EMPTY);
    }
    pwm_out = 1023 - pwm_out; // We're driving the red LED
    return pwm_out;
}

uint8_t update_ui(ui_model_t* ui_model, bool fault){
    uint8_t go_to_sleep = update_state_from_button(ui_model);

    if (!go_to_sleep){
        uint8_t target_current = ui_model->brightness;
        uint8_t max_current = get_max_current(ui_model);
        if (target_current > max_current) {
            target_current = max_current; 
        }
        set_target_current(target_current);

        // set status LEDs
        if (ui_model->battery_undervoltage || fault){
            uint16_t blink_pwm = 1023;
            if (fault) blink_pwm = 511;
            if (ui_model->led_count  & 0x8) {
                set_status_leds(0, true);
            } else {
                set_status_leds(blink_pwm, false);
            }
        } else {
            set_status_leds(batt_level_to_pwm(ui_model->filtered_battery_voltage), false);
        }
        ui_model->led_count += 1;
    } else {
        set_target_current(0);
    }

    return go_to_sleep;
}