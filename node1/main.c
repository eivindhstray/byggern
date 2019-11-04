

#ifndef F_CPU
#define F_CPU 4915200UL
#endif

#include "io.h"
#include "adc.h"
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "oled.h"
#include "mcp.h"
#include "spi.h"
#include "can.h"
#include "joystick.h"


#include <stdio.h>
//#define FOSC 4915200UL// Clock Speed
#define BAUD 9600
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR 31
#include "menu.h"


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
	SFIOR = (1 <<  XMM2);		
	
	

	oled_init();
	message_t position;
	position.id = 0b01;

	menu_ptr menu = menu_build();
	//menu_init(menu);

	position.length = 4;
	
	mcp_init();
	can_init();
	while(1){
		
			
		
		joystick_update_details(&position);
		
		_delay_ms(20);
		

		can_send_message(&position);
		_delay_ms(200);
	
		
		
		

		
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
