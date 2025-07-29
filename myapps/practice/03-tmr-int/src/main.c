
// LED: PA8 (active low)

#include "CH58x_common.h"
#include <stdbool.h>

__INTERRUPT
__HIGH_CODE
void TMR1_IRQHandler()
{
  //
  if (TMR1_GetITFlag(TMR0_3_IT_CYC_END)) {
    GPIOA_InverseBits(GPIO_Pin_8);
    TMR1_ClearITFlag(TMR0_3_IT_CYC_END);
  }
}

int main()
{
  SetSysClock(CLK_SOURCE_PLL_60MHz);
  
  GPIOA_SetBits(GPIO_Pin_8);  // LED
  GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeOut_PP_5mA);
  
  TMR1_TimerInit(30000000); // for 500ms
  TMR1_ClearITFlag(TMR0_3_IT_CYC_END);
  TMR1_ITCfg(true, TMR0_3_IT_CYC_END); //RB_TMR_IE_CYC_END, first bit
  PFIC_EnableIRQ(TMR1_IRQn);
  TMR1_Enable();
  
  while (1);
}
