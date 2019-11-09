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
int u;

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
    u = K_p*(error) + K_i * integral;
   
    motor_set_speed(u);
    

    
}




void pi_update_ref(int reference){
    ref = reference;
}

void pi_init(){

}

