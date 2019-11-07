

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
#include "solenoid.h"


#include <stdio.h>
//#define FOSC 4915200UL// Clock Speed
#define BAUD 9600
#define FOSC 16000000UL
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR 103
message_t message;

void main(void){
	cli();
	USART_Init(MYUBRR);
	mcp_init();
	can_init();
	pwm_init();
	goal_sensor_init();
	motor_init();
	motor_enable();
	solenoid_init();
	
	solenoid_shoot();
	
	sei();
	pi_init();
	
	
	while(1){
		pi_regulator();	
		_delay_ms(10);
		if(message.data[4]){
			solenoid_shoot();
			_delay_ms(200);
		}
	}
}


ISR(INT2_vect){
	cli();
	printf("hei");
	can_receive_message(&message);
	uint8_t wagon = message.data[0];
	uint8_t servo = message.data[1];
	pi_update_ref(wagon);
	pwm_update_duty_cycle(servo);
	
	sei();
}

ISR(BADISR_vect){
	printf("badisr");
}



