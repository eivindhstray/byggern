#include "uart.h"

bool transmit_ready(void){
	if(/*condition*/){
		return 0;
	}
	return 1;
}

unsigned int USART_Resceive(void){
	unsigned char status, resh, rel;
	
	while(!(UCSRA0 & (1<<RXC0)))
		status = UCRSA0;
		resh = UCRSB0;
		resl = UDR0;
	
	if (status & (1<<FE) | (1<<DOR) | (1<<UPE))
		return -1;
	
	
	resh = (resh >> 1) & 0x01;
	return ((resh << 8) | resl);
}


unsigned char USART_Receive( void ){
/* Wait for data to be received */
while ( !(UCSRA & (1<<RXC)) );
/* Get and return received data from buffer */
return UDR;
}



//void USART_Transmit( unsigned char data ){
/* Wait for empty transmit buffer */
//while ( !( UCSRA & (1<<UDRE)) );
/* Put data into buffer, sends the data */
//UDR = data;
//}/*



void USART_Transmit( unsigned int data ){
/* Wait for empty transmit buffer */
while ( !( UCSRA & (1<<UDRE)) );
/* Copy 9th bit to TXB8 */UCSRB &= ~(1<<TXB8);if ( data & 0x0100 )UCSRB |= (1<<TXB8);/* Put 
data into buffer, sends the data */
UDR = data;
}
