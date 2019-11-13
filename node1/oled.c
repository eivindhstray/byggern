#include "oled.h"
#include <stdint.h>
#include "fonts.h"
#include <string.h>
#include "adc.h"
#include <util/delay.h>
#include <stdlib.h>

volatile uint8_t *oled_command = (char*) 0x1000;
volatile uint8_t *oled_data = (char*) 0x1200;

void oled_write_c(char command){
    oled_command[0] = command;
}

void oled_write_data(int data){
    oled_data[0] = data;
}


void oled_write_char(char letter){
    int ascii = letter - 32;
    for (int i = 0; i<8; i++){
        oled_data[0] = pgm_read_byte(&font8[ascii][i]);
    }
}


void oled_init(void){
    oled_write_c(0xae);        //  display  off 
    oled_write_c(0xa1);        //segment  remap        
    oled_write_c(0xda);        //common  pads  hardware:  alternative        
    oled_write_c(0x12);        
    oled_write_c(0xc8);        //common  output scan direction:com63~com0       
    oled_write_c(0xa8);        //multiplex  ration  mode:63        
    oled_write_c(0x3f);        
    oled_write_c(0xd5);        //display  divide ratio/osc. freq. mode       
    oled_write_c(0x80);                               
    oled_write_c(0xd9);        //set  pre-charge  period        
    oled_write_c(0x21);                
    oled_write_c(0x20);        //Set  Memory  Addressing  Mode        
    oled_write_c(0x02);                
    oled_write_c(0xdb);        //VCOM  deselect  level  mode        
    oled_write_c(0x30);                
    oled_write_c(0xad);        //master  configuration          
    oled_write_c(0x00);                
    oled_write_c(0xa4);        //out  f0xb0 RAM  content        
    oled_write_c(0xa6);        //set  n0xb0display        
    oled_write_c(0xaf);        //  disp0xb0
    //oled_write_c(0xa5);        //make0xb0 white
    oled_write_c(0x20);
    oled_write_c(0b10);
   
}




void oled_change_brightness(int brightness){ //0x00-0xFF         
    oled_write_c(0x81);
    oled_write_c(brightness);
}


void oled_reset(void){
    oled_write_c(0xb0);        //set row 0xb0
    oled_write_c(0x21);        //select0xb0d the size of col
    oled_write_c(0); 
    oled_write_c(0x7f);         
    oled_write_c(0x22);        //select0xb0d the size of row
    oled_write_c(0x00);
    oled_write_c(0x07);
    int rows = 9;
    int cols = 128;
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<cols; j++){  
            oled_write_data(0x00);  //write 0 (off) everywhere
        }
        oled_write_c(0xb0 + i);     //newline
    } 
    oled_write_c(0xb0);             //to whereever we want to write. 1st row.
}

void oled_select_line(int row){ 
    oled_write_c(0x22);
    oled_write_c(0x00);
    oled_write_c(0x07);
    oled_write_c(0xb0 + row-1);  
    oled_write_c(0x21);        //select col and the size of col
    oled_write_c(0); 
    oled_write_c(0x7f);         //col 12;
}

void oled_select_col(int col){
    oled_write_c(0x00 + (col % 16));
    oled_write_c(0x00 + (col/16));
}

void oled_select_position(int row, int position){
    oled_select_line(row);
    oled_select_col(position);
}

void oled_remove_marker(void){
             
    oled_write_c(0x22);        //select0xb0d the size of row
    oled_write_c(0x00);
    oled_write_c(0x07);
    for (int j = 0; j<8; j++){
        oled_write_c(0x21);        //select0xb0d the size of col
        oled_write_c(0x70); 
        oled_write_c(0x7f);
        oled_write_c(0xb0 + j);
        for (int i = 0x70; i<0x7F; i++){
            oled_write_data(0x00);
        }
    }
}


void oled_select_indicator(int row){
    oled_remove_marker();
    oled_write_c(0x22);
    oled_write_c(0x00);
    oled_write_c(0x07);
    oled_write_c(0xb0 + row-1);
    oled_write_c(0x21);        //select col and the size of col
    oled_write_c(0x70); 
    oled_write_c(0x7f);         //col 127
    print_string("<-");
    oled_select_line(row);
    
}


int oled_scroll(void){
    
    if (y_pos() <= 50){
        _delay_ms(200);
        return 1; 
           
    }
    if (y_pos() >= 205){ //such that it does not seem that one can "select" the upper information line and the blank space.
        _delay_ms(200);
        return -1;
    }
    return 0;
}

int oled_select(void){
    if(x_pos() >= 205){
        _delay_ms(200);
        return 1;
    }
    if(x_pos() <= 50){
        _delay_ms(200);
        return -1;
    }
    return 0;
}

void print_string(char* content){
    int size = strlen(content);
    for (int i = 0; i< size; i++){
        oled_write_char(content[i]);
    }
}


void  oled_bright_high(void){     
    oled_change_brightness(0xFF);
    
}

void oled_bright_medium(void){         
    oled_change_brightness(0x0F);
}

void oled_bright_low(void){        
    oled_change_brightness(0x05);
}