/* 
 * File:   i2c.h
 * Author: EE475
 *
 * Created on April 10, 2019, 9:36 AM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define PIN_MASK_I2C   0x18

    void I2C_Initialize(const unsigned long freq);
    void I2C_Hold(void);
    void I2C_Begin(void);
    void I2C_End(void);
    void I2C_Receive_Enable(void);
    void I2C_Repeated_Start(void);
    void I2C_ACK(unsigned char ack);
    unsigned char ACK_Received();
    
    void I2C_Write(unsigned char data);
    void I2C_Write_Multiple(unsigned char* data, unsigned char len);
    unsigned char I2C_Read(unsigned char ack);
    
    void I2C_Write_Register(unsigned char addr, unsigned char reg, unsigned char data);
    unsigned char I2C_Read_Register(unsigned char addr, unsigned char reg);
    
    void I2C_Write4_Registers(unsigned char addr, 
        unsigned char startAddr, 
        unsigned char *data);
    unsigned char *I2C_Read4_Registers(unsigned char addr, 
        unsigned char startAddr);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */


