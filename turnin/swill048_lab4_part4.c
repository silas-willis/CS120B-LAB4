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
enum LOCK { INIT,POUND, LOCK, UNLOCK, X, LOCK_INSIDE}LOCK_STATE ; 
unsigned char POUND_OK = 0 ; 
unsigned char Y_OK = 0 ; 

unsigned char lock = 0x00 ; 



void TickToggle( ) { // state transitions

unsigned char tmpA = PINA ; 

  
//# = PA2 
//Y = PA1
//X = PA0 
	switch(LOCK_STATE){
	 
	case INIT: 
		released = 0 ; 
	if(lock == 0x00){  // locked, begin unlock sequence
		if(tmpA == 0x04){
			LOCK_STATE = POUND ; 
		}		
		else{
			LOCK_STATE = INIT ; 
		}
	}	
	else if(lock == 0x01){ // unlocked, begin lcoking sequence
		if(tmpA== 0x04){
			LOCK_STATE = POUND ; 
		}
		else{
			LOCK_STATE = INIT ; 
		}
	}	
	else if(tmpA == 0x80){ // lcck from inside
		LOCK_STATE = LOCK_INSIDE ; 
		}
	else{
		LOCK_STATE = INIT ; 
	}
	break; 
	case POUND:
	if((POUND_OK == 1) && (tmpA == 0x02)){
		if(lock ==0x00){ //continue unlcok
			LOCK_STATE = UNLOCK ; //correct passcode has been entered
		}		
		else if(lock ==0x01){ //continue lock 
			LOCK_STATE = LOCK ; 
		}
	}
	else if((POUND_OK == 0) && (tmpA == 0x00))



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
 	
		LOCK_STATE = INIT ; 

		break;
	case X: // cant get to this state in current iteration 

		break; 
	case LOCK_INSIDE:
		if(tmpA == 0x80){ //remain in this state 
		LOCK_STATE = LOCK_INSIDE ; 
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
	case LOCK_INSIDE:
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
