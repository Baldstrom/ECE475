#include "i2c_slave.h"
#include "main.h"
#include "xc.h"

void I2C_Slave_Interrupt_Enable()
{
    // Enable priority interrupts
    RCON |= 0x80;
    // Enable global and peripheral interrupts
    INTCON |= 0xC0;
    // Enable interrupt on SSP1
    PIE1 |= 0x08;
    // Set SSP1 to high priority interrupt
    IPR1 |= 0x08;
    // Set interrupt enable bit for start
    SSP1CON3 |= 0x60;
}

void I2C_Slave_Initialize()
{
    PMD1 = 0x00; // Enable all peripherals because why not
    // Setup so that the initialization
    // does not effect UART / other
    // PORTC operations.
    PORTC &= ~PIN_MASK_I2C;
    LATC &= ~PIN_MASK_I2C;
    ANSELC &= ~PIN_MASK_I2C;
    TRISC |= PIN_SDA; // Set RC4 TRIS = 2
    TRISC |= PIN_SCL; // Set RC3 TRIS = 1
    
    // Initialize I2C SSP bus 1
    SSP1STAT = 0x00;
    SSP1ADD = SLAVE_ADDR;
    SSP1MSK = SLAVE_ADDR_MASK;
    SSP1CON1 = 0x2E; 
    SSP1CON2 = 0x00;
    SSP1CON3 = 0x00;
    
    
    // clear the slave interrupt flag
    PIR1bits.SSP1IF = 0;
    // enable the master interrupt
    PIE1bits.SSP1IE = 1;
   
    
    I2C_Slave_Interrupt_Enable();
    I2C_Slave_Clear_Interrupt();
}

// 1 for R, 0 for W
unsigned char RW_Status() {return SSP1STAT & 0x4;} 

// 0 for in progress, 1 for completed
unsigned char Buffer_Status() {return  SSP1STAT & 0x01;} 

// read 1 registers
unsigned char I2C_Read_Byte() 
{   
    // for multiple bytes, repeat this process.
    // match address


    unsigned char check = SSP1BUF;

    // wait for start
    while(!(SSP1STAT & 0x8)); // will stuck here
    unsigned char reg3 = SSP1STAT;
    // SSP1ADD = 0x78;

    
    // for multiple bytes, repeat this process.
    // wait to address finish
    //__delay_ms(10);
     //while(!Buffer_Status());
    unsigned char reg1 = SSP1STAT;
    PIR1 &= ~0x8;
    
    
    
    //__delay_ms(10);
    // wait for data
    //while(!Buffer_Status());
    // clear interrupt flag;
    PIR1 &= ~0x8;
    // CKP = 1, releasing SCL1
    SSP1CON1 |= 0x10;
    while(!Buffer_Status());
    
    unsigned char data = SSP1BUF;
    unsigned char reg2 = SSP1STAT;
    
    
    // wait for stop bit
    // while(!(SSP1STAT & 0x10));
    return check == ((data & reg1) | (reg2 & reg3));
}

void I2C_Slave_Clear_Interrupt() { PIR1 &= ~IF_SSP1; }

// Compiler should set the interrupt vector table automatically
// from what I have read.
void I2C_Slave_Interrupt()
{
    // Clear interrupt status
    I2C_Slave_Clear_Interrupt();
    LATA = 0xFF;
    __delay_ms(10);
    LATA = 0x00;
    return;
}

void I2C_Write_Data(unsigned char reg) 
{
    // wait for start
    while(!(SSP1STAT & 0x8));
    
    
    PIR1 &= 0x8;
    SSP1BUF = reg;
    
    
    
}



