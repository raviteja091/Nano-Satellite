#include "cmsis_os.h"
#include "i2c.h"
#include "usart.h"
#include "ltr390.h"
#include "tsl2591.h"
#include "flash.h"

void SystemClock_Config(void);

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_FLASH_Init();

  LTR390_Init(&hi2c1);
  TSL2591_Init(&hi2c1);

  while (1) {
    float uv = LTR390_ReadUV();
    uint16_t ir = TSL2591_ReadFullLux();
    char buf[64];
    int len = snprintf(buf, sizeof(buf), "UV:%.2f IR:%u\r\n", uv, ir);
    HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, HAL_MAX_DELAY);
    osDelay(2000);
  }
}
