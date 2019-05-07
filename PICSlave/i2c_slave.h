/* 
 * File:   i2c_slave.h
 * Author: EE475
 *
 * Created on April 15, 2019, 11:15 AM
 */

#ifndef I2C_SLAVE_H
#define	I2C_SLAVE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define IF_SSP1             0x08
    #define PIN_SDA             0x10
    #define PIN_SCL             0x08
    
    #define PIN_MASK_I2C        PIN_SDA | PIN_SCL
    
    #define SLAVE_ADDR          0x78 << 1
    #define SLAVE_ADDR_MASK     0x7F << 1
    
    void I2C_Slave_Interrupt_Enable(void);
    void I2C_Slave_Initialize();
    
    void I2C_Slave_Interrupt();
    
    void I2C_Slave_Clear_Interrupt();
    
    unsigned char I2C_Read_Byte();
    
    unsigned char RW_Status();


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_SLAVE_H */

