/*	Author: swill048
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


    /* Insert DDR and PORT initializations */


    /* Insert your solution below */
enum LED_STATES{ LED_B0_Wait, LED_B1, LED_B1_Wait, LED_B0 }LEDs ; 
void TickToggle( ) { // state transitions

unsigned char tmpA = PINA ; 
	switch( LEDs ){

	case LED_B0_Wait: // wait for button press
		if(tmpA == 0x01){
		LEDs = LED_B1 ; 
		}
		else{
		LEDs = LED_B0_Wait ;  
		}
		break;
	case LED_B1: // wait for button release
		if(tmpA == 0x00){
		LEDs =  LED_B1_Wait ; 
		}	
		else{
		LEDs = LED_B1 ; 
		}
		break; 
	case LED_B1_Wait: // wait for button press
		if(tmpA == 0x01){
		LEDs = LED_B0; 
		}
		else{
		LEDs = LED_B1_Wait ; 
		}
		break;
	case LED_B0: // wait for button release
		if(tmpA == 0x00){
		LEDs = LED_B0_Wait ; 
		}
		else{
		LEDs = LED_B0 ; 
		}
		break; 
	default:
		break; 
	}
	switch(LEDs){
	case LED_B0_Wait:
	PORTB = 0x01 ;
	break; 
	case LED_B1:
	PORTB = 0x02 ; 
	break; 
	case LED_B1_Wait:
	PORTB = 0x02 ; 
	break; 	
	case LED_B0:
	PORTB = 0x01 ; 
	break;
	}


}
int main(void){
DDRA = 0x00 ; PORTA = 0xFF ; 
DDRB = 0xFF ; PORTB = 0x00 ; 
//unsigned char tmpA = 0x00 ; 
 LEDs = LED_B0_Wait ; 
   while (1) {
//	tmpA = PINA ;  
	 TickToggle() ; 


    }
    return 1;
}
