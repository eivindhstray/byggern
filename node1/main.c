

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
#include <avr/interrupt.h>


#include <stdio.h>
//#define FOSC 4915200UL// Clock Speed
#define BAUD 9600
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR 31
#include "menu.h"
void main_init(){
	//PORTA = (0<<PORTA0)|(0<<PORTA1);
	DDRA = 0xFF; //define PORTA as output
	DDRB = 0xFF; //define PORTB as output
	r_button_init();
	DDRE = 0xFF;
	USART_Init(MYUBRR);
	DDRD = 0x00;
	PORTD = 0xFF;
	MCUCR = (1 << SRE); 		//Enable external memory. SRAM init.
	SFIOR = (1 <<  XMM2);	
	oled_init();
	mcp_init();
	can_init();
}

void main(void){
	cli();
	main_init();
	message_t position;
	position.id = 0b01;
	oled_change_brightness(0xFF);
	write_open_message();
	_delay_ms(5000);
	oled_reset();
	menu_ptr menu = menu_build();
	menu_init(menu);
	

	position.length = 5;
	
	uint8_t position_before[8];
	
	
	//Play function defined s.t. CAN bus only on when play_game. 
	while(1){
		menu_pause();
		
		
		joystick_update_details(&position);
		
		can_should_send(position, &position_before); //only send if there is actually a change of information to
		//be sent to node2	
		
	}
	
}







	
