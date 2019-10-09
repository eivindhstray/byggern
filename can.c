#include "mcp.h"
#include <stdio.h>
#include "spi.h"
#include "can.h"
#include "MCP2515.h"

void can_set_mode(int mode){
    mcp_bit_modify(MCP_CANCTRL, 0b11100000, mode);
}

void can_init(void){

    mcp_init();

    can_set_mode(0x40);

}


void can_send_message(message_t message){
    mcp_write(MCP_TXB0SIDH, (message.id)>>3);
    mcp_write(MCP_TXB0SIDL, (message.id)<<5);  //2 first are ID, we wish to know why this is this way!
    mcp_write(MCP_TXB0DLC, message.length);     // length
    for(int i = 0; i<8; i++){
        mcp_write(MCP_TXB0D0 + i , message.data[i]); //data to be sent
    }
    mcp_request_to_send(0);

}


message_t can_receive_message(){
    message_t message;

    uint8_t id_low = mcp_read((MCP_RXB0SIDH)<<3);
    uint8_t id_high = mcp_read((MCP_RXB0SIDL)>>5);

    message.length = mcp_read(MCP_RXB0DLC);

    int array[8];
    for (int i = 0 ; i<message.length; i++){
        array[i] = mcp_read(MCP_RXB0D0 + i );
    }
    *message.data = array;
    return message;

}

