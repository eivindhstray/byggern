

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "mcp.h"
#include "spi.h"
#include "can.h"


#include <stdio.h>
//#define FOSC 4915200UL// Clock Speed
#define BAUD 9600
#define FOSC 16000000UL
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR 103



void main(void){
	//PORTA = (0<<PORTA0)|(0<<PORTA1);
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRE = 0xFF;
	USART_Init(MYUBRR);
	//SRAM_initialize();
	DDRD = 0x00;
	PORTD = 0xFF;
	MCUCR = (1 << SRE); 		//når denne brukes kan man ikke sette registre selv
	//SFIOR = (1 <<  XMM2);		
	

	//DDRB |= (1 << PB0);

	//spi_master_init();
	//spi_slave_init();
	/*while(mcp_read(0x0E) != 128){
		mcp_reset();
		printf("Trying to reset mcp2515\n\r");
	}*/
	
	mcp_init();
	can_init();
	//printf("CANSTAT after reset: %d\n\r", mcp_read(0x0E));
	while(1){
		//printf("ready? %d", mcp_ready_to_send());
		//PORTB ^= (1 << PB0);
		
		message_t test;
		
		_delay_ms(200);
		can_receive_message(&test);
		printf("message_data %d\r\n", test.data[3]);
		printf("message_length %d\r\n", test.length);
		printf("id %d\n\r", test.id);
		

		
	}
	

	//ttyACM0
	











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