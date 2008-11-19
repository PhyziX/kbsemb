#include   	<avr/io.h>   //gcc
#include 	<avr/iom16.h>
#include 	<avr/interrupt.h>

#define outp(a, b) b = a

int main(void) {
	
	for(;;){
		motor1(0xAF, 1);
		motor2(0xAF, 1);
	}

} 


void motor1(int speed, int direction){
        OCR1AL 	= speed;   		//Load Pulse width - 175
        OCR1AH 	= 0;
	
		if(direction == 1){
			PORTD = 0x60;		// forward, bit 5 & 6
			DDRD  = 0x60;
		}else if(direction == -1){
			PORTD = 0xA0;		// backward, bit 5 & 7
			DDRD = 0xA0;
		}else{
			PORTD = 0xE0;		// brake, bit 5,6 & 7
			DDRD  = 0xE0;
		}

        TCCR1A 	= 0x81;         //8-bit, Non-Inverted PWM
        TCCR1B 	= 0x01;         //Start PWM
}


void motor2(int speed, int direction){
        OCR1AL 	= speed;   		//Load Pulse width - 175
        OCR1AH 	= 0;
		PORTD = 0x08;			// set pwm2
		
		if(direction == 1){
			PORTB = 0x01;		// forward, bit 0
			DDRB  = 0x01;
		}else if(direction == -1){
			PORTB = 0x02;		// backward, bit 1
			DDRB = 0x02;
		}else{
			PORTB = 0x03;		// brake, bit 0 & 1
			DDRB  = 0x03;
		}

        TCCR1A 	= 0x81;         //8-bit, Non-Inverted PWM
        TCCR1B 	= 0x01;         //Start PWM
}
