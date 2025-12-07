/**
 * PWM5 Generated Driver File
 * 
 * @file pwm5.c
 * 
 * @ingroup pwm5
 * 
 * @brief This is the generated driver implementation file for the PWM5 driver.
 *
 * @version PWM5 Driver Version 1.0.0
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "../pwm5.h"
static void (*PWM5_Callback)(void);

/**
  Section: PWM5 APIs
*/

void PWM5_Initialize(void)
{
  //PRIE disabled; DCIE disabled; PHIE disabled; OFIE disabled; 
  PWM5INTE = 0x0;

  // PRIF cleared; DCIF cleared; PHIF cleared; OFIF cleared; 
  PWM5INTF = 0x0;

  // CLKSEL FOSC; PRESC No_Prescalar; 
  PWM5CLKCON = 0x0;

  // LD do_not_load; 
  PWM5LDCON = 0x0;

  // OFTOUTMC match_decrementing; 
  PWM5OFCON = 0x0;

  // PWMPHH 0; 
  PWM5PHH = 0x0;

  // PWMPHL 0; 
  PWM5PHL = 0x0;

  // PWMDCH 1; 
  PWM5DCH = 0x1;

  // PWMDCL 131; 
  PWM5DCL = 0x83;

  // PWMPRH 12; 
  PWM5PRH = 0xC;

  // PWMPRL 154; 
  PWM5PRL = 0x9A;

  // PWMOFH 252; 
  PWM5OFH = 0xFC;

  // PWMOFL 4; 
  PWM5OFL = 0x4;

  // PWMTMRH 0x0; 
  PWM5TMRH = 0x0;

  // PWMTMRL 0x0; 
  PWM5TMRL = 0x0;

  //Clear interrupt flag


  //PWMEN enabled; PWMMODE standard_PWM; PWMPOL active_hi; 
  PWM5CON = 0x80;
}

void PWM5_Start(void)
{
  PWM5CONbits.EN = 1;
}

void PWM5_Stop(void)
{
  PWM5CONbits.EN = 0;
}

bool PWM5_CheckOutputStatus(void)
{
  return (PWM5CONbits.OUT);
}

void PWM5_LoadBufferSet(void)
{
  PWM5LDCONbits.LDA=1;
}

void PWM5_PhaseSet(uint16_t phaseCount)
{
  PWM5PHH = (uint8_t)(phaseCount>>8);
  PWM5PHL = (uint8_t)(phaseCount);
}

void PWM5_DutyCycleSet(uint16_t dutyCycleCount)
{
  PWM5DCH = (uint8_t)(dutyCycleCount>>8);
  PWM5DCL = (uint8_t)(dutyCycleCount);
}

void PWM5_PeriodSet(uint16_t periodCount)
{
  PWM5PRH = (uint8_t)(periodCount>>8);
  PWM5PRL = (uint8_t)(periodCount);
}

void PWM5_OffsetSet(uint16_t offsetCount)
{
  PWM5OFH = (uint8_t)(offsetCount>>8);
  PWM5OFL = (uint8_t)(offsetCount);
}

uint16_t PWM5_timerCountGet(void)
{
  return (((uint16_t) (PWM5TMRH<<8)| PWM5TMRL));
}

bool PWM5_IsOffsetMatchOccured(void)
{
  return (PWM5INTFbits.OFIF);
}

bool PWM5_IsPhaseMatchOccured(void)
{
  return (PWM5INTFbits.PHIF);
}

bool PWM5_IsDutyCycleMatchOccured(void)
{
  return (PWM5INTFbits.DCIF);
}

bool PWM5_IsPeriodMatchOccured(void)
{
  return (PWM5INTFbits.PRIF);
}


/**
 End of File
*/