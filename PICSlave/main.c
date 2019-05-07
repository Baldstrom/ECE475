/*
 * File:   main.c
 * Author: EE475
 *
 * Created on April 9, 2019, 5:32 PM
 */
#include "main.h"
#include "i2c_slave.h"
#include <xc.h>

/*
 * SURGICAL SLAVE / REMOTE NODE
 */

void main(void) {
    
    // Setup debug port
    PORTA = 0x00;
    ANSELA = 0x00;
    TRISA = 0x00; 
    
    // Setup read debug data
    unsigned char data = 0;
    
    // Setup I2C 
    I2C_Slave_Initialize();
    
    // Initialize Debug LOW
    LATA = 0x00;
    
    while(1)
    {   
        //data = I2C_Read_Byte();
        //LATA = 0x0;
        __delay_ms(1);
        
        //LATA |= ((data) == 0x56);//RW_Status() != 0x0;//

    }
    
}

void delay(int val) { for (int i = 0; i < val; i++); }

void __interrupt (high_priority) high_interrupt()
{
    // Check which interrupt and select ISR accordingly
    if (PIR1 & 0x08) { I2C_Slave_Interrupt(); return; }
}