#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "pi.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "motor.h"
#include <util/delay.h>




double K_p = 1;
double K_i = 1;
int ref = 0;
double integral = 0;
double error_prev = 0;
double T = 0.01;
int scaling_factor;
static double motor_min;
static double motor_max;
volatile double d_pos;
volatile double pos_before;






void pi_regulator(void){
    double pos = motor_read_encoder();
    int motor_position = 255*(pos-(motor_min))/((motor_max) -(motor_min));
    int ref_pos = ref-128;  //to center it around 0
    
    double speed = d_pos/T;
    int error = (ref - speed);
    pos_before = pos;
    
    error_prev = error;
    if(integral < 255 & integral>0){
        integral = integral + error*T;
    }
    int u = K_p*(error) + K_i * integral;
    
    motor_set_speed(u);

    
}

void pi_update_ref(int reference){
    ref = reference;
}

void pi_init(){
    
    
    //TIMSK2 = (1<<TOIE2);
    
    //TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);

    motor_set_speed(255);
    _delay_ms(1000);
    motor_reset_toggle();
    motor_min = motor_read_encoder();
    motor_set_speed(0);
    _delay_ms(1000);
    motor_set_speed(128);
    motor_max = motor_read_encoder();
    _delay_ms(2000);
    
    
    
    
    
}

ISR(TIMER2_OVF_vect){
    cli();

   
    sei();
}
