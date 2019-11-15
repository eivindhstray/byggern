#include "oled.h"
#include "io.h"
#include "draw.h"
#include <avr/io.h>
#include "adc.h"
#include <util/delay.h>





void draw_game(void){
    oled_reset();
    int x_pos = 0;
    int y_pos = 0;
    int marked = 0;
    
    while(!l_button()){
        
        x_pos += oled_select()*8;
        y_pos += oled_scroll();
        if(x_pos <0){
            x_pos = 0;
        }
        if(x_pos > 15*8){
            x_pos = 15*8;
        }
        if(y_pos <0){
            y_pos = 0;
        }
        if(y_pos > 7){
            y_pos = 7;
        }
        unsigned char full_square[8] = {0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111};
        oled_select_position(y_pos, x_pos);

        if (r_button() /*&& (oled_select() != 0 || oled_scroll() != 0)*/) {
	        for (int i = 0; i < 8; i++) {
                oled_write_data(full_square[i]);
	        }
        }
        else if (oled_select() == 0 && oled_scroll() == 0){
            
            print_string("*");
            
        }

        else{
            print_string(" ");
        }
        _delay_ms(100);
    }
}




