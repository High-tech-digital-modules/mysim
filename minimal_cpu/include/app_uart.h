//
// Created by daniel on 26.1.23.
//

#ifndef MYSIM_APP_UART_H
#define MYSIM_APP_UART_H

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

/* Forward declarations */
int _write(int file, char *ptr, int len);

extern void clock_setup(void);

extern void usart_setup(void);

#endif //MYSIM_APP_UART_H
