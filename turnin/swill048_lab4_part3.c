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
enum LOCK { INIT, POUND, Y, X, LOCK}LOCK_STATE ; 
unsigned char released = 0 ; 
unsigned char lock = 0x00 ; 
void TickToggle( ) { // state transitions

unsigned char tmpA = PINA ; 

  
//# = PA2 
//Y = PA1
//X = PA0 
	switch(LOCK_STATE){
	 
	case INIT: 
		released = 0 ; 
		if(tmpA == 0x04){//go to POUND
		LOCK_STATE = POUND ; 
		}	
		else if(tmpA == 0x80){ // lcck from inside
		LOCK_STATE = LOCK ; 
		}
		else{
		LOCK_STATE = INIT ; 
		}
		break; 
	case POUND:
		if((tmpA == 0x02 ) && (released == 1)){ 
		LOCK_STATE = Y ; 
		}
		else if((tmpA ==0x00) ){
		released = 1 ; 
		LOCK_STATE = POUND ; 
		}
		else if(tmpA == 0x04){
		LOCK_STATE = POUND ; 
		}
		else{
		LOCK_STATE = INIT ; 
		}
		break; 
	case Y: // door is unlocked, remain until A7 
//		lock = 0x01 ; 	
		LOCK_STATE = INIT ; 

		break;
	case X: // cant get to this state in current iteration 

		break; 
	case LOCK:
		if(tmpA == 0x80){ //remain in this state 
		LOCK_STATE = LOCK ; 
		}
		else{
		LOCK_STATE = INIT ; 
		}

		break; 
	default:
		break; 
	}
	switch(LOCK_STATE){
	
	case INIT:
		PORTB = lock ; 
		break;
	case POUND:
			
		break; 
	case Y:
		lock = 0x01; 
		PORTB = lock; 
		break; 
	case X:

		break; 
	case LOCK:
		lock = 0x00 ; 
		PORTB = lock ;  
		break;
	default:
		break;
	}


}
int main(void){
DDRA = 0x00 ; PORTA = 0xFF ; 
DDRB = 0xFF ; PORTB = 0x00 ;  
//unsigned char tmpA = 0x00 ; 
 LOCK_STATE = INIT ;  //fixme 
   while (1) { 
	 TickToggle() ; 
    }
    return 1;
}
