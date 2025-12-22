
#include "mcc_generated_files/system/system.h"
#include "pwm_control.h"
#include "ui.h"

void setup_ui(ui_model_t* ui_model){
    ui_model->state = ST_SLEEP;
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

uint8_t check_battery_voltage(ui_model_t* ui_model){
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
    } else if (ui_model->filtered_battery_voltage < BATT_UNDERVOLTAGE_RELEASE){
        max_current = BATT_LOWVOLTAGE_MAX_CURRENT;
    }
    return max_current;
}

void update_state_from_button(ui_model_t* ui_model){
    uint8_t button_notpressed = IO_RA5_GetValue();

    switch (ui_model->state){
        case ST_SLEEP:
            if (button_notpressed == 0){
                ui_model->button_press_count = 0;
                ui_model->state = ST_BUTTON_WAKE;
            }
            break;
        
        case ST_BUTTON_WAKE:
            if (button_notpressed){
                ui_model->state = ST_SLEEP;
            } else {
                if (ui_model->button_press_count > BUTTON_PRESS_COUNT_POWER){
                    ui_model->state = ST_BUTTON_WAKE_WAIT;
                } else {
                    ui_model->button_press_count += 1;
                }
            }
            break;

        case ST_BUTTON_WAKE_WAIT:
            if (button_notpressed){
                ui_model->state = ST_ON;
            }
            break;

        case ST_ON:
            if (button_notpressed == 0){
                ui_model->state = ST_BUTTON_PRESSED;
                ui_model->button_press_count = 0;
            }
            break;

        case ST_BUTTON_PRESSED:
            if (button_notpressed){
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
                        ui_model->brightness = BRIGHTNESS_25;
                        break;
                }
                ui_model->state = ST_ON;
            } else {
                if (ui_model->button_press_count > BUTTON_PRESS_COUNT_POWER){
                    ui_model->state = ST_SLEEP;
                } else {
                    ui_model->button_press_count += 1;
                }
            }
            break;

        default:
            ui_model->state = ST_SLEEP;
            break;
    }
}

void set_outputs(
    ui_model_t* ui_model, 
    bool fault, 
    bool* go_to_sleep,
    uint8_t* target_current
){
    *go_to_sleep = false;
    uint8_t current_limit = check_battery_voltage(ui_model);

    if (ui_model->brightness > current_limit){
        *target_current = current_limit;
    } else {
        *target_current = ui_model->brightness;
    }

    switch (ui_model->state){
        case ST_SLEEP:
            *go_to_sleep = true;
            *target_current = 0;
            break;

        case ST_BUTTON_WAKE:
            *target_current = 0;
            break;
    }
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

void update_status_leds(ui_model_t* ui_model, bool fault){
    if (ui_model->state == ST_SLEEP){
        set_status_leds(0, true);
        return;
    }
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
}

void update_ui(
    ui_model_t* ui_model, 
    bool fault, 
    bool* go_to_sleep,
    bool* disable_pwm,
    uint8_t* target_current
){
    update_state_from_button(ui_model);
    set_outputs(ui_model, fault, go_to_sleep, disable_pwm, target_current);
    update_status_leds(ui_model, fault);
}