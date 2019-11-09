#include "solenoid.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include <avr/interrupt.h>


int allowed = 0;

void solenoid_init(void){
    DDRB |= (1<<PB6);
    PORTB |=(1<<PB6);
}


void solenoid_disengage(void){
     DDRB&=~(1<<PB6);
}




void solenoid_shoot(void){

    //set pulse length
    int pulse_length = 150;
    PORTB&= ~(1<<PB6);
    _delay_ms(pulse_length);
    PORTB|=(1<<PB6); 
    
    
    
	
    
    /*  
    TCCR2B |= (1<<CS22)|(1<<CS20);
    TIMSK2 |= (1<<OCIE2A);
    TIFR2 |= (1<<TOV2);
    TCCR2A = 0x00;
    OCR2A = 1562;
    */
    
    
}



ISR(TIMER2_OVF_vect){
   
}