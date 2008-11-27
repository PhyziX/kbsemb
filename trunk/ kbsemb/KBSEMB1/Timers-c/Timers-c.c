#include   	<avr/io.h>
#include 	<avr/iom16.h>
#include 	<avr/signal.h>
#include 	<avr/interrupt.h>
#include	<avr/sfr_defs.h>

void motor1(int,int);			// funtion declaration
void motor2(int,int);			// funtion declaration
void forever();					// funtion declaration

volatile int mSpeed = 0x8C;		// motor speed, start at 140
int up = 1;						// motorspeed up / down counter
volatile int direction1 = 0;	// motor1: 0 = not running, 1 = forward, -1 = break
volatile int direction2 = 0;	// motor2: 0 = not running, 1 = forward, -1 = break

/* Initialize variables for interrupt */
int main(void) {
	
	cli();
	// Set values for timer/counter2 interrupt
		TCCR2 = 0x02;			// COM20 & CS21
		OCR2 = 0xFC;			// fc Output compare 
		TIMSK = 0xC0;			// Set compare flag, overflow & compare
		TCNT2 = 0xF8;			// Reset counter
	
	// Set values for timer/counter1 (motors)
		TCCR1A = 0xA1;			// Set COM1A1, COM1B1 & WGM10
		TCCR1B = 0x01;			// CS10

	// Set PWM signal for motors
		PORTD = 0x34;			// Set PWM1 & PWM2 signal
		DDRD = 0x34;			// Set PWM1 & PWM2 signal

	// Onboard leds off
		DDRB = 0xFF;
	sei();

	forever(); 					// Goto an endless loop
} 

/* Start an endless loop  */
void forever(){
	// if PB2 is pushed, start the motors or reverse
	if(bit_is_set(PINB, 2)){
		while(bit_is_set(PINB, 2)){}	// Start if button is released
		if(((direction1 == -1) && (direction2 == -1)) || ((direction1 == 0) && (direction2 == 0))){
			direction1 = 1;				// motor1 forward
			direction2 = 1;				// motor2 forward
		}else{
			direction1 = -1;			// motor1 backward
			direction2 = -1;			// motor2 backward
		}
	// if PB3 is pushed, increase or decrease speed.
	}else if(bit_is_set(PINB, 3)){
		while(bit_is_set(PINB, 3)){}	// Start if button is released
		if(up == 1){					// If direction is up:
			if(mSpeed <= 0xAF){			// If speed <= 175 
				mSpeed = mSpeed + 0x05;	// Increase speed with 5
			}else{						// Else
				up = 0;					// The next time counting down
				mSpeed = mSpeed - 0x05;	// Decrease speed with 5
			}
		}else{
			if(mSpeed >= 0x91){			// If speed >= 145 
				mSpeed = mSpeed - 0x05;	// Decrease speed with 5
			}else{						// Else
				up = 1;					// The next time counting up
				mSpeed = mSpeed + 0x05;	// Increase speed with 5
			}
		
		}
	// if PB4 is pushed, stop the motors
	}else if(bit_is_set(PINB, 4)){		
		direction1 = 0;					// Change direction in 0
		direction2 = 0;					// Change direction in 0
	}	

	forever();							// Start an endless loop
}

// Interrupt routine: Overflow
ISR(TIMER2_OVF_vect){					
	motor1(mSpeed, direction1);			// Start motor1
	TCNT2 = 0xF8;						// Set counter value 
}

// Interrupt routine: Compare
ISR(TIMER2_COMP_vect){
	motor2(mSpeed, direction2);			// Start motor2
}


void motor1(int speed, int direction){
		OCR1AL = speed;					// Save speed in OCR1AL
		OCR1AH = 0; 
		
		if(direction == 1){				// If forward
			PORTD = 0x70;				// PWM1,PWM2 & Forward bit
		}else if(direction == -1){		// If backward
			PORTD = 0xB0;				// PWM1,PWM2 & Backward bit
		}else{							// Else, stop
			PORTD = 0xF0;				// PWM1,PWM2 & Forward & backward bit
		} 
}

void motor2(int speed, int direction){
		OCR1BL = speed;					// Save speed in OCR1BL
		OCR1BH = 0; 
	
		if(direction == 1){				// If forward
			PORTB = 0x02;				// Forward bit
		}else if(direction == -1){		// If backward
			PORTB = 0x01;				// Backward bit
		}else{							// Else, stop
			PORTB = 0x03;				// Forward & backward bit
		} 
}

