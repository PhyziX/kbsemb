#include   	<avr/io.h>
#include 	<avr/iom16.h>
#include 	<avr/interrupt.h>
#include 	"delay.c"

void motor1(int,int);			// funtion declaration
void motor2(int,int);			// funtion declaration
void forever();					// funtion declaration
void init();

volatile int mSpeed = 0x8C;		// motor speed, start at 140
int up = 1;						// motorspeed up / down counter
volatile int direction1 = 0;	// motor1: 0 = not running, 1 = forward, -1 = break
volatile int direction2 = 0;	// motor2: 0 = not running, 1 = forward, -1 = break

/* Initialize variables for interrupt */
int main(void) {
	
	cli();						// Disable interrupts
	init();						// Initialze registers
	sei();						// Enable interrupts

	forever(); 					// Goto an endless loop
} 

/* Initialze registers */
void init(){
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
}
/* Start an endless loop  */
void forever(){
	TCCR0 = 0x02; // clkI/O/8 (From prescaler)
	TCNT0 = 0x00; // set counter to 0

	// Begin trigger pulse
	DDRC = 0xFF;
	PORTC = 0x00;
	delay_us(3);
	PORTC = 0x01;
	delay_us(3);
	PORTC = 0x00;
	// End trigger pulse

	PORTC = 0x01;
	PINC = 0x01;
	DDRC = 0xFF;
	while(bit_is_set(PINC,0)){}
	TCNT0=0x00;	//clear timer 
	while(!bit_is_set(PINC,0)){}

	if(TCNT0 < 0xFF){
		direction1 = 0;				// motor1 forward
		direction2 = 0;	

	}

	
	/* FLIP_PORT(DDRC, PingPin);   // Switch PingPin to INPUT
loop_until_bit_is_set(PINC, PingPin);     // Loop until the the PingPin goes high  (macro found in sfr_def.h)
//clears timer, reset overflow counter
reset_timer_0();       //reset timer 0
loop_until_bit_is_clear(PINC, PingPin);     // Loop until the the PingPin goes low  (macro found in sfr_def.h)
//read timer0's overflow counter
//255 is count before overflow, dependent on clock
int elapsed_time=timer0GetOverflowCount()*255+TCNT0;
//   The PING))) returns a pulse width of 29.033 uS per centimeter
PingVal = elapsed_time; */
	
	
	
	
	/* DDRC = 0x00;

	TCNT0 = 0x00;
	TCCR0 = 0x01;

	while(bit_is_set(PINC,0)){}

	TCCR0 = 0x00;

	if(TCNT0 < 10000){
		if(((direction1 == -1) && (direction2 == -1)) || ((direction1 == 0) && (direction2 == 0))){
			direction1 = 1;				// motor1 forward
			direction2 = 1;				// motor2 forward
		}else{
			direction1 = -1;			// motor1 backward
			direction2 = -1;			// motor2 backward
		}
	} */

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
