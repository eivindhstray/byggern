#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "pi.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "motor.h"
#include <util/delay.h>




double K_p = 2;
double K_i = 2;
int ref = 0;
double integral = 0;
double error_prev = 0;
double T = 0.01;
int scaling_factor;
static double motor_min;
static double motor_max;
volatile double d_pos;
volatile double pos_before;
int u;
int ref_pos = 230;



void pi_pos_regulator(void){
    double pos = motor_read_encoder();
    int motor_position = 255*(pos-(motor_min))/((motor_max)-(motor_min));
    
    int error =  motor_position - ref_pos;


    if(integral < 255 & integral > 0){
        integral = integral + error*T;
    }

    u = K_p*(error) + K_i * integral + 128;
    
    motor_set_speed(u);
}




void pi_update_ref(int reference){
    ref = reference;
}

void pi_update_pos_ref(int reference){
    ref_pos = 255 -reference;
}

void pi_init(){
    _delay_ms(1000);
    motor_set_speed(0);
    _delay_ms(1000);
    motor_max = motor_read_encoder();
    motor_set_speed(255);
    _delay_ms(1000);
    motor_min = motor_read_encoder();
    motor_set_speed(128);

}



void pi_timer_init(void){
    // make 0.1 sek counter
	TCCR2A = 0x00;
	//prescaler 111 = 1024, prescaler 100 = 256
	TCCR2B |= (1<<CS20)|(1<<CS22)|(1<<CS21);
	//enable overflow vector
	TIMSK2|=(1 << TOIE2);
	//clear overflow flag
	TIFR2 |= (1<<TOV2);	

	TCNT2 = 0x00;
}














/* Implementing difficulty using K_d and K_p is more tricky that i thought. Higher values of K_p sets
motor speed directly left. Maybe that could be a nice difficulty setting? */
/*
void pi_set_regulator values(int difficulty){
    if (difficulty == 1){       //Normal diff
        K_p = 1;
        K_d = 1;
    }
    if (difficulty == 2){       //Hard diff
        K_p = 10;
        K_d = 10;
    }
    else {
        K_p = 1;
        K_d = 1;
    }

}
*/
/*
void pi_regulator(void){
    double pos = motor_read_encoder();
    int motor_position = 255*(pos-(motor_min))/((motor_max) -(motor_min));
    
    double speed = d_pos/T;
    int error = (ref - speed);
    pos_before = pos;
    
    error_prev = error;
    if(integral < 255 & integral>0){
        integral = integral + error*T;
    }
    u = K_p*(error) + K_i * integral;
   
    motor_set_speed(u);
    

    
}*/