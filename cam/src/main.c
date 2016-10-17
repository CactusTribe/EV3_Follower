#include "main.h"

int main(void)
{

  CPU_CACHE_Enable();

  HAL_Init();
  
  SystemClock_Config();

  BSP_LED_Init(LED1);

}
