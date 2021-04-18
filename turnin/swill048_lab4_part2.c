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
enum LED_STATES{ LED_INIT, LED_WAIT, LED_INC, LED_DEC, LED_ZERO }LEDs ; 
unsigned char sum = 0x07 ; 

void TickToggle( ) { // state transitions

unsigned char tmpA = PINA ; 
//unsigned char sum = 0x00 ; // FIXME 
	switch( LEDs ){

	case LED_INIT: //init state
		LEDs = LED_WAIT ; //fixme  
		break; 
	case LED_WAIT:
		if((PINA == 0x01) && (sum < 9)){ // inc
			sum = sum +1 ; 
			LEDs = LED_INC ; 
		}
		else if((PINA == 0x02) && (sum > 0) ){ // dec
			sum = sum - 1  ; 
			LEDs = LED_DEC ; 
		}
		else if(PINA == 0x03){ // reset
			sum = 0 ; 
			LEDs = LED_ZERO ; 
		}
		else{
		LEDs = LED_WAIT ; 
		}
		break; 
	case LED_INC:
		if(PINA == 0x03){
			LEDs = LED_ZERO ; 	
			sum = 0x00 ; 
		}		
		else if(PINA == 0x01){
			LEDs = LED_INC ;  
		}
		else{
			LEDs = LED_WAIT ; 
		}
		break; 
	case LED_DEC:
		if(PINA == 0x03){
			LEDs = LED_ZERO ; 
			sum = 0x00 ; 
		}
		else if(PINA == 0x02){
			LEDs = LED_DEC ; 
		}
		else{
			LEDs = LED_WAIT ; 
		}
		break; 
	case LED_ZERO:
		if(PINA == 0x03){
			LEDs = LED_ZERO ; 
		}
		else{
			LEDs = LED_WAIT ; 
		}
		break; 
	default:
		break; 
	}
	switch(LEDs){
	case LED_INIT:
		PORTC = 0x07 ; 
		break;
	case LED_WAIT:
		//do nothing
//		PORTC = sum ; 
		break; 
	case LED_INC: // up one
		PORTC = sum ; 
		break;
	case LED_DEC: // down one
		PORTC = sum ; 
		break; 
	case LED_ZERO: //set to zero
		PORTC = 0x00 ; 
		break;
	default:
		break;
	}


}
int main(void){
DDRA = 0x00 ; PORTA = 0xFF ; 
DDRC = 0xFF ; PORTC = 0x00 ;  
//unsigned char tmpA = 0x00 ; 
 LEDs = LED_WAIT ;  //fixme 
   while (1) {
//	tmpA = PINA ;  
	 TickToggle() ; 


    }
    return 1;
}
