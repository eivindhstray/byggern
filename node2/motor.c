#include "motor.h"
#include "twi.h"
#include <avr/io.h>
#include <util/delay.h>
#include "pi.h"


void motor_init(void){
    DDRD |= (1<<PD0)|(1<<PD1);
    TWI_Master_Initialise();
    
    DDRH = 0xFF; //set direction and enable. 
    motor_reset_toggle();

    DDRK = 0x00;

    
}

void motor_enable(void){
    PORTH |= (1<<PH4);
}

void motor_disable(void){
    PORTH &= ~(1<<PH4);
}

void motor_set_speed(int joystick){
    int speed;
    //set PH1 to change direction, speed 0-255
    if(joystick<128){
        speed = 255-2*joystick;
        PORTH |= (1<<PH1);
    }
    else{
        speed = (joystick-128)*2;
        PORTH &=~(1<<PH1);
    }

    if (speed > 255){
        speed = 255;
    }
    if (speed < 0){
        speed = 0;
    }
    


    char speed_to_motor = speed*0.25;

    unsigned char msg[] = {80,0,speed_to_motor};

    int msg_size = 3;

    
    TWI_Start_Transceiver_With_Data(msg, msg_size);
    
}




void motor_reset_toggle(void){
    PORTH &=~(1<<PH6); //Toggle RST
    
    PORTH |= (1<<PH6);
    
}


int motor_read_encoder(void){
    PORTH &= ~(1<<PH5); //set !OE low
    PORTH &= ~(1<<PH3); //set SEL low
    _delay_us(120);
    uint8_t high = PINK;
    PORTH |= (1<<PH3); //set sel high
    _delay_us(120);
    uint8_t low = PINK; 

    PORTH|= (1<<PH5); //set !OE high

    return (high<<8)|low;
    
}


