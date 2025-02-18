#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "registers.h"

#include "gpio.h"
#include "adafruit_qtpy_rp2040.h"

#define IS_RGBW true
#define NUM_PIXELS 150
#define PICO_DEFAULT_WS2812_POWER_PIN 11

#define QTPY_BOOT_PIN_NUM 21

#define Total_Presses 5

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 2
#endif


void set_neopixel_color(uint32_t color_num){
    uint32_t r_num = color_num >> 16;
    uint32_t g_num = color_num << 16;
    g_num = g_num >> 24;
    uint32_t b_num = color_num << 24;
    b_num = b_num >> 24;
    uint32_t color_final = ((r_num << 8) |
                            (g_num << 16)|
                            (b_num));
    pio_sm_put_blocking(pio0, 0, color_final << 8u);
}


int main() {
    volatile uint32_t QTPY_BOOT_PIN_REG = IO_BANK0_BASE + 0x0A8;
    
    const uint POWER_PIN_NAME = PICO_DEFAULT_WS2812_POWER_PIN;
    gpio_init(POWER_PIN_NAME);
    gpio_init(QTPY_BOOT_PIN_NUM);
    gpio_set_dir(POWER_PIN_NAME, GPIO_OUT);
    gpio_set_dir(QTPY_BOOT_PIN_NUM, GPIO_IN);
    gpio_put(POWER_PIN_NAME, 1);
    stdio_init_all();

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    while(!stdio_usb_connected());

    while(1){

        
        int counter = 0;
        int i = 0;
        int getcount[5] = {0};
        
        
        while (i < Total_Presses){
            uint32_t boot_status = register_read(QTPY_BOOT_PIN_REG);
            if(boot_status != 0){
                counter+=1;
            }else{
                if (counter != 0){
                    printf("%d\n", counter);
                    getcount[i] = counter;
                    i += 1;
                }
                counter = 0;
            }
            sleep_ms(100);
        }
        printf("\n");

    
        i = 0;
        uint32_t counter_in;
        while (i < 5){
            scanf("%d", &counter_in);
            set_neopixel_color(0xffafaf);
            sleep_ms(500);
            set_neopixel_color(0);
            sleep_ms(counter_in*50);
            i = i+1;
            printf("Replayed\n");
        }
        printf("Done\n");

        sleep_ms(100);
    }
}