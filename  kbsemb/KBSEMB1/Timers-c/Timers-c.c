#include <avr/io.h>

int main (void)
{
	int i = 0;
	DDRA = 255; // Set LED as output
	DDRB = 255;
	DDRC = 255;
	DDRD = 0;
	PORTC = 0x04;
	

	TCCR1B = 0x04; // Set up timer at Fcpu/64 

	for (;;)
	{
		// Check timer value in if statement, true when count matches 1/20 of a second
		if (TCNT1 >= 62500)
		{
			if(i == 1){
				PORTA = 255;
				i = 0;
			}
			else{
				PORTA = 0;
				i = 1;
			}

		 	TCNT1 = 0; // Reset timer value
		}
	}
	} 
