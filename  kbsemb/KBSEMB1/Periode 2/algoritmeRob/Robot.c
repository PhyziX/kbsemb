#define 	F_CPU 8000000UL		// Needed for delay function
#include   	<avr/io.h>
#include 	<avr/iom16.h>
#include 	<avr/interrupt.h>
#include	"Usart.h"
#include	"Motors.h"
#include 	"delay.h"
#include	"sensors.h"

void motor1(int,int);			// funtion declaration
void motor2(int,int);			// funtion declaration
void forever();					// funtion declaration
void init();					// funtion declaration

int distance;					// distance in cm from sensors
volatile int mSpeed = 0xA0;		// motor speed, start at 160
volatile int direction1 = 0;	// motor1: 0 = not running, 1 = forward, -1 = backward
volatile int direction2 = 0;	// motor2: 0 = not running, 1 = forward, -1 = backward

int main(int argc, char** argv) {
	
	cli();						// Disable interrupts
	init();						// Initialize variables for interrupt
	USART_Init();				// Initialize USART variables
	sei();						// Enable interrupts

	forever(); 					// Goto an endless loop
	return 0;
} 

/* Start an endless loop  */
void forever(){
	if(bit_is_set(PINB, 4)){	
		while(bit_is_set(PINB, 4)){}		
		mSpeed = 0xA0;
		direction1 = 1;
		direction2 = 1;
	}
	forever();					// Start an endless loop
}

/* Initialize variables for interrupt */
void init(){
	// Set values for timer/counter2 (interrupt)
		TCCR2 = 0x02;			// COM20 & CS21
		OCR2 = 0xFD;			// fc Output compare 
		TIMSK = 0xC0;			// Set compare flag, overflow & compare
		TCNT2 = 0xFB;			// Reset counter
	
	// Set values for timer/counter1 (motors)
		TCCR1A = 0xA1;			// Set COM1A1, COM1B1 & WGM10
		TCCR1B = 0x01;			// CS10

	// Set values for timer/counter0 (ultrasone sensors)
		TCCR0 = 0x04;			// Set frequency at 256
	
	// Set PWM signal for motors
		PORTD = 0x34;			// Set PWM1 & PWM2 signal
		DDRD = 0x34;			// Set PWM1 & PWM2 signal

	// Onboard leds off
		DDRB = 0xFF;
}

// Interrupt routine: Overflow
ISR(TIMER2_OVF_vect){					
	motor1(mSpeed, direction1);		// Start motor1
	
	int i;
	int j = 1;
	for(i = 0; i < 5; i++){
		_delay_ms(5);
		distance = sensor1();		// Read sensor 1, returns distance in cm
		if(distance <= 7){
			j++;
		}
	}
	if(j == 5){
		direction1 = 0;
		direction2 = 0;
	}
	TCNT2 = 0xFB;					// Set counter value 
}

// Interrupt routine: Compare
ISR(TIMER2_COMP_vect){
	motor2(mSpeed, direction2);		// Start motor2
}



