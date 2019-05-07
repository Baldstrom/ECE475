#include "main.h"
#include "uart.h"
#include "xc.h"

void UART_Initialize()
{
    // Setup pins so that the initialization
    // does not effect UART / other
    // PORTC operations.
    // Pins should bein EUSART1 config afterwards
    PORTC &= ~PIN_MASK_UART;
    ANSELC &= ~PIN_MASK_UART;
    TRISC |= PIN_MASK_UART;
    LATC &= ~PIN_MASK_UART;
    
    // Setup EUSART control registers
    
}

