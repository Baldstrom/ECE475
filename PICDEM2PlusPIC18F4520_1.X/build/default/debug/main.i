# 1 "main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "main.c" 2
# 10 "main.c"
# 1 "./pic18f452-custom.h" 1



#pragma config CONFIG4L = 0x05
#pragma config WDT = 0
# 11 "main.c" 2

void delay();

void delay() {
    int counter = 0;
    for (counter = 0; counter<1000; counter++) {
        ;
    }
}

void main(void) {


    int count = 0;



    *(volatile unsigned long *) 0xF81 = 0x00;
    *(volatile unsigned long *) 0xF8A = 0x00;

    *(volatile unsigned long *) 0xF93 = 0x00;

    while (1) {


        *(volatile unsigned long *) 0xF81 = count;

        delay();

        count++;
    }
}
