
//#include "io.h"
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
	//PORTA = (0<<PORTA0)|(0<<PORTA1);
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRE = 0xFF;
	USART_Init(MYUBRR);

	MCUCR = (1 << SRE); 
	SFIOR = (1 <<  XMM2);		//når denne brukes kan man ikke sette registre selv
	while(1){
		volatile char *ext_ram = (char*) 0x1400;
		ext_ram[0] = 0x1400;
	}
	
}


//sudo picocom -b 9600 -r -l /dev/ttyS0


	
	/*while(1){
		USART_Transmit('a'); //day 2
		unsigned char test = USART_Receive();
		if(UDR0 != 0){
			printf("hei");			
		}

		
		
		PORTE = (0<<PORTE1);
		PORTA = 0xFF;
		_delay_ms(100);
		PORTE = (1<<PORTE1);
		_delay_ms(1500);
		PORTE &= ~(1<<PORTE1);
		PORTA &= ~(1<<PORTA0);
		_delay_ms(1000);
		PORTA = (1<<PORTA0);

		_delay_ms(5000);

		PORTE = (0<<PORTE1);
		PORTA = 0x00;
		_delay_ms(100);
		PORTE = (1<<PORTE1);
		_delay_ms(1500);
		PORTE &= ~(1<<PORTE1);
		PORTA &= ~(1<<PORTA0);
		_delay_ms(1000);
		PORTA = (1<<PORTA0);
		
		
		if(USART_Receive() == 'a'){ //day 2
			PORTB = (1<<PB0);
			_delay_ms(1500);
			PORTB = (0<<PB0);
			_delay_ms(1500);
			printf("a");
			USART_Transmit("a");
			
		}
		
	}*/
