//
// Created by daniel on 26.1.23.
//

#define STM32F4

#include "app_uart.h"

#define RCC_BASE_ADDRESS 0x40023800
#define RCC_APB1ENR_OFFSET 0x40

// Define memory addresses for USART2 registers
#define USART2_BASE_ADDRESS 0x40004400
#define USART2_SR_OFFSET 0x00
#define USART2_DR_OFFSET 0x04
#define USART2_BRR_OFFSET 0x08
#define USART2_CR1_OFFSET 0x0C

// Define bit positions for USART2 registers
#define USART_SR_TXE_BIT_POSITION 7
#define USART_CR1_UE_BIT_POSITION 13
#define USART_CR1_TE_BIT_POSITION 3

// Define system clock frequency and UART baud rate
#define SYS_CLK_FREQUENCY 8000000
#define UART_BAUD_RATE 115200

void clock_setup(void)
{
    *((volatile uint32_t*)(RCC_BASE_ADDRESS + RCC_APB1ENR_OFFSET)) |= (1 << 17); // RCC_APB1ENR: USART2EN
}

void usart_setup(void)
{
    // Configure USART2 baud rate
    uint32_t brr = (SYS_CLK_FREQUENCY + UART_BAUD_RATE/2) / UART_BAUD_RATE;
    *((volatile uint32_t*)(USART2_BASE_ADDRESS + USART2_BRR_OFFSET)) = brr;

    // Configure USART2 control registers
    *((volatile uint32_t*)(USART2_BASE_ADDRESS + USART2_CR1_OFFSET)) |= (1 << USART_CR1_UE_BIT_POSITION); // Enable USART2
    *((volatile uint32_t*)(USART2_BASE_ADDRESS + USART2_CR1_OFFSET)) |= (1 << USART_CR1_TE_BIT_POSITION); // Enable USART2 transmitter
}

void usart2_transmit_char(char c)
{
    // Wait for the TXE flag in the SR register to be set
    while(!(*((volatile uint32_t*)(USART2_BASE_ADDRESS + USART2_SR_OFFSET)) & (1 << USART_SR_TXE_BIT_POSITION)));

    // Write the character to the DR register
    *((volatile uint32_t*)(USART2_BASE_ADDRESS + USART2_DR_OFFSET)) = c;
}

int _write(int file, char *ptr, int len)
{
    int i;

    if (file == STDOUT_FILENO || file == STDERR_FILENO) {
        for (i = 0; i < len; i++) {
            if (ptr[i] == '\n') {
                usart2_transmit_char('\r');
            }
            usart2_transmit_char(ptr[i]);
        }
        return i;
    }
    errno = EIO;
    return -1;
}
