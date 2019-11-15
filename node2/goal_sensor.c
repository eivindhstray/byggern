#include "goal_sensor.h"
#include <avr/io.h>
#include <util/delay.h>


void goal_sensor_init(void){
    DDRF &= ~(1<<PF2);
    //set voltage reference
    ADMUX |= (1<<REFS0);
    ADMUX &= ~(1<<REFS1);
    //select ADC2
    ADMUX |= (1<<MUX1);
    ADMUX &= ~(1<<MUX0);
    ADMUX &= ~(1<<MUX2);
    ADMUX &= ~(1<<MUX3);
    ADMUX &= ~(1<<MUX4);
    ADCSRB &= ~(1<<MUX5);
    ADCSRA |=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);


    // set up 0100 for CTC
    // timer 3
    // prescale 1024
    //COMA1,A0 = 0
    DDRE |= (1<<PE3);

    TCCR3A |= (1<<WGM32);

    TCCR3B|= (1<<CS32) ;

    TIMSK3 |= (1<<OCIE3A);

    OCR3A = 62500;
    
}

int goal_sensor_read(void){
    ADCSRA |= (1<<ADSC);
    while(!ADCSRA &(1<<ADIF)); //wait for conversion to be ready
    
    int adc_low = ADCL;
    int adc_high = ADCH;
    return adc_high<<8 | adc_low;

}


int goal_score(){
    int threshold = 100;
    if(goal_sensor_read() < threshold){
        return 1;
    }
    return 0;

}



