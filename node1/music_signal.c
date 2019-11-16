#include "music_signal.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 4915200UL
#endif



void music_init(void){
    //set OSC1A as output
    DDRD |= (1<<PD5);

    TCCR1A |= (1<<COM1A0);

    TCCR1A |= (1<<WGM10)|(1<<WGM11);
    TCCR1B |= (1<<WGM13)|(1<<WGM12);
    TCCR1B |= (1<<CS11);



}

void music_set_tone(int freq){
    uint16_t frequency = freq;
    
    //ICR3  = F_CPU*(frequency*8*2)-1;

    OCR1A = 4915200/(freq * 8);
    
}

void music_disable(void){
    TCCR1B&=~(1<<CS11);
}

void music_enable(void){
    TCCR1B|= (1<<CS11);
}

void music_welcome(void){
	music_set_tone(300);
	_delay_ms(3000);
	music_disable();
	_delay_ms(500);
	music_enable();
	music_set_tone(300);
	_delay_ms(3000);
	music_disable();
    _delay_ms(1000);
    music_enable();
	music_set_tone(1000);
	_delay_ms(3000);
	music_disable();
}




void music_timer_init(void){
    TCCR0 = (1<<WGM01)|(1<<CS02)|(1<<CS00);
    OCR0 = 80;

    TIMSK = (1<<OCIE0);
}

ISR(TIMER0_COMP_vect){
    OCR0 = 80;

}
