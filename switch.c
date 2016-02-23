/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */
#include <xc.h>

void initSW1(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRISAbits.TRISA7 = 1;// Enable input for switch
    CNCONAbits.ON = 1;      // Turn on CN device
    CNENAbits.CNIEA7 = 1;
    IEC1bits.CNAIE = 1;
    IFS1bits.CNAIF = 0;  //flag down
    IPC8bits.CNIP = 7;
    CNPUAbits.CNPUA7 = 1; // enable pull up resistor
    
}


void initSW2(){
    TRISDbits.TRISD6 = 1;// Enable input for switch
    CNCONDbits.ON = 1;       // Turn on CN device
    IPC8bits.CNIP = 7;
    CNENDbits.CNIED6 = 1;       // Enable CN interrupt for pin
    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    
    CNPUDbits.CNPUD6 = 1;// Enable Internal Pull-up resistor
    
}
