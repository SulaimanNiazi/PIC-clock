/*
 * File:   main.c
 * Author: Sulaiman Niazi
 *
 * Created on February 11, 2025, 9:03 PM
 */

//**Define pins and ports**

#define displayPort PORTB
#define displayPortDIR TRISB

//*************************

#define _XTAL_FREQ 20000000
#include <xc.h>

void main(void) {
    //Initialization of pins and ports
    
    displayPortDIR = 0x00;
    displayPort = 0x00;
    
    while(1){
        
    }
}
