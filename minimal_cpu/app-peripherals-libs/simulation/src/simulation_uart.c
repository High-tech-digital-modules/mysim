//
// Created by daniel on 26.1.23.
//

#include "app_uart.h"

#include <fcntl.h>

const char * userButton = "/tmp/userButton";

void clock_setup(void)
{
    // Nothing needed here
}

void usart_setup(void)
{
    // setup linux uart
}

void gpio_setup(void)
{
    int fd = open(userButton, O_WRONLY);

    write(fd, (uint8_t*)'0', 1);
    close(fd);
}

void button_setup(void)
{
    // Nothing to do here
}

uint16_t button_state(void) {
    int fd = open(userButton, O_RDONLY);
    char state[1];
    read(fd, state, sizeof(state));
    close(fd);
    return state[0] == '1' ? 1 : 0;
}

int _write(int file, char *ptr, int len)
{
    // Write into uart
    return -1;
}
