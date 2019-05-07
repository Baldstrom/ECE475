#ifndef PIC18F452_CUSTOM
#define PIC18F452_CUSTOM

#pragma config CONFIG4L = 0x05
#pragma config WDT = 0    

// PORTA
#define PORTA_REG       *(volatile unsigned long *) 0xF80
#define PORTA_TRIS      *(volatile unsigned long *) 0xF92
#define PORTA_LAT       *(volatile unsigned long *) 0xF89

// PORTB
#define PORTB_REG       *(volatile unsigned long *) 0xF81
#define PORTB_TRIS      *(volatile unsigned long *) 0xF93
#define PORTB_LAT       *(volatile unsigned long *) 0xF8A

// PORTC
#define PORTC_REG       (volatile unsigned long *) 0xF82
#define PORTC_TRIS      (volatile unsigned long *) 0xF94
#define PORTC_LAT       (volatile unsigned long *) 0xF8B

// PORTD
#define PORTD_REG       (volatile unsigned long *) 0xF83
#define PORTD_TRIS      (volatile unsigned long *) 0xF95
#define PORTD_LAT       (volatile unsigned long *) 0xF8C

// PORTE
#define PORTE_REG       (volatile unsigned long *) 0xF84
#define PORTE_TRIS      (volatile unsigned long *) 0xF96
#define PORTE_LAT       (volatile unsigned long *) 0xF8D

#endif