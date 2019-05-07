/*
 * File:   main.c
 * Author: EE475
 *
 * Created on April 17, 2019, 3:45 PM
 * This uses the device library from C18
 */


#include <p18f25k22.h>
#include <i2c.h>
#include <delays.h>

// CONFIG1H
#pragma config FOSC = INTIO7   // Oscillator Selection bits (Internal oscillator block)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

void main(void) {    
    char slave_address = 0x78;
    unsigned char result = 0;
    OpenI2C(MASTER, SLEW_OFF);
    
    IdleI2C1();                         // Wait until the bus is idle
    StartI2C1();                        // Send START condition
    IdleI2C1(); 
    
    while (1){
        result = 0;
        LATA = result;
        Delay10KTCYx(250);
        result = WriteI2C( slave_address & 0xfe );  // Send address with R/W cleared for write
        LATA |= result;
        Delay10KTCYx(250);
        IdleI2C1();                         // Wait for ACK
    }
    
    return;
}
