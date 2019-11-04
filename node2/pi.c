#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "pi.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "motor.h"




double K_p = 1;
double K_i = 1;
int ref = 0;
double integral = 10;
double error_prev = 0;
double T = 0.016;
int scaling_factor;
int motor_min;
int motor_max;






void pi_regulator(void){
    
    int motor_position = (motor_read_encoder()-4400)/(4400/100);
    int ref_pos = ref;
    int error = ref - motor_position;
    
    double dt = (error_prev - error)/T;
    error_prev = error;
    integral = integral + integral*dt;
    int u = K_p * error + K_i * integral;
    
    if(u>0 & u<255){
        motor_set_speed(u);
    }
}

void pi_update_ref(int reference){
    ref = reference;
}

void pi_init(){
    cli();
    
    TIMSK2 = (1<<TOIE2);
    
    TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
    sei();
    
    
}
int count = 1;
ISR(TIMER2_OVF_vect){
    cli();

   
    sei();
}

