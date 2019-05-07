#include "main.h"
#include "i2c.h"
#include "xc.h"

// Initializes SSP1 for I2C (MASTER configuration)
void I2C_Initialize(const unsigned long freq)
{
    PMD1 &= ~0x40;
    // Setup so that the initialization
    // does not effect UART / other
    // PORTC operations.
    PORTC &= ~PIN_MASK_I2C;
    LATC &= ~PIN_MASK_I2C;
    ANSELC &= ~PIN_MASK_I2C;
    TRISC |=  PIN_MASK_I2C; // Set RC4, RC3 TRIS = 1
    // Initialize I2C SSP bus 1
    SSP1CON1 = 0x28;
    SSP1CON2 = 0x00;
    SSP1CON3 &= ~0x3;
    SSP1ADD = (_XTAL_FREQ / (4 * freq)) - 1;
    
}

// Do nothing while not in idle (HALT program until I2C finishes)
void I2C_Hold(void) { while((!!(SSP1CON2 & 0x1F) | !!(SSP1STAT & 0x04))); }

// Begins a transmission with a START sequence
void I2C_Begin(void)
{ 
    I2C_Hold();
    SSP1CON2 |= 0x01; // START ENABLE (SEN)
    I2C_Hold();
}

// Ends transmission with a STOP sequence
void I2C_End(void)
{
    I2C_Hold();
    SSP1CON2 |= 0x04; // STOP ENABLE (PEN)
    I2C_Hold();
}

// Enables the receive control bit. Not sure if this is necessary.
void I2C_Receive_Enable(void)
{
    SSP1CON2 |= 0x08; // RECEIVE ENABLE (RCEN)   
}

// Repeated starts. Primarily for reading multiple registers
void I2C_Repeated_Start(void)
{
    SSP1CON2 |= 0x02; // REPEATED START COND (RSEN)
}

// For some reason, I don't see an ACK here. We can debug later
void I2C_ACK(unsigned char ack)
{
    // ACKDT is active low (inverted) / is ~ACK
    SSP1CON2 |= (((ack) ? 0: 1) << 5); // ACKDT Set
    SSP1CON2 |= 0x10; // ACK ENABLE (ACKEN)
}

// Simplest Write Command possible
void I2C_Write(unsigned char data)
{
    I2C_Begin();
    SSP1BUF = data;
    I2C_End();
}

// Returns whether or not an ACK was received on the last transmission
unsigned char ACK_Received() { return !!(SSP1CON2 & 0x40); }

// Check for ACK?
// Tested seems working
void I2C_Write_Multiple(unsigned char* data, unsigned char len)
{
    // Check inputs to be considered for Write_Multiple
    // Inputs must be > 0.
    if (len == 1) { I2C_Write(data[0]); }
    if (len < 2) { return; }
    
    I2C_Begin();
    for(int i = 0; i < len; i++)
    {
        SSP1BUF = data[i];
        I2C_Hold();
    }
    I2C_End();
    
}

// Simplest read command possible
unsigned char I2C_Read(unsigned char ack)
{
    unsigned char incoming;
    I2C_Begin();
    I2C_Receive_Enable();
    
    I2C_Hold();
    // Read Data
    incoming = SSP1BUF;
    
    I2C_Hold();
    
    I2C_ACK(ack);
    
    I2C_End();
    return incoming;
}

// Tested Seems working
// Writes a byte to a register on a particular device
void I2C_Write_Register(unsigned char addr, unsigned char reg, unsigned char data)
{
    unsigned char data_arr[3];
    
    data_arr[0] = (addr << 1) & ~0x01; // Write address
    data_arr[1] = reg;
    data_arr[2] = data;
    
    I2C_Write_Multiple(data_arr, 3);
}

// NOT IMPLEMENTED
// Writes 4 bytes starting at startAddr register
void I2C_Write4_Registers(unsigned char addr, 
    unsigned char startAddr, 
    unsigned char *data)
{
    
}

// Seems to work, no device to test with though
// Reads a byte from a specified device and register
unsigned char I2C_Read_Register(unsigned char addr, unsigned char reg)
{
    unsigned char incoming;
    // Setup register address
    I2C_Begin();
    SSP1BUF = (addr << 1) & ~0x01; // Write
    I2C_Hold();
    SSP1BUF = reg;
    I2C_End();
    
    I2C_Repeated_Start();
    
    I2C_Hold();
    SSP1BUF = (addr << 1) | 0x01; // Read
    I2C_Hold();
    
    I2C_Receive_Enable();
    
    I2C_Hold();
    incoming = SSP1BUF;
    I2C_Hold();
    
    // NACK to stop. Repeated reads require ACK, 
    // but currently this method does not support repeated reads
    I2C_ACK(0); 
    I2C_End();
    
    return incoming;
}

// Seems to work. No device to test on right now
// Reads 4 registers starting at the startAddr register
// Returns a pointer to the data.
// This pointer is in the stack, so we should probably change that
// Otherwise we will have weird overwriting bugs
// There is no heap on the PIC. At least no way to allocate it without
// Making our own memory management system.
unsigned char *I2C_Read4_Registers(unsigned char addr, unsigned char startAddr)
{
    unsigned char incoming[4];
    // Setup register address
    I2C_Begin();
    SSP1BUF = (addr << 1) & ~0x01; // Write
    I2C_Hold();
    SSP1BUF = startAddr;
    I2C_End();
    
    I2C_Repeated_Start();
    
    I2C_Hold();
    SSP1BUF = (addr << 1) | 0x01; // Read
    I2C_Hold();
    
    for (int i = 0; i < 4; i++) {
        I2C_Receive_Enable();

        I2C_Hold();
        incoming[i] = SSP1BUF;
        I2C_Hold();

        // NACK to stop. Repeated reads require ACK, 
        // but currently this method does not support repeated reads
        I2C_ACK(i < 3); 
        I2C_Hold();
    }
    I2C_End();
    
    return incoming;
}

