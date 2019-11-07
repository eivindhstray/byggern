#include "adc.h"
#include <stdio.h>
#include "can.h"
#include "joystick.h"





//update array of joystick inputs within the position-message
void joystick_update_details(message_t *message){
    message->data[0] = x_pos();
    message->data[1] = y_pos();
    message->data[2] = l_slider();
    message->data[3] = r_slider();
    message->data[4] = r_button();
}

// x = 255: right 
//y = 255: top

