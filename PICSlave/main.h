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
    
    // CONFIG1H
    #pragma config FOSC = INTIO7   // Oscillator Selection bits (Internal oscillator block)

    // CONFIG2H
    #pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
    #pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

    #define _XTAL_FREQ      16000000
    
    void delay(int val);
    void high_interrupt();
    
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

