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
	
	// setup UART 
	TRISCbits.TRISC6 = 0; // TX as output 
	TRISCbits.TRISC7 = 1; // RX as input
	TXSTA1bits.SYNC = 0; // Async operation 
	TXSTA1bits.TX9 = 0; // No tx of 9th bit 
	TXSTA1bits.TXEN = 1; // Enable transmitter
	RCSTA1bits.RX9 = 0; // No rx of 9th bit 
	RCSTA1bits.CREN = 1; // Enable receiver 
	
	BAUDCON1bits.BRG16 = 0; // Divisor at 8 bit 
	TXSTA1bits.BRGH = 0; // No high-speed baudrate
    RCSTA1bits.SPEN = 1; // Enable serial port

	OSCCON |= 0x60; // select 4MHz
	// Fosc /4 /(n+1) = baudrate
	SPBRG1 = 12; // divisor value for 9600


}

void UART_Write(unsigned char data) {
	// wait the end of transmission 
	while (TXSTA1bits.TRMT == 0) {}; 
	TXREG1 = data; // start sending the new byte
}
unsigned char UART_Read() {
	while (PIR1bits.RC1IF == 0) { // wait for char 
		if (RCSTA1bits.OERR == 1) { 
		RCSTA1bits.OERR = 0; // clear overrun if it occurs 
		RCSTA1bits.CREN = 0; 
		RCSTA1bits.CREN = 1; 
		} 
	} 
	return RCREG1;
}

