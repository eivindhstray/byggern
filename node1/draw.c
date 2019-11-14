#include "oled.h"
#include "io.h"
#include "draw.h"
#include <avr/io.h>
#include "adc.h"
#include <util/delay.h>


void draw_init(void){
    draw_clear_screen();
}


void draw_clear_screen(void){
    for(int i = 0; i<128*8; i++){
        sram_write(i, 0);
    }
}

void draw_set_bit(int x, int y){
    int line = y/8;
    int bit = y%8;

    int address = x*8 + line;
    char byte = sram_read(address);

    byte |= (1<<bit);

    sram_write(address,byte);

}


void draw_print_sram(void){
    for(int cols = 0; cols<128; cols++){
        for(int line = 0; line<8; line++){
            int address = cols*8 +line;
            char byte = sram_read(address);
            oled_select_position(line,cols);
            oled_write_data(byte);
        }
    }
}


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
        if(y_pos <0){
            y_pos = 0;
        }
        unsigned char full_square[8] = {0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111};
        oled_select_position(y_pos, x_pos);

        if (r_button() /*&& (oled_select() != 0 || oled_scroll() != 0)*/) {
	        for (int i = 0; i < 8; i++) {
                oled_write_data(full_square[i]);
	        }
        }
        else {
            oled_select_position(x_pos, y_pos);
            oled_write_char("*");
        }
        /*
        else {
            if(oled_select() != 0 || oled_scroll() != 0 ){
                // skrive over gammel *?
                oled_select_position(y_pos,x_pos);
                if(!marked){
                    oled_write_char("*");
                }
                marked = 1;
                
            }

            //oled_write_char("*");
            oled_select_position(x_pos, y_pos);
        }
        if(oled_select() != 0 || oled_scroll()!= 0){
            marked = 0;
        }
        */
        _delay_ms(100);
    }
}




