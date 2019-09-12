#include "adc.h"
#include "io.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>




int x_pos(void){
    volatile uint8_t *ext_ram = (char*) 0x1400;
    ext_ram[0] = 0x04;
	_delay_ms(60);
    volatile uint8_t out = ext_ram[0];
    return out;
}


int y_pos(void){
    volatile char *ext_ram = (char*) 0x1400;
    ext_ram[0] = 0x05;
	_delay_ms(60);
	uint8_t out = ext_ram[0];
	return out;
}

int l_slider(void){
    volatile char *ext_ram = (char*) 0x1400;
    ext_ram[0] = 0x06;
	_delay_ms(60);
	uint8_t out = ext_ram[0];
	return out;
}

int r_slider(void){
    volatile char *ext_ram = (char*) 0x1400;
    ext_ram[0] = 0x07;
	_delay_ms(60);
	uint8_t out = ext_ram[0];
	return out;
}
