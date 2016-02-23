/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>
#include "leds.h"

#define TRIS_RUN TRISGbits.TRISG12
#define TRIS_STOP TRISGbits.TRISG14
//#define ODC_RUN ODCGbits.ODCG12
//#define ODC_STOP ODCGbits.ODCG14
#define RUN1_LED LATGbits.LATG12 // TRD1
#define RUN2_LED LATGbits.LATG14 // TRD2

#define INPUT 1
#define OUTPUT 0

#define ON 1
#define OFF 0


#define Running1 1
#define Running2 2

void initLEDs(){
    //TODO: Initialize the appropriate pins to work with the LEDs
    TRIS_RUN = OUTPUT;
    TRIS_STOP = OUTPUT;
    RUN1_LED = ON;
    RUN2_LED = OFF;    
}

void turnOnLED(int led)
{
    if(led == Running1)
    {
        RUN1_LED = ON;
        RUN2_LED = OFF;
        
    }
    else if (led == Running2)
    {
        RUN1_LED = OFF;
        RUN2_LED = ON;
    }
}