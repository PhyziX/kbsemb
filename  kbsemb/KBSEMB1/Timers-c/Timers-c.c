#include   	<avr/io.h>
#include 	<avr/iom16.h>
#include 	<avr/interrupt.h>

void motor1(int,int);
void motor2(int,int);
void forever();

int i = 0;

/* Initialize variables for interrupt */
int main(void) {
	/* cli();
	TCCR1A 	= 0x80;		// Compare ouput mode
	TCCR1B 	= 0x01;		// Counter frequency
	OCR1AH 	= 0x01;		// Compare register high
	OCR1AL 	= 0x01;		// Compare register low
	TIMSK 	= 0x10;		// Set compare flag
	TCNT1H 	= 0x00;		// Set high counter value to zero
	TCNT1L 	= 0x00;		// Set low counter value to zero
	sei(); */

	cli();
	TCCR2 = 0x22;
	OCR2 = 0x08;
	TIMSK = 0x80;
	TCNT2 = 0x00;
	sei();

	forever(); 			// Goto an endless loop
	
	// for(;;){ motor1(0x8F,1); }

} 

/* Start an endless loop  */
void forever(){
	PORTA = 0xFF;
	forever();
}

/* If an interrupt accures, execute this code */
ISR(TIMER2_COMP_vect){
	if(i == 0){
		motor1(0xFF, 1);	// Start motor 1 motorX(speed,direction);
		i = 1;
	}else{
		motor2(0xFF, 1);
		i = 0;
	}
	
	TCNT2 = 0x00;		// Set counter value to zero		
}


void motor1(int speed, int direction){
		OCR1AL = speed;
		OCR1AH = 0; 
		
		if(direction == 1){
			PORTD = 0x60;
			DDRD = 0x60;
		}else if(direction == -1){
			PORTD = 0xA0;
			DDRD = 0xA0;
		}else{
			PORTD = 0xE0;
			DDRD = 0xE0;
		} 

		TCCR1A = 0x81;
		TCCR1B = 0x01;
			
}


void motor2(int speed, int direction){
    	OCR1BL = speed;
		OCR1BH = 0; 
		PORTD = 0x10;
		DDRD = 0x10;	// 10

		if(direction == 1){
			PORTB = 0x01;
			DDRB = 0x01;
		}else if(direction == -1){
			PORTB = 0x02;
			DDRB = 0x02;
		}else{
			PORTB = 0x03;
			DDRB = 0x03;
		} 

		TCCR1A = 0x21;
		TCCR1B = 0x01;
}

