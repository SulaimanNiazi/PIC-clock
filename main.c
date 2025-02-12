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

int main(void){
    //Initialization of pins and ports
    
    displayPortDIR = 0x00;
    displayPort = 0x00;
    
    uint8_t digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0;
    
    //Initialization of Timer
    
    T1CON = 0x01;
    TMR1 = 0;

    uint16_t count = 0;
    
    while(1){
        if(PIR1bits.TMR1IF){
            PIR1bits.TMR1IF = 0;
            count++;
            if(count >= 76){
                count = 0;
                if(digit4 == 9){
                    digit4 = 0;
                    if(digit3 == 5){
                        digit3 = 0;
                        if(digit2 == 9){
                            digit2 = 0;
                            if((digit2 == 3)&&(digit1 == 2)){
                                digit2 = 0;
                                digit1 = 0;
                            }
                            else{
                                digit1++;
                            }
                        }
                        else{
                            digit2++;
                        }
                    }
                    else{
                        digit3++;
                    }
                }
                else{
                    digit4++;
                }
            }
        }
        displayPort = digit4;
        showDigit(4);
        displayPort = digit3;
        showDigit(3);
        displayPort = digit2;
        showDigit(2);
        displayPort = digit1;
        showDigit(1);
    }
}
