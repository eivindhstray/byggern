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

}

int goal_sensor_read(void){
    ADCSRA |= (1<<ADSC);
    while(!ADCSRA &(1<<ADIF)); //wait for conversion to be ready
    
    int adc_low = ADCL;
    int adc_high = ADCH;
    return adc_high<<8 | adc_low;

}


int goal_score(){
    int threshold = 400;
    if(goal_sensor_read() < threshold){
        printf("goal!!!");
        _delay_ms(200);
        return 1;
    }
    return 0;

}