/*
 * File:   main.c
 * Author: Sulaiman Niazi
 *
 * Created on February 11, 2025, 9:03 PM
 */

//**Define pins and ports**

#define displayPort PORTB
#define displayPortDIR TRISB
#define modePin PORTDbits.RD0
#define modePinDIR TRISDbits.TRISD0
#define nextDigitPin PORTDbits.RD1
#define nextDigitPinDIR TRISDbits.TRISD1
#define prevDigitPin PORTDbits.RD2
#define prevDigitPinDIR TRISDbits.TRISD2
#define CCPclockPin PORTCbits.RC2
#define CCPclockPinDIR TRISCbits.TRISC2

//*************************

#define _XTAL_FREQ 20000000
#include <xc.h>
#include <builtins.h>
#include <pic16f877a.h>

uint16_t interruptCount = 0;

void showDigit(uint16_t digit){
    displayPort &= 0x0F;
    if(digit > 0){
        displayPort |= 0x10 << (digit - 1);
    }
}

int main(void){
    //Initialization of pins and ports
    
    displayPortDIR = 0x00;
    displayPort = 0x00;
    modePinDIR = 1;
    nextDigitPinDIR = 1;
    prevDigitPinDIR = 1;
    
    //Initialization of Timer1 and CCP1 module
    
    CCPclockPinDIR = 1;
    while(!CCPclockPin){
        __delay_ms(500);
        break;
    }
    if(CCPclockPin){
        INTCONbits.GIE = 1;
        INTCONbits.PEIE = 1;    //enable all peripheral interrupts
        PIE1bits.CCP1IE = 1;
        PIR1bits.CCP1IF = 0;
        CCP1CON = 0x05;         //capture mode every rising edge
    }
    else{
        T1CON = 0x31;           //16-bit timer, internal clock, 1:8 prescaler
        TMR1H = 0x0B;           //65536 - 3036 = 62500
        TMR1L = 0xDB;
    }

    //Initialization of variables

    uint16_t sec = 0, mode = 0, selectedDigitNo;
    uint8_t digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0;
    
    while(1){
        while(mode == 0){
            if(modePin){
                __delay_ms(10);
                if(modePin){
                    while(modePin);
                    mode = 1;
                }
            }
            if(PIR1bits.TMR1IF){
                PIR1bits.TMR1IF = 0;
                interruptCount++;
            }

            if(interruptCount > 9){
                interruptCount = 0;
                if(sec == 59){
                    sec = 0;
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
                else{
                    sec++;
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

        interruptCount = 0, selectedDigitNo = 1;
        
        while(mode == 1){
            if(modePin){
                __delay_ms(10);
                if(modePin){
                    while(modePin);
                    mode = 2;
                }
            }
            if(nextDigitPin){
                __delay_ms(10);
                if(nextDigitPin){
                    selectedDigitNo++;
                    while(nextDigitPin);
                }
            }
            if(prevDigitPin){
                __delay_ms(10);
                if(prevDigitPin){
                    selectedDigitNo--;
                    while(prevDigitPin);
                }
            }
            
            switch(selectedDigitNo){
                case 0: selectedDigitNo = 4; break;
                case 1: displayPort = digit1; break;
                case 2: displayPort = digit2; break;
                case 3: displayPort = digit3; break;
                case 4: displayPort = digit4; break;
                case 5: selectedDigitNo = 1; break;
            }
            showDigit(selectedDigitNo);
        }
        
        uint8_t *selectedDigit, digitMaxVal = 9;
        switch(selectedDigitNo){
            case 1: selectedDigit = &digit1; digitMaxVal = 2; break;
            case 2: selectedDigit = &digit2; if(digit1 == 2)digitMaxVal = 4; break;
            case 3: selectedDigit = &digit3; break;
            case 4: selectedDigit = &digit4; break;
        }
        showDigit(0);
        __delay_ms(500);
        
        while(mode == 2){
            if(modePin){
                __delay_ms(10);
                if(modePin){
                    while(modePin);
                    mode = 0;
                }
            }
            if(nextDigitPin){
                __delay_ms(10);
                if(nextDigitPin){
                    if(*selectedDigit == digitMaxVal){
                        *selectedDigit = 0;
                    }
                    else{
                        (*selectedDigit)++;
                    }
                    while(nextDigitPin);
                }
            }
            if(prevDigitPin){
                __delay_ms(10);
                if(prevDigitPin){
                    if(*selectedDigit == 0){
                        *selectedDigit = digitMaxVal;
                    }
                    else{
                        (*selectedDigit)--;
                    }
                    while(prevDigitPin);
                }
            }
            
            displayPort = *selectedDigit;
            showDigit(selectedDigitNo);
        }
    }
}

void __interrupt() ISR(void){
    if(PIR1bits.CCP1IF){
        PIR1bits.CCP1IF = 0;
        interruptCount++;
    }
}