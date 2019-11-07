#include "mcp.h"
#include <stdio.h>
#include "spi.h"
#include "can.h"
#include "MCP2515.h"
#include <avr/interrupt.h>
#include <util/delay.h>




void can_set_mode(int mode){
    mcp_bit_modify(MCP_CANCTRL, 0b11100000, mode);
}

void can_init(void){
    spi_set_ss(0);
    // received message interrupt
    mcp_bit_modify(MCP_CANINTE, 0b00000011,0b11);

    //clear interrupt flag
    mcp_bit_modify(MCP_CANINTF, 0b00000011,0);

    EICRB |= (1<<ISC01);
	EIMSK |= (1<<INT2);
    //clear interrupt flag on PD2
    EIFR |= (1<<INTF2);
    
    //mcp_init();

    can_set_mode(0x00);

    spi_set_ss(1);

}


void can_send_message(message_t* message){
    mcp_write(MCP_TXB0SIDH, (message->id)>>3);
    mcp_write(MCP_TXB0SIDL, (message->id)<<5);  
    mcp_write(MCP_TXB0DLC, message->length);     // length
    for(int i = 0; i<message->length; i++){
        mcp_write(MCP_TXB0D0 + i , message->data[i]); //data to be sent
    }
    mcp_request_to_send(0);

}


void can_receive_message(message_t* message){

/* With * and /
    uint8_t id_high = mcp_read(MCP_RXB0SIDH)*0b1000;
    uint8_t id_low = mcp_read(MCP_RXB0SIDL)/0b100000;
*/
    //With shifting bits
    char can_intf = mcp_read(MCP_CANINTF);
    if(can_intf &(1<<0)){
        uint8_t id_high = mcp_read(MCP_RXB0SIDH)<<3;
        uint8_t id_low = mcp_read(MCP_RXB0SIDL)>>5;

        message->id = id_high + id_low;

        message->length = mcp_read(MCP_RXB0DLC);

    
        for (int i = 0 ; i<message->length; i++){
            message->data[i] = mcp_read(MCP_RXB0D0 + i );
        }
        can_intf &= ~(1<<0);
        can_intf &= ~(1<<1);

    }

    
    mcp_write(0x2C, can_intf);
    
    
   

}


