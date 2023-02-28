#include "app_uart.h"

int main(void) {
    clock_setup();
    usart_setup();

    uint32_t lCounter = 0;
    while (1) {
        lCounter++;
        if(lCounter % 1000000 == 0) {
            printf("I am alive\n");
        }
    }

    return 0;
}
