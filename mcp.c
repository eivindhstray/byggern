#include "mcp.h"
#include "MCP2515.h"
#include <stdint.h>
#include <stdio.h>
#include "spi.h"
#include <inttypes.h>
#include <util/delay.h>

void mcp_init(void){
    spi_master_init();
    mcp_reset();

    
}

int mcp_read(int address){  //for some reason we are not allowed to use uint8_t 
    
    spi_master_transmit(MCP_READ);
    spi_master_transmit(address);
    int data = spi_read();
    return data;
    
}

void mcp_write(int address, int data){
   
    spi_master_transmit(MCP_WRITE);
    spi_master_transmit(address);
    spi_master_transmit(data);
    
}


void mcp_reset(void){
    
    spi_master_transmit(MCP_RESET);
    _delay_ms(200);
    
}

int mcp_read_status(void){

    spi_master_transmit(MCP_READ_STATUS);
    return MCP_READ_STATUS;
}

int mcp_ready_to_send(void){
    if( (MCP_TXB0CTRL & (1<<3)) == 0){
        return 1;
    }
    return 0;
}
void mcp_request_to_send(int buffer_number){
    //spi_set_ss(0);
    buffer_number = buffer_number % 3;
    char data = MCP_RTS_TX0;
    if(buffer_number == 0){
        data = MCP_RTS_TX0;
    }
    else if (buffer_number == 1){
        data = MCP_RTS_TX1;
    }
    else if (buffer_number == 2){
        data = MCP_RTS_TX2;
    }
    spi_master_transmit(data);

}


void mcp_bit_modify(int address, int mask, int data){
    spi_master_transmit(MCP_BITMOD);
    spi_master_transmit(address);
    spi_master_transmit(mask);
    spi_master_transmit(data);
}