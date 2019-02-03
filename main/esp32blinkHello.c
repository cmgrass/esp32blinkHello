/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#define BLINK_GPIO 4
#define BLINK_DELAY 500

#define HELLO_DELAY 2000

#define TID_BLINK "blink_task"
#define TID_HELLO "hello_task"

void blink_task(void *pvParameter)
{
  /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
     muxed to GPIO on reset already, but some default to other
     functions and need to be switched to GPIO. Consult the
     Technical Reference for a list of pads and their default
     functions.)
  */
  gpio_pad_select_gpio(BLINK_GPIO);

  /* Set the GPIO as a push/pull output */
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

  while (1) {
    /* Blink off (output low) */
    gpio_set_level(BLINK_GPIO, 0);
    vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS);

    /* Blink on (output high) */
    gpio_set_level(BLINK_GPIO, 1);
    vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS);
  }
}

void hello_task(void *pvParameter)
{
  while (1) {
    printf("--Hello World--\n");
    printf("  btw, here are some infos:\n");
#if 0
    printf("  portTICK_PERIOD_MS:%d\n", portTICK_PERIOD_MS);
    printf("  BLINK_GPIO        :%d\n", BLINK_GPIO);
    printf("  GPIO_MODE_OUTPUT  :%d\n", GPIO_MODE_OUTPUT);
    printf("  TID_BLINK:        :%s\n", TID_BLINK);
    printf("  TID_HELLO:        :%s\n", TID_HELLO);
    printf("\n\n");
#endif

    vTaskDelay(HELLO_DELAY / portTICK_PERIOD_MS);
  }
}

void app_main()
{
  xTaskCreate(&blink_task, TID_BLINK, configMINIMAL_STACK_SIZE, NULL, 10, NULL);
#if 1
  xTaskCreate(&hello_task, TID_HELLO, configMINIMAL_STACK_SIZE, NULL, 5, NULL);
#endif
}
