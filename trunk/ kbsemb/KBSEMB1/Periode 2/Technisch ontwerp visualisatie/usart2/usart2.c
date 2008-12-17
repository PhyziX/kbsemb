#define F_CPU 8000000UL

#include <stdint.h>
#include <avr/io.h>
#include "delay.h" 

unsigned short int distance;
unsigned char buffer[40];
void USART_Init();
void USART_SendString(unsigned char *);
void USART_SendByte(unsigned int );
void send(int, int);
// Initialise USART

int main(void){
	USART_Init();
	USART_SendByte(100);
	// Send byte
	send(6,6);
	send(6,7);
	send(6,8);
	send(7,8);
	send(7,7);
	send(7,6);
	send(8,6);
	send(9,6);
	send(9,7);
	send(8,7);
	send(8,8);
	send(8,9);
	send(9,9);
	send(9,8);
	send(10,8);
	send(10,9);
	send(11,9);
	send(11,10);
	send(11,11);
}

void USART_Init(){
	// Set baud rate (9600)
	UBRRL = 0x33;
	// Set frame format to 8 data bits, no parity, 2 stop bits
	UCSRC = 0x86;
	// Enable receiver and transmitter
	UCSRB = 0x08; 
}

void USART_SendString(unsigned char *string){
	while(*string){
		USART_SendByte(*string++);
	}
}

void USART_SendByte(unsigned int c){
	// Wait if a byte is being transmitted
	while((UCSRA&(1<<UDRE) == 0));
	// Transmit data
	UDR = c;
}

void send(int x, int y){
	USART_SendByte(101);
	_delay_ms(30);
	USART_SendByte(x);
	_delay_ms(30);
	USART_SendByte(102);
	_delay_ms(30);
	USART_SendByte(y);
	_delay_ms(30);
}
