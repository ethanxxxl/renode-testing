#include "libopencm3/stm32/f4/rcc.h"
#include <stdbool.h>
#include <stdint.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/usart.h>

int main() {
    // setup clock;
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);

    char *text = "Hello World!!!";

    // setup USART1 peripheral
    rcc_periph_clock_enable(RCC_USART1);
    usart_enable(USART1);
    usart_set_baudrate(USART1, 9600);
    usart_set_mode(USART1, USART_MODE_TX);
    usart_set_parity(USART1, 0);
    usart_set_databits(USART1, 8);

    // send hello world
    for (char *c = text; *c != '\0'; c++) {
        usart_send_blocking(USART1, *c);
    }

    // infinite loop at end
    while (true) {
        asm("nop");
    }
}
