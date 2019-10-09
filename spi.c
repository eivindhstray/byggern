#include "spi.h"
#include "MCP2515.h"
#include <stdint.h>
#include <avr/io.h>

void set_CS(int value){
    switch(value){
        case 0:
            PORTB = (0<<PB4);
            break;
        case 1:
            PORTB = (1<<PB4);
            break;
    }

}

void spi_master_init(void){
    DDRB = (1<<PB5) | (1<<PB7); //set MOSI and SCK output, all others input
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0); //enable spi, master, set clock rate fck/16
}

void spi_master_transmit(char cData){
    SPDR = cData; //start transmission
    while(!(SPSR & (1<<SPIF)))//wait for transmission complete
    ;
}

void spi_slave_init(void){
    DDRB = (1<<PB6); //set MISO output, all others input
    SPCR = (1<<SPE); //enable SPI
}

char spi_slave_receive(void){
    while(!(SPSR & (1<<SPIF))) //Wait for reception complete
    ;
    return SPDR; //return data register
}

//1<<SPE crucial for SPI operations. Bit 6 in SPCR
//MSTR: Master/Slave select
//SPIF - status register

char mcp_read(char content){
    set_CS(0);
    spi_master_transmit(content);

    set_CS(1);
}