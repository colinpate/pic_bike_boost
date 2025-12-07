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
© [2025] Microchip Technology Inc. and its subsidiaries.

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
#include "current.h"
#include "pwm_control.h"
#include "fault_monitor.h"

/*
    Main application
*/

current_model_t current_model;

uint8_t tick_flag_current;
uint8_t tick_flag_pwm;
uint32_t tick_counter;

void tick(void){
    tick_counter += 1;
    if ((tick_counter % TICKS_PWM) == 0){
        tick_flag_pwm = 1;
    }
    if ((tick_counter % TICKS_CURRENT) == 0){
        tick_flag_current = 1;
    }
}

void init_ticks(void){
    tick_counter = 0;
    tick_flag_current = 0;
    tick_flag_pwm = 0;
    TMR1_OverflowCallbackRegister(tick);
}

uint16_t get_vo(){
    return ADC_ChannelSelectAndConvert(5);
}

int main(void)
{
    SYSTEM_Initialize();
    
    init_ticks();
    setup_current(&current_model);
    setup_pwm();
    setup_fault_monitor();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 
    
    set_target_current(100);
    
    while(1)
    {
        if (tick_flag_current){
            update_current(&current_model);
            tick_flag_current = 0;
        }
        if (tick_flag_pwm){
            IO_RA5_SetHigh();
            uint16_t current = get_latest_current(&current_model);
            uint16_t vo = get_vo();
            update_fault_monitor(current, vo);
            
            update_pwm(&current_model, is_fault_active());
            tick_flag_pwm = 0;
            IO_RA5_SetLow();
        }
    }
}