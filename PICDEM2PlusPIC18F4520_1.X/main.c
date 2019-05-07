/*
 * File:   main.c
 *
 * Created on August 16, 2010, 12:09 PM
 */

//#include "p18cxxx.h"
//#include <xc.h>
//#include <pic18f452.h>
#include "pic18f452-custom.h"

void delay();

void delay() {
    int counter = 0;
    for (counter = 0; counter<1000; counter++) {
        ;
    }
}

void main(void) {
    
    // Implement GPIO counter on PORTB
    int count = 0;
    
    //Configure PORTB
    // CLEAR LATCHES
    PORTB_REG = 0x00;
    PORTB_LAT = 0x00;
    // SET OUTPUTS
    PORTB_TRIS = 0x00;
    
    while (1) {
        
        // Set PORTB output to the current count
        PORTB_REG = count;
        
        delay();
        
        count++;
    }
}


