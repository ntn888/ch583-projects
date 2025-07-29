
// TMR1/PWM1/CAP1: PA10 (active low)

#include "CH58x_common.h"
#include <stdbool.h>

#define PWM_FREQ  1000
#define PWM_PRD   FREQ_SYS/PWM_FREQ
// 0 -> 60,000
#define PWM_STEP  600
// 600: 100 steps
#define DELAY_STEP 50
// 5 second fade in

int main()
{
  int32_t d = 0;
  bool rising = true;
  
  SetSysClock(CLK_SOURCE_PLL_60MHz);
  
  GPIOA_SetBits(GPIO_Pin_10); // PWM OUT
  GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
  
  TMR1_PWMInit(Low_Level, PWM_Times_1); // Note: PWMX_PolarTypeDef defined in CH58x_pwm.h
                      // Need to init before setting PWMCycleCfg & PWMActDataWidth
  TMR1_PWMCycleCfg(PWM_PRD);
  //TMR1_PWMActDataWidth(PWM_PRD*PWM_DUTY); // MAX value: TMR1_PWMCycleCfg above (for 100%)
  TMR1_PWMActDataWidth(d); // MAX value: TMR1_PWMCycleCfg above (for 100%)
  TMR1_PWMEnable(); // enables output pin, configured above
  TMR1_Enable();
  
  while (1) {
    
    if (rising == true) {
      
      DelayMs(DELAY_STEP);
      d += PWM_STEP;
      
      if (d == PWM_PRD)
        rising = false;
      
      TMR1_Disable();
      TMR1_PWMActDataWidth(d);
      TMR1_Enable();
    
    } else {
      
      DelayMs(DELAY_STEP);
      d -= PWM_STEP;
      
      if (d == 0)
        rising = true;
      
      TMR1_Disable();
      TMR1_PWMActDataWidth(d);
      TMR1_Enable();
    }
  }
  
}
