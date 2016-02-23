// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"
#include "lcd.h"
#include "config.h"


#define W2 PORTDbits.RD6 //reset
#define W1 PORTAbits.RA7 //start or stop
#define press 0
#define release 1
#define running1 1
#define running2 2

typedef enum stateTypeEnum
{
    Reset, Running, Stop, savetime, readtime, wait, deBounce1, deBounce2
}stateType;

volatile stateType state;
volatile long int time = 0;
volatile const char*print;
volatile long int currT;
volatile int currTMR;
volatile int k;
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
void getTString(int time){
    int MM = 0, SS = 0, FF =0;
    char string[10];
    MM = ((time / 100) / 60) % 60 ;
    SS = (time / 100) % 60;
    FF = time % 100;
    sprintf(string, "%02d:%02d:%02d",MM,SS,FF);
    printStringLCD(string);
}//set time


int main(void)
{
    SYSTEMConfigPerformance(10000000); //10MHZ
    initTimer1();
    initTimer2();
    initLEDs();
    initLCD();
    initSW1();
    initSW2();
    enableInterrupts();
    currTMR = 0;
    currT = 0;
    state = Reset;

    while(1)
    {
        switch(state){
            case Reset:
                delayUs(10);
                turnOnLED(running1);
                time = 0;
                TMR1 = 0;
                currT = 0;
                currTMR = 0;
                clearLCD();
                moveCursorLCD(0,0);
                printStringLCD("Stopped:");
                moveCursorLCD(1,0);
                printStringLCD("00:00:00");
                state = wait;
               
                break;
            case Running:
                //for(k = 0; k < 300; k++)delayUs(100);
                clearLCD();
                moveCursorLCD(0,0);
                printStringLCD("Running:");
                //delayUs(1000);
                turnOnLED(running2);
                moveCursorLCD(1,0);
                getTString(time);
                break;
                
            case Stop:
                //for(k = 0; k < 300; k++)delayUs(100);
                clearLCD();
                turnOnLED(running1);
                moveCursorLCD(0,0);
                printStringLCD("stopped:");
                moveCursorLCD(1,0);
                getTString(currT);
                break;   
               
            case savetime:
                currT = time;
                currTMR = TMR1;
                state = Stop;
                break;
            case readtime:
                time = currT;
                TMR1 = currTMR;
                state = Running;
                break;
                
            case wait:
                delayUs(10);
              
                break;
            
            case deBounce1:
                delayUs(10);
                break;
                
            case deBounce2:
                delayUs(10);
                break;
        }
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
       IFS1bits.CNAIF = 0;
       IFS1bits.CNDIF = 0;
       int j = PORTAbits.RA7;
       int k = PORTDbits.RD6;
     
       if(state == Running && PORTAbits.RA7 == press)
       {
           state = deBounce1;
       }
       else if(state == Stop && PORTAbits.RA7 == press && PORTDbits.RD6 == release)
       {
           state = deBounce2;
       }
       else if(state == deBounce1 && PORTAbits.RA7 == release)
       {
           state = savetime;
       }
       else if(state == deBounce2 && PORTAbits.RA7 == release)
       {
           state = readtime;
           
         
       }
       
       else if(state == Stop && PORTDbits.RD6 == press)
       {
           state = Reset; 
       }
       else if(state == wait && PORTAbits.RA7 == press)
       {
           state = deBounce2;
          
       }
        
    

}

void __ISR(_TIMER_1_VECTOR, IPL7SRS)_T1Interrupt()
{
    IFS0bits.T1IF = 0;
    if(state == Running){
        time ++;
    }  
}
