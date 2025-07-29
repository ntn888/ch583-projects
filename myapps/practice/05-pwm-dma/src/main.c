
// TMR1/PWM1/CAP1: PA10 (active low)

#include "CH58x_common.h"
#include <stdbool.h>

#define PWM_FREQ  1000
#define PWM_PRD   FREQ_SYS/PWM_FREQ
// 0 -> 60,000
#define PWM_STEP  240
// 125 steps
#define TABLE_SIZE 500

uint32_t step_table[TABLE_SIZE];    // need to use 32bit register to match 'FIFO' reg

void load_dma()
{
  uint16_t i = 0;
  for (uint32_t n = 0; n < PWM_PRD; n += PWM_STEP) {
    step_table[i] = n;
    i++;
  }
  for (uint32_t n = PWM_PRD; n > 0; n -= PWM_STEP) {
    step_table[i] = n;
    i++;
  }
}

int main()
{
  
  SetSysClock(CLK_SOURCE_PLL_60MHz);
  
  load_dma();
  
  GPIOA_SetBits(GPIO_Pin_10); // PWM OUT
  GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
  
  TMR1_PWMInit(Low_Level, PWM_Times_8); // Note: PWMX_PolarTypeDef defined in CH58x_pwm.h
                      // Need to init before setting PWMCycleCfg & PWMActDataWidth
  TMR1_DMACfg(ENABLE, (uint16_t)(uint32_t)step_table, (uint16_t)(uint32_t)&step_table[TABLE_SIZE], true);
  TMR1_PWMCycleCfg(PWM_PRD);
  TMR1_PWMActDataWidth(0); // MAX value: TMR1_PWMCycleCfg above (for 100%)
  TMR1_PWMEnable(); // enables output pin, configured above
  TMR1_Enable();
  
  while (1);
  
}
