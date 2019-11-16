#include "mcp.h"
#include <stdio.h>
#include "spi.h"
#include "can.h"
#include "MCP2515.h"
#include <avr/interrupt.h>
#include "uart.h"




void can_set_mode(int mode){
    mcp_bit_modify(MCP_CANCTRL, 0b11100000, mode);
}

void can_init(void){
    spi_set_ss(0);

    mcp_bit_modify(MCP_CANINTE, 0b00000011,0b11);

    //clear interrupt flag
    mcp_bit_modify(MCP_CANINTF, 0b00000011,0b00);


    //enable INT0 to update whenever information is sent from node2
    GICR |= (1 << INT0); 
	MCUCR |= (1 << ISC01); 
	MCUCR &= ~(1 << ISC00); 
	DDRD &=  ~(1 << PIND2);

    //mcp_init();

    can_set_mode(0x00);

    spi_set_ss(1);

    sei(); //could probably be removed


    //set up interrupt for sending message



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

int can_should_send(message_t message, uint8_t position_before[8]){
    if ((abs(message.data[0] - position_before[0]) >3)|| (abs(message.data[1] - position_before[1])>3) || 
    (abs(message.data[3] - position_before[3])>3) || (abs(message.data[4] - position_before[4])>0)){
			can_send_message(&message);	
		}
		for(int i = 0; i<8; i++){
			position_before[i] = message.data[i];
		}	
}


message_t can_receive_message(message_t *message){    

    uint8_t id_high = mcp_read(MCP_RXB0SIDH)<<3;
    uint8_t id_low = mcp_read(MCP_RXB0SIDL)>>5;

    message->id = id_high + id_low;

    message->length = mcp_read(MCP_RXB0DLC);

 
    for (int i = 0 ; i<message->length; i++){
        message->data[i] = mcp_read(MCP_RXB0D0 + i );
    }

    mcp_bit_modify(MCP_CANINTF,0b11,0b00);

    
}





