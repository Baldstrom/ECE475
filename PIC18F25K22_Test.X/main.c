/*
 * File:   main.c
 * Author: EE475
 *
 * Created on April 9, 2019, 5:32 PM
 */
#include "main.h"
#include "i2c.h"
#include "uart.h"
#include <xc.h>

// CONFIG1H
#pragma config FOSC = INTIO7   // Oscillator Selection bits (Internal oscillator block)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

static unsigned char CURRENT_SLAVE_STATUE = 0;
static unsigned char CURRENT_VOLTAGE_SENSE= 0;

void delay(int val);

/*
 * SURGICAL MASTER / LOCAL NODE
 */

void main(void) {
    // Setup I2C
    I2C_Initialize(400000);
    // Setup UART (RC6 TX1, RC7 RX1)
    UART_Initialize();
    
    unsigned char data[4] = { 0x56, 0x00, 0xFF, 0x92 };
    
    while(1)
    {
		UART_Write(data[0]);


		/*
        I2C_Write_Register(SLAVE_ADDR, CONTROL, ON);
        __delay_ms(100);
        I2C_Write_Register(SLAVE_ADDR, MOTOR_SPEED, 0x20);
        __delay_ms(100);
        I2C_Write_Register(SLAVE_ADDR, SETPOINT, 0x7F);
        __delay_ms(100);
        CURRENT_SLAVE_STATUE = I2C_Read_Register(SLAVE_ADDR, SLAVE_STATUS);
        __delay_ms(100);
        CURRENT_VOLTAGE_SENSE = I2C_Read_Register(SLAVE_ADDR, VOLTAGE_SENSE);
		*/
    }
    
    
}

void delay(int val) { for (int i = 0; i < val; i++); }