#include "oled.h"
#include "io.h"
#include "draw.h"
#include <avr/io.h>
#include "adc.h"


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
    draw_clear_screen();
    
    while(1){
        int x_pos = 0;
        int y_pos = 0;
        x_pos += oled_select();
        y_pos += oled_scroll();
        if(x_pos <0){
            x_pos = 0;
        }
        if(y_pos <0){
            y_pos = 0;
        }
        oled_select_position(x_pos,y_pos);
        print_string("*");
       
        if(r_button()){
            draw_set_bit(x_pos,y_pos);
            draw_print_sram();
        }

    }
}




