
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#define F_CPU 4195200UL
#include <stdio.h>


int main(void){

	
	DDRB = 1;
		
	while(1){
		PORTB = (1<<PB0);
		_delay_ms(1500);
		PORTB = (0<<PB0);
		_delay_ms(1500);
		USART_Transmit("a");
		
	}	
}
