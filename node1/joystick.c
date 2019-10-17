#include "adc.h"
#include <stdio.h>
#include "can.h"



int get_x_pos(){
    return x_pos();
}

int get_y_pos(){
    return y_pos();
}

int get_left_slider(){
    return l_slider();
}

int get_right_slider(){
    return r_slider();
}


//update array of joystick inputs within the position-message
void joystick_update_details(message_t *message){
    message->data[0] = x_pos();
    message->data[1] = y_pos();
    message->data[2] = l_slider();
    message->data[3] = r_slider();
}

// x = 255: right 
//y = 255: top