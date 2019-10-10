#include "mcp.h"
#include <stdio.h>
#include "spi.h"
#include "can.h"
#include "MCP2515.h"
#include <avr/interrupt.h>




void can_set_mode(int mode){
    mcp_bit_modify(MCP_CANCTRL, 0b11100000, mode);
}

void can_init(void){
    spi_set_ss(0);
    // received message interrupt
    mcp_bit_modify(MCP_CANINTE, 0b00000001,1);

    mcp_bit_modify(MCP_CANINTE, 0b00000100,1);

    //clear interrupt flag
    mcp_bit_modify(MCP_CANINTF, 0b00000001,0);

    mcp_bit_modify(MCP_CANINTF, 0b00000100,0);

    //set interrupt on PD2 to falling edge
    MCUCR |= (1<<ISC01);

    //enable interrupt on PD2
    GICR |= (1<<INT0);

    //clear interrupt flag on PD2
    GIFR |= (1<<INTF0);

    //mcp_init();

    can_set_mode(0x40);

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


    uint8_t id_high = mcp_read(MCP_RXB0SIDH)*0b1000;
    uint8_t id_low = mcp_read(MCP_RXB0SIDL)/0b100000;

    message->id = id_high + id_low;

    message->length = mcp_read(MCP_RXB0DLC);

 
    for (int i = 0 ; i<message->length; i++){
        message->data[i] = mcp_read(MCP_RXB0D0 + i );
        printf("%d\n\r", message->data[i]);
    }
    
   

}


