#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "pi.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "motor.h"
#include "uart.h"



double K_p = 1;
double K_i = 1;
int ref;
double integral = 0;
double error_prev = 0;
double T = 0.016;






void pi_regulator(void){
    int motor_position = motor_read_encoder();
    int ref_pos = ref;
    int error = ref - motor_position;
    
    double dt = (error_prev - error)/T;
    error_prev = error;
    integral = integral + dt;
    int u = K_p * error + K_i * integral;
    motor_set_speed(u);
}

void pi_update_ref(int reference){
    ref = reference;
}

void pi_init(){
    cli();
    TIMSK3 |= (1<<TOIE1);

    TCCR3B = (1<<CS30) | (1<<CS31) | (1<<CS32);
    sei();
    
}

ISR(TIMER3_COMPA_vect){
    pi_regulator();
    
}

