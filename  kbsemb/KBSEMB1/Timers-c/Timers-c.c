#include   <avr/io.h>   //gcc
#include <avr\iom16.h>

#define outp(a, b) b = a

int main(void) {
	pwm();
	int i = 2;
	int p = 4;
	for(i = 0; i < 3; i++){
		i = i + p;
	}
	while(1){
	}
} 


void pwm(){
	/* set OC2 for PWM output*/

	outp((1<<PINB3), DDRB);

	/*set timer counter initial value*/

	TCNT1=0x00;

	/*Set timer output compare register*/

	OCR1A=0x80;

	/*start timer:

	without presscaler

	Non inverted mode in OC2 pin;

	phase corect PWM*/
	TCCR1A = 0xC9;
	//outp((1<<FOC1A)|(1<<COM1A0)|(1<<COM1A0)|(1<<WGM10), TCCR1A);
	TCCR1B = 0x01;
	//outp((1<<CS10), TCCR1B);

}
