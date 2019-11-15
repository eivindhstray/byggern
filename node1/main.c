

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
#include "draw.h"
#include "music_signal.h"
#include "states.h"


#include <stdio.h>
//#define FOSC 4915200UL// Clock Speed
#define BAUD 9600
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR 31
#include "menu.h"

message_t node2;
volatile int points = 0;
volatile int quit = 0;
volatile int game_over = 0;
volatile int point_change = 0;



enum states state;

void main(void){

	
    cli();
	
	DDRA = 0xFF; //define PORTA as output
	DDRB = 0xFF; //define PORTB as output
	r_button_init();
	DDRE = 0xFF;
	USART_Init(MYUBRR);
	DDRD = 0x00;
	PORTD = 0xFF;
	MCUCR = (1 << SRE); 		//Enable external memory. SRAM init.
	SFIOR = (1 <<  XMM2);	
	mcp_init();
	can_init();
	music_init();
	music_timer_init();
	message_t position;
	position.id = 0b01;
	oled_init();
	oled_reset();
	
	music_welcome();
	
	write_open_message();
	_delay_ms(5000);
	oled_reset();
	menu_ptr menu = menu_build();
	
	

	position.length = 5;
	
	uint8_t position_before[8];

	sei();

	state = MENU;
	
	
	//Play function defined s.t. CAN bus only on when play_game. 
	while(1){
		switch(state){

		case(PLAYING):
			printf("playing");
			joystick_update_details(&position);
				
			can_should_send(position, &position_before); //only send if there is actually a change of information to
				//be sent to node2
			
			if(game_over){
				
				write_lost_menu();
				_delay_ms(2000);
				state = MENU;
			}

			if(points > 9){
				
				write_win_menu();
				_delay_ms(2000);
				state = MENU;
			}

			if(point_change){
				get_score(points);
				play_game();
				point_change = 0;
			}
			if(l_button()){
				state = PAUSE_MENU;
				point_change = 0;
			}
			break;



		case(MENU):
			points = 0;
			game_over = 0;
			get_score(points);
			menu_run(menu);
			oled_reset();
			play_game();
			
			state = PLAYING;

			break;

		
		case(PAUSE_MENU):

			menu_pause();

			if(r_button()){
				play_game();
				state = PLAYING;
				point_change = 0;
			}
			if(oled_select() == -1){
				state = MENU;
				point_change = 0;
			}

			break;

		}
	
	
	}

}

ISR(INT0_vect){
	
	can_receive_message(&node2);
	points += node2.data[0];
	game_over = node2.data[1];
	if(state != PAUSE_MENU){
		point_change = 1;
	}
	
	
}







	
