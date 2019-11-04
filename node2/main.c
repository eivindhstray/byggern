

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
#include "twi.h"
#include "motor.h"
#include "pi.h"


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
	motor_init();
	motor_enable();
	sei();
	//pi_init();
	

	double integral;
	while(1){
		
		
		can_receive_message(&test);
		
		uint8_t wagon = test.data[0];
		uint8_t servo = test.data[1];
		pi_update_ref(wagon);
		//motor_set_speed(wagon);
		motor_set_speed(wagon);
		pwm_update_duty_cycle(servo);
		printf("yolo%d\r\n",motor_read_encoder());
		
	}
	

	//ttyACM0
	//dmesg | grep -i tty
	
}


//sudo picocom -b 9600 -r -l /dev/ttyS0
