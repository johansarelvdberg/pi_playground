
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "ws28128-rpi/ws2812-rpi-defines.h"
#include "ws28128-rpi/ws2812-rpi.h"

#define FLAG_VALUE 123

void core1_entry()
{

    multicore_fifo_push_blocking(FLAG_VALUE);

    uint32_t g = multicore_fifo_pop_blocking();

    if (g != FLAG_VALUE)
        printf("Hmm, that's not right on core 1!\n");
    else
        printf("Its all gone well on core 1!");

    while (1)
        tight_loop_contents();
}

int main()
{
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else    
    constexpr uint LED_PIN = PICO_DEFAULT_LED_PIN;
    NeoPixel<LED_PIN>  pixel;
    //gpio_init(LED_PIN);
    //gpio_set_dir(LED_PIN, GPIO_OUT);

    multicore_launch_core1(core1_entry);

    uint32_t g = multicore_fifo_pop_blocking();

    if (g != FLAG_VALUE)
        printf("Hmm, that's not right on core 0!\n");
    else
    {
        multicore_fifo_push_blocking(FLAG_VALUE);
        printf("It's all gone well on core 0!");
    }

    uint32_t color_index = 0;
    while (true)
    {
        pixel.show(color_index);
        sleep_ms(500);
        ++color_index;
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        //sleep_ms(250);
    }
#endif
}