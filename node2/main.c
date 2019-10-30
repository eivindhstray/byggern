

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>
#include "uart.h"
#include "mcp.h"
#include "spi.h"
#include "can.h"
#include "pwm.h"
#include "goal_sensor.h"

#include <stdio.h>
//#define FOSC 4915200UL// Clock Speed
#define BAUD 9600
#define FOSC 16000000UL
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR 103



void main(void){
	
	/*DDRA = 0xFF;
	DDRB = 0xFF;
	DDRE = 0xFF;
	*/
	USART_Init(MYUBRR);
	
	DDRD = 0x00;
	MCUCR = (1 << SRE); 		//når denne brukes kan man ikke sette registre selv
		
	message_t test;
	cli();
	mcp_init();
	can_init();
	pwm_init();
	goal_sensor_init();

	pwm_update_duty_cycle(1.7);
	//printf("CANSTAT after reset: %d\n\r", mcp_read(0x0E));
	sei();
	while(1){
		
		
		
		can_receive_message(&test);
		_delay_ms(200);
		printf("goal%d\r\n",goal_sensor_read());
		printf("message_data %d\r\n", test.data[0]);
		printf("message_data %d\r\n", test.data[1]);
		printf("message_data %d\r\n", test.data[2]);
		printf("message_data %d\r\n", test.data[3]);
		printf("message_length %d\r\n", test.length);
		printf("id %d\n\r", test.id);
		
		uint8_t joy = test.data[0];

		pwm_update_duty_cycle(joy);
			

		
	}
	

	//ttyACM0
	//dmesg | grep -i tty
	
}







//sudo picocom -b 9600 -r -l /dev/ttyS0
