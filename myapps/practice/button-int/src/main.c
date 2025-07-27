
// LED: PA8 (active low)
// BUT: PB22 (active low, no pullup)

#include "CH58x_common.h"

__INTERRUPT
__HIGH_CODE
void GPIOB_IRQHandler()
{
  if (GPIOB_ReadITFlagBit(GPIO_Pin_8)) {
    GPIOA_InverseBits(GPIO_Pin_8);
    GPIOB_ClearITFlagBit(GPIO_Pin_8);
  }
}

int main()
{
  SetSysClock(CLK_SOURCE_PLL_60MHz);
  
  GPIOA_SetBits(GPIO_Pin_8);  // LED
  GPIOA_ModeCfg(GPIO_Pin_8, GPIO_ModeOut_PP_5mA);
  
  GPIOB_ModeCfg(GPIO_Pin_22, GPIO_ModeIN_PU); // button
  GPIOB_ITModeCfg(GPIO_Pin_8, GPIO_ITMode_FallEdge);  // PB8 mux'd as PB22 see below
  GPIOB_ClearITFlagBit(GPIO_Pin_8);
  GPIOPinRemap(ENABLE, RB_PIN_INTX); // <================== workaround, as R16_PB_INT reg is 16b wide
  PFIC_EnableIRQ(GPIO_B_IRQn);
  
  while (1);
  
}

