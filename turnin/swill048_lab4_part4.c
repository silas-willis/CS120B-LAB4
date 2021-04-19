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


enum LOCK { INIT,POUND, LOCK, UNLOCK, X, LOCK_INSIDE}LOCK_STATE ; 
unsigned char POUND_OK = 0 ; 
unsigned char Y_OK = 0 ; 
unsigned char lock = 0x00 ; 



void TickToggle( ) { // state transitions

unsigned char tmpA = PINA ; 

switch(LOCK_STATE){
case INIT: 
	if(tmpA == 0x04){
		if(lock == 0x00){
			LOCK_STATE = POUND ; 			
		}
		else if(lock == 0x01){
			LOCK_STATE = POUND ; 
		}
		else{
		LOCK_STATE = INIT ; 
		}
	}
	else if(tmpA == 0x80){
	LOCK_STATE = LOCK_INSIDE ; 
	}

break ; 
case POUND:
if((POUND_OK == 1) && (tmpA == 0x02)){
	if(lock == 0x00){
		LOCK_STATE = UNLOCK ; 
	}
	else if(lock == 0x01){
		LOCK_STATE = LOCK ; 
	}
	else{
	LOCK_STATE = INIT ; 
	}
}
else if(POUND_OK == 0){  // wait for un pressing 
	if(tmpA == 0x00){
	POUND_OK = 1 ; 
	LOCK_STATE = POUND ; 
	}
	else if(tmpA == 0x04){
	LOCK_STATE = POUND ; 
	}
	else{ // if anything other than PA2 is pressed 
	LOCK_STATE = INIT ; 
	}
}
break; 
case LOCK:
	lock = 0x00 ; 
	PORTB = lock ; 
	LOCK_STATE = INIT ; 

break ; 
case UNLOCK:
	lock = 0x01 ; 
	PORTB = lock ; 
	LOCK_STATE = INIT ; 
break; 

case X:
// do nothing 
break ; 
case LOCK_INSIDE:
	if(tmpA == 0x80){
		LOCK_STATE = LOCK_INSIDE ; 
	}	
	else{		
		lock = 0x08 ; 
		PORTB = lock ; 
		LOCK_STATE = INIT ; 
	}
break; 
default:
break ; 





	}
	switch(LOCK_STATE){
	case INIT:

	break ; 
	case POUND:

	break ; 
	case LOCK:

	break; 
	case UNLOCK:

	break; 
	case X:

	break ; 
	case LOCK_INSIDE:
	
	break; 
	default:
	break ; 



	}
}
int main(void){
DDRA = 0x00 ; PORTA = 0xFF ;
DDRB = 0xFF ; PORTB = 0x00 ; 

LOCK_STATE = INIT ; 
while(1){
	TickToggle() ; 

}
return 1 ; 
}

