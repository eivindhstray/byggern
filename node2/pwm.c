#include "pwm.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

static int pulse_period = 20/(1000);

void pwm_init(void){
    pwm_set_output();
    pwm_set_timer();
    printf("yolo%d", 1);
}

void pwm_set_output(void){
    DDRB |= (1<<PB5);
    


    //Set N to 8
    //TCCR1B &= ~(1<<CS10);
    TCCR1B |= (1<<CS12);
    //TCCR1B &= ~(1<<CS12);

    TCCR1A |= (1<<COM1A1) | (1<<COM1A0);

/*
    TCCR0B = (0<<CS00)|(0<<CS01)|(1<<CS02); //set N to 256 page 130
    TCCR1A = (1<<COM1A1)|(0<<COM1A0);         //set non-inverted mode for Fast PWM Control Reg A in the datasheet
*/
}

void pwm_set_timer(void){
    TCCR1A |= (0<<WGM10)|(1<<WGM11);
    TCCR1B |= (1<<WGM13)|(1<<WGM12);
    //ICR1H = 0b00000100;  //1250
    //ICR1L = 0b11100010;
    ICR1 = 1250;
}


int pwm_duty_cycle_ms(int joystick){
    int max = 255/2;
    int output =  (abs(joystick-max)/max)*1.2 + 0.9;
    if( (output >= 0.9) && (output <= 2.1)){
        return output;
    }
    return 0.9;
}

void pwm_clear_interrupt(void){
    while (TIFR0 &= (1<<OCF0A)){
        TIFR0 &= ~(1<<OCF0A);
    }
}


void pwm_update_duty_cycle(int duty_cycle){
   OCR1A = 2*1100; //0x14*duty_cycle*10;

}

