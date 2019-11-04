#include "solenoid.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"


void solenoid_init(void){
    DDRB |= (1<<PB6);
    PORTB |=(1<<PB6);
}


void solenoid_shoot(void){
    //set pulse length
    int pulse_length = 150;
    PORTB&= ~(1<<PB6);
    _delay_ms(pulse_length);
    PORTB|=(1<<PB6); 
    
    
}