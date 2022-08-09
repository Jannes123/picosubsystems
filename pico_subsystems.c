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
    LED_value = !LED_value;

    return 0;
}

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 9600

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

// GPIO defines
// Example uses GPIO 2
#define INPUT_BUTTON_MIDDLE 17

int main()
{
    struct repeating_timer jtimer;
    stdio_init_all();
    add_repeating_timer_ms(720, xtimer_callback, NULL, &jtimer);
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Setup UART
    uart_init(UART_ID, BAUD_RATE);
    
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    gpio_init(INPUT_BUTTON_MIDDLE);
    gpio_set_dir(INPUT_BUTTON_MIDDLE, GPIO_IN);

    puts("******uart test********");
    const uint led_pin_green = 25;//GPIO_25
    const uint led_pin_amber = 14;//GPIO_14 PIN_19
    const uint led_pin_yellow = 13;//GPIO_13 PIN_17
    gpio_init(led_pin_green);
    gpio_init(led_pin_amber);
    gpio_init(led_pin_yellow);
    gpio_set_dir(led_pin_green, GPIO_OUT);
    gpio_set_dir(led_pin_amber, GPIO_OUT);
    gpio_set_dir(led_pin_yellow, GPIO_OUT);
    while (true) {
            // Blink LED
            printf("Blinking!\r\n");
            gpio_put(led_pin_green, true);
            gpio_put(led_pin_amber, true);
            //gpio_put(led_pin_yellow, false);
            sleep_ms(1210);
            gpio_put(led_pin_green, false);
            gpio_put(led_pin_amber, false);
            //gpio_put(led_pin_yellow, true);
            sleep_ms(1210);
            gpio_put(led_pin_green, LED_value);
            gpio_put(led_pin_amber, LED_value);
            gpio_put(led_pin_yellow, LED_value);
            sleep_ms(1210);
        }

    return 0;
}
