#include   	<avr/io.h>
#include 	<avr/iom16.h>
#include 	<avr/interrupt.h>

int main(void) {
	cli();
	TCCR1A = 0x80;		// Compare ouput mode
	TCCR1B = 0x01;		// Counter frequency
	OCR1AH = 0x01;		// Compare register high
	OCR1AL = 0x01;		// Compare register low
	TIMSK = 0x10;		// Set compare flag
	TCNT1H = 0x00;		// Set high counter value to zero
	TCNT1L = 0x00;		// Set low counter value to zero
	sei();

	forever();
} 

void forever(){
	PORTA = 0xFF;
	forever();
}
ISR(TIMER1_COMPA_vect)
	{
		
		motor1(0xAF, 1);
		TCNT1H = 0x00;		// Set high counter value to zero
		TCNT1L = 0x00;		// Set low counter value to zero
			// motor2(0xAF, 1);
		

		/*
		cli					; Disable interrupts
		ldi temp, 0x80
		out TCCR1A, temp	; Set check for compare flag A
		ldi temp, 0x04		; (0x01 test value)
		out TCCR1B, temp 	; Set counter frequency (0x04 = Cl_fr/256)
		ldi temp, 0xF4		; (0x01 test value)
		out OCR1H, temp		; Compare register high (value to compare to counter)
		ldi temp, 0x24		; (0x01 test value)
		out OCR1L, temp		; Compare register low
		ldi	temp, 0x10
	    out	TIMSK, temp		; Set compare flag (tell the counter to compare to OCR1A)
		ldi temp, 0x00
		out TCNT1H, temp	; Set high counter value to zero
		out TCNT1L, temp	; Set low counter value to zero
		sei					; Enable interrupts
		*/

	}

void motor1(int speed, int direction){
        int i = TCNT1L;
		TCNT1L = 0x00; 
		OCR1AL 	= speed;   		//Load Pulse width - 175
        OCR1AH 	= 0;
	
		if(direction == 1){
			PORTD = 0x60;		// forward, bit 5 & 6
			DDRD  = 0x60;
			TCNT1L = i;
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
