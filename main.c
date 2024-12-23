#include <stdbool.h>
#include <stdint.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>

#define UART_PORT (GPIOA)
#define TX_PIN (GPIO9)
#define RX_PIN (GPIO10)

int main() {
    // setup clock;
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);

    char *text = "Hello World!!!";

    // setup USART1 peripheral
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(UART_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, TX_PIN | RX_PIN);
    gpio_set_af(UART_PORT, GPIO_AF7, TX_PIN | RX_PIN);

    rcc_periph_clock_enable(RCC_USART1);

    usart_set_mode(USART1, USART_MODE_TX_RX);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
    usart_set_databits(USART1, 8);
    usart_set_baudrate(USART1, 115200);
    usart_set_parity(USART1, 0);
    usart_set_stopbits(USART1, 1);

    usart_enable(USART1);

    // send hello world
    for (char *c = text; *c != '\0'; c++) {
        usart_send_blocking(USART1, *c);
    }

    // infinite loop at end
    while (true) {
        asm("nop");
    }
}
