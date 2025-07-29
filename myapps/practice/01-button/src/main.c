
// LED: PA8 (active low)
// BUT: PB22 (active low, no pullup)

#include "CH58x_common.h"

int main()
{
  SetSysClock(CLK_SOURCE_PLL_60MHz);
  
  GPIOA_SetBits(GPIO_Pin_8);  // LED
  GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeOut_PP_5mA);
  
  GPIOB_ModeCfg(GPIO_Pin_22, GPIO_ModeIN_PU);  // Button
  
  while(1) {
    if (GPIOB_ReadPortPin(GPIO_Pin_22))
      GPIOA_SetBits(GPIO_Pin_8);
    else
      GPIOA_ResetBits(GPIO_Pin_8);
  }
  
}

