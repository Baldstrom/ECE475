/* 
 * File:   main.h
 * Author: EE475
 *
 * Created on April 11, 2019, 12:51 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif


    #define _XTAL_FREQ      16000000

    #define SLAVE_ADDR 0x78

    /** 
     * Possibility values for Control
     */
     enum control_options {
      OFF = 0x0,
      ON =  0x1
    };
    /**
     * The index and corresponding meaning
     */
     enum registers {
       MOTOR_SPEED = 0x0,
       CONTROL = 0x1,
       SETPOINT = 0x2,
       SLAVE_STATUS = 0x3,
       VOLTAGE_SENSE = 0x4
     };


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

