#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "pico_subsystems.h"

#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

#define HIGH 1
#define LOW 0
#define INPUT 1
#define OUTPUT 0

//input ADC thresholds
#define input_allowedRange 100//the allowed range around each expected value

const uint led_pin_green = 25;//GPIO_25 PIN_37
const uint led_pin_amber = 14;//GPIO_2 PIN_
const uint led_pin_yellow = 13;//GPIO_2 PIN_

bool LED_value = false;

bool xtimer_callback(struct repeating_timer *jtimer_ptr) {
    if(LED_value){
        LED_value = false;
    }
    else{
        LED_value = true;
    }
    return true;
}

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 1
#define UART_RX_PIN 2

// GPIO defines
// Example uses GPIO 2
#define INPUT_BUTTON_MIDDLE 16

int main(){
    repeating_timer_t jtimer;
    int countie = 0;
    stdio_init_all();
    add_repeating_timer_ms(1200, xtimer_callback, NULL, &jtimer);
    //spi_init(SPI_PORT, 1000*1000);
    //gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    //gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    //gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    //gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    //gpio_set_dir(PIN_CS, GPIO_OUT);
    //gpio_put(PIN_CS, 1);

    //i2c_init(I2C_PORT, 400*1000);
    
    //gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    //gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    //gpio_pull_up(I2C_SDA);
    //gpio_pull_up(I2C_SCL);

    // Setup UART
    uart_init(UART_ID, BAUD_RATE);
    
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    gpio_init(INPUT_BUTTON_MIDDLE);
    gpio_set_dir(INPUT_BUTTON_MIDDLE, GPIO_IN);

    puts("******uart test********");
    printf("YEAH!!");
    const uint led_pin_green_onboard = 25;//GPIO_25
    const uint led_pin_green_th = 14;//GPIO_14 PIN_19
    const uint led_pin_yellow = 13;//GPIO_13 PIN_17
    gpio_init(led_pin_green_onboard);
    gpio_init(led_pin_green_th);
    gpio_init(led_pin_yellow);
    gpio_set_dir(led_pin_green_onboard, GPIO_OUT);
    gpio_set_dir(led_pin_green_th, GPIO_OUT);
    gpio_set_dir(led_pin_yellow, GPIO_OUT);
    while (true) {
            // Blink LED
            printf("syncing.\r\n");
            printf(" count:  %d", countie);
            countie = countie + 1;
            if(LED_value){
                printf("ON");
            }
            //else{
            //    printf("OFF");
            //}
            sleep_ms(110);
            gpio_put(led_pin_green_onboard, LED_value);
            sleep_ms(110);
            gpio_put(led_pin_green_th, LED_value);
            sleep_ms(110);
            gpio_put(led_pin_yellow, LED_value);
            sleep_ms(110);
            gpio_put(led_pin_green_onboard, false);
        }

    return 0;
}
