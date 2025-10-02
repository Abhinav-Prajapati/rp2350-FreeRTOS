#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

const uint LED_PIN = PICO_DEFAULT_LED_PIN;

void blink_task(void *params) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1); 
        vTaskDelay(500 / portTICK_PERIOD_MS); 
        gpio_put(LED_PIN, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS); 
    }
}

int main() {
    stdio_init_all();

    xTaskCreate(blink_task, "BlinkTask", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();

    while (true);
}