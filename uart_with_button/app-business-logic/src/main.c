#include <stdio.h>
#include "app_uart.h"
#include "simulation.h"

int main(void) {
    clock_setup();
    gpio_setup();
    usart_setup();
    button_setup();

    printf("hello world!\n");
    uint8_t button_is_pressed = 0;

    while (1) {
        // On real chip it is empty doing nothing. On simulation there is 100us sleep to
        // avoid 100% cpu load
        SLEEP_SIM()
        if (!button_is_pressed && button_state()) {
            button_is_pressed = 1;
        } else if (button_is_pressed && !button_state()) {
            printf("button pressed\n");
            button_is_pressed = 0;
        }
    }

    return 0;
}
