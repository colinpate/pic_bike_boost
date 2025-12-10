 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/power/power.h"
#include "current.h"
#include "pwm_control.h"
#include "fault_monitor.h"
#include "ui.h"

/*
    Main application
*/

current_model_t current_model;
ui_model_t ui_model;

uint8_t tick_flag_current;
uint8_t tick_flag_pwm;
uint8_t tick_flag_ui;
uint32_t tick_counter;

void tick(void){
    tick_counter += 1;
    if ((tick_counter % TICKS_PWM) == 0){
        tick_flag_pwm = 1;
    }
    if ((tick_counter % TICKS_CURRENT) == 0){
        tick_flag_current = 1;
    }
    if ((tick_counter % TICKS_UI) == 0){
        tick_flag_ui = 1;
    }
}

void init_ticks(void){
    tick_counter = 0;
    tick_flag_current = 0;
    tick_flag_pwm = 0;
    tick_flag_ui = 0;
    TMR1_OverflowCallbackRegister(tick);
}

void disable_outputs(){
    IO_RA1_SetDigitalInput(); // LED1
    IO_RA2_SetDigitalInput(); // LED2
    IO_RC4_SetDigitalInput(); // PWM
}

int main(void)
{
    //__delay_ms(500);
    setup_ui(&ui_model);

    while (1){

        SYSTEM_Initialize();
        
        init_ticks();
        setup_current(&current_model);
        setup_pwm();
        setup_fault_monitor();

        // Enable the Global Interrupts 
        INTERRUPT_GlobalInterruptEnable(); 

        // Enable the Peripheral Interrupts 
        INTERRUPT_PeripheralInterruptEnable();

        uint8_t go_to_sleep = 0;
        
        while(!go_to_sleep)
        {
            if (tick_flag_current){
                tick_flag_current = 0;
                update_current(&current_model);
            }
            if (tick_flag_pwm){
                tick_flag_pwm = 0;
                uint16_t current = get_latest_current(&current_model);
                update_fault_monitor(current);
                
                update_pwm(&current_model, is_fault_active());
            }
            if (tick_flag_ui) {
                tick_flag_ui = 0;
                go_to_sleep = update_ui(&ui_model);
            }
        }

        // disable the timer interrupt
        TMR1_Deinitialize();
        // turn the outputs to inputs
        disable_outputs();
        
        // Enable the interrupt
        IOCAN = 0x20;
        // sleep now
        POWER_LowPowerModeEnter();
        // Disable the interrupt
        IOCAN = 0x0;
    }
}