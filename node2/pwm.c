#include "pwm.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

static unsigned int pulse_period = 40000;

void pwm_init(void){
    pwm_set_output();
    pwm_set_timer();
}

void pwm_set_output(void){
    DDRB |= (1<<PB5);
    


    //Set N to 8

    TCCR1B |= (1<<CS11);


    TCCR1A |= (1<<COM1A1) | (1<<COM1A0);


}

void pwm_set_timer(void){
    TCCR1A |= (0<<WGM10)|(1<<WGM11);
    TCCR1B |= (1<<WGM13)|(1<<WGM12);
    ICR1 = pulse_period;
}


double pwm_duty_cycle_ms(int joystick){
    
    double max = 255;
    double output =  ((joystick/max))*1.2 + 0.9;
    return output;
}

void pwm_clear_interrupt(void){
    while (TIFR0 &= (1<<OCF0A)){
        TIFR0 &= ~(1<<OCF0A);
    }
}


void pwm_update_duty_cycle(int joystick){
    double duty_cycle = pwm_duty_cycle_ms(joystick);
    if(duty_cycle<0.9){
        duty_cycle = 0.9; //make sure D is not too low!
    }
    if (duty_cycle>2.1){
        duty_cycle = 2.1; //make sure D is not too high!
    }

    
    OCR1A = (pulse_period/20)*(20-duty_cycle); 

}

