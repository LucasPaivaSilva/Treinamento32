#include <stdlib.h>
#include <driver/adc.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

int Hall_Read = 0;

void setup()
{
    // Configura a GPIO 
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    io_conf.pin_bit_mask = GPIO_NUM_12;
    gpio_config(&io_conf);

    // Configura o ADC
    adc1_config_width(ADC_WIDTH_BIT_12);
}

void loop()
{
    while (1)
    {
        gpio_set_level(12, 0);
        vTaskDelay(Hall_Read / portTICK_PERIOD_MS);
        gpio_set_level(12, 1);
        vTaskDelay(Hall_Read / portTICK_PERIOD_MS);
        Hall_Read = hall_sensor_read();
        printf("Hall_Read: %d\n", Hall_Read);
        if (Hall_Read < 0){
            Hall_Read = Hall_Read * -1;
        }
        Hall_Read = Hall_Read + 1;
        // Hall_Read = adc1_get_raw(ADC1_CHANNEL_2);
    } 

}

void app_main() {
    setup();
    loop(); 
}