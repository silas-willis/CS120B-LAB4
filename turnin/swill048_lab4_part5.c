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


enum LOCK { INIT, LOCK, UNLOCK, LOCK_INSIDE}LOCK_STATE ; 
unsigned char POUND = 3 ; 
unsigned char Y = 2 ;
unsigned char X = 1 ;
unsigned char lock = 0x00 ; 
unsigned char pass[4] = {0,0,0,0} ; 
unsigned char counter = 0 ;   
void TickToggle( ) { // state transitions

unsigned char tmpA = PINA ; 

switch(LOCK_STATE){
case INIT: 
	if(tmpA == 0x80){
	LOCK_STATE = LOCK_INSIDE ; 
	}
	else if(counter == 4){
		if( (pass[0] == 3) && (pass[1] == 1) && (pass[2] == 2) && (pass[3] == 1)){ // check correct vals
			if(lock == 0x00){
			LOCK_STATE = UNLOCK ; 
			}		
			else{
			LOCK_STATE = LOCK ; 
			}
		}
		else{
		counter = 0 ; 
		LOCK_STATE = INIT ; 
		}
	
	}
	else if(tmpA == 0x01){ // check for x
		pass[counter] = X ; 	
		++counter ; 
		LOCK_STATE = INIT ; 
	}
	else if(tmpA == 0x02){ // check for y
		pass[counter] = Y ; 
		++counter ; 
		LOCK_STATE = INIT ; 
	} 
	else if(tmpA == 0x04){   // check for #
		pass[counter] = POUND ; 
		++counter ; 
		LOCK_STATE = INIT ; 
	}	
 	else{
		LOCK_STATE = INIT ; 
	}
break ; 
case LOCK:
	lock = 0x00 ; 
	counter = 0 ; 
	PORTB = lock ; 
	LOCK_STATE = INIT ; 
break ; 
case UNLOCK:
	lock = 0x01 ; 
	counter = 0 ; 
	PORTB = lock ; 
	LOCK_STATE = INIT ; 
break ;  
case LOCK_INSIDE:
	if(tmpA == 0x80){
		LOCK_STATE = LOCK_INSIDE ; 
	}	
	else{		
		lock = 0x01; // FIXME ? 
		PORTB = lock ;
		counter = 0 ;  
		LOCK_STATE = INIT ; 
	}
break; 
default:
break ; 
}
	switch(LOCK_STATE){
	case INIT:
	break ;  
	case LOCK:
	break; 
	case UNLOCK:
	break; 
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

