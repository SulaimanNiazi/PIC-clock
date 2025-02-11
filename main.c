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

void showDigit(uint16_t digit){
    displayPort &= 0x0F;
    displayPort |= 0x10 << (digit - 1);
}

void main(void) {
    //Initialization of pins and ports
    
    displayPortDIR = 0x00;
    displayPort = 0x00;
    
    uint8_t digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0;
    
    //Initialization of Timer
    
    OPTION_REG = 0x0F;
    TMR0 = 0 ;
    uint16_t count = 0;
    
    while(1){
        if(TMR0IF){
            TMR0IF = 0;
            count++;
            if(count >= 152){
                count = 0;
                digit4++;
            }
        }
        if(digit4 > 9){
            digit4 = 0;
            digit3++;
            if(digit3 > 6){
                digit3 = 0;
                digit2++;
                if(digit2 > 9){
                    digit2 = 0;
                    digit1++;
                }
                else if((digit2 == 4)&&(digit1 == 2)){
                    digit2 = 0;
                    digit1 = 0;
                }
            }
        }
        displayPort = digit4;
        showDigit(4);
        __delay_ms(1);
        displayPort = digit3;
        showDigit(3);
        __delay_ms(1);
        displayPort = digit2;
        showDigit(2);
        __delay_ms(1);
        displayPort = digit1;
        showDigit(1);
        __delay_ms(1);
    }
}
