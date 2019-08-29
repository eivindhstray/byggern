
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#define F_CPU 4195200UL
#include <stdio.h>
#define FOSC 4195200// Clock Speed
#define BAUD 9600
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR 31


void main(void){

	DDRB = 1;
	USART_Init(MYUBRR);
	

	while(1){
		//unsigned char a = USART_Receive();
		USART_Transmit("a");
		USART_Transmit("b");
		USART_Transmit("z");
		printf("a");

		/*if(USART_Receive() == 'a'){
			PORTB = (1<<PB0);
			_delay_ms(1500);
			PORTB = (0<<PB0);
			_delay_ms(1500);
			printf("a");
			USART_Transmit("a");
			
		}*/
	}


	/*while(1){              day 1 test function
		PORTB = (1<<PB0);
		_delay_ms(1500);
		PORTB = (0<<PB0);
		_delay_ms(1500);
	
	}*/	
}


//sudo picocom -b 9600 -r -l /dev/ttyS0
