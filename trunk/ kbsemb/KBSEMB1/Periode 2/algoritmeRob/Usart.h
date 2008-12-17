/*
	USART

	Last edited:	10-12-2008
	Created by:		Windesheim, M3TI, Groep 2
*/

//#include <stdint.h>
//#include <avr/io.h>

#include "delay.h"

void USART_Init();				
void USART_SendString(unsigned char *);
void USART_SendByte(unsigned char );
void send(int,int);

void USART_Init(){
	UBRRL = 0x33;	// Set baud rate (9600) for 8Mhz (ATMega16 datasheet) 
	UCSRC = 0x86;	// Set frame format to 8 data bits, no parity, 1 stop bits
	UCSRB = 0x08; 	// Enable receiver and transmitter
}

void USART_SendString(unsigned char *string){
	while(*string){
		USART_SendByte(*string++);
	}
}

void USART_SendByte(unsigned char c){	
	while((UCSRA&(1<<UDRE)) == 0); // Wait if a byte is being transmitted
	UDR = c;	// Transmit data
}

void send(int x, int y){
	USART_SendByte(101);
	_delay_ms(30.0);
	USART_SendByte(x);
	_delay_ms(30.0);
	USART_SendByte(102);
	_delay_ms(30.0);
	USART_SendByte(y);
	_delay_ms(30.0);
}
