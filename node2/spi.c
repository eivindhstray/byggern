#include "spi.h"
#include "MCP2515.h"
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

/*
void set_CS(int value){
    switch(value){
        case 0:
            PORTB = (0<<PB4);
            break;
        case 1:
            PORTB = (1<<PB4);
            break;
    }

}*/

void spi_master_init(void){
    
    DDRB = (1<<PB2) | (1<<PB7) | (1<<PB1) | (1<<PB0); //set MOSI and SCK output, all others input
    DDRB &= ~(1<<PB3);
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0) /*| (1<<SPIE)*/; //enable spi, master, set clock rate fck/16
    spi_set_ss(1);
}

void spi_master_transmit(char cData){
    //spi_set_ss(0);
    SPDR = cData; //start transmission
    while(!(SPSR & (1<<SPIF)))//wait for transmission complete
    ;
    //spi_set_ss(1);
}



int spi_read(){
    
    SPDR = 0xff;
    while(!(SPSR & (1<<SPIF))) //Wait for reception complete
    ;
   // spi_set_ss(1);
    return SPDR; //return data register
;
}

void spi_set_ss(int value){
    switch(value){
        case 0:
            PORTB &= ~(1<<PB7);
          
            break;
        case 1:
            PORTB |= (1<<PB7);
           
            break;
    }
}


//1<<SPE crucial for SPI operations. Bit 6 in SPCR
//MSTR: Master/Slave select
//SPIF - status register
