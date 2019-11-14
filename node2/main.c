

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
#include "play.h"a


#include <stdio.h>
//#define FOSC 4915200UL// Clock Speed
#define BAUD 9600
#define FOSC 16000000UL
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR 103
message_t message;
volatile int solenoid_shot = 0;
int solenoid_timer_counter = 0;
int right_button = 0;

volatile int button_pressed = 0;

uint8_t pos;
void main(void){
	cli();
	USART_Init(MYUBRR);
	mcp_init();
	pwm_init();
	goal_sensor_init();	
	motor_enable();
	solenoid_init();
	sei();
	printf("lessgo!");
    motor_init();
	can_init();
	pi_init();
	pi_timer_init();
    while(1){
		//printf("%d\n\r",message.data[4]);
		if( button_pressed && solenoid_shot==0 ){
			solenoid_shot = 1;
			solenoid_shoot();
		}
		
		
       
    }
	
}

ISR(INT2_vect){
	
	
	can_receive_message(&message);
	uint8_t servo = message.data[0];
	uint8_t pos = message.data[3];
	
	pi_update_pos_ref(pos);
	pwm_update_duty_cycle(servo);
	button_pressed = message.data[4];
	
	
}

ISR(TIMER2_OVF_vect){
	
	pi_pos_regulator();
	cli();
	if(solenoid_timer_counter < 60 && solenoid_shot == 1){
		solenoid_timer_counter ++;
		
	}
	else if (solenoid_shot == 1){
		solenoid_shot = 0;
		solenoid_timer_counter = 0;
		
	}
	sei();
	TCNT2 = 0x00;
}


ISR(BADISR_vect){
	printf("badisr");
}



