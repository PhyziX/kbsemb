#include <stdint.h>
#include <avr/io.h>
#include <avr/delay.h> 

int distance;
void USART_init();
void USART_SendByte(uint8_t);
int main(void){
	TCCR0 = 0x01;  // cs00, no prescaling
	while(1){
        // Output pulse to Ping))) 
        DDRB = (1 << PB3); 
        _delay_us(5); 

        // Bring pin to high-z input 
        DDRB = 0x00; 

        _delay_us(750); 
  
       // wait for PB3 to go high 
        loop_until_bit_is_set(PINB, PINB3); 
        TCNT0 = 0; 

        // wait for PB3 to go low 
        loop_until_bit_is_clear(PINB, PINB3); 
        //distance = (0.27 * TCNT1) / 29.033;    // 3.6864MHz = 0.27uS/cycle; 29.033uS/cm 
        distance = ((0.27 * TCNT0) / 73.746) / 2;    // 3.6864MHz = 0.27uS/cycle; 73.746uS/in; 2 (round trip time) 
        //itoa(TCNT1, buffer, 10); 
        // itoa(distance, buffer, 10); 

        // usart_tx_string(buffer); 
        // usart_tx_string("in"); 
       	// usart_tx('\r'); 
        // usart_tx('\n'); 

		uint8_t Data;
		// Initialise USART
		USART_Init();
		// Send string
		USART_SendByte(distance);
        _delay_ms(1); 

    } 

}

void USART_Init(){
	// Set baud rate (9600)
	UBRRL = 0x67;
	// Set frame format to 8 data bits, no parity, 2 stop bits
	UCSRC = 0x0E;
	// Enable receiver and transmitter
	UCSRB = 0x08; 
}


void USART_SendByte(uint8_t Data){
	// Wait if a byte is being transmitted
	while((UCSRA&(1<<UDRE)) == 0);
	// Transmit data
	UDR = Data;
}

