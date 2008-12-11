/*
	USART

	Last edited:	11-12-2008
	Created by:		Windesheim, M3TI, Groep 2
*/

void motor1(int speed, int direction){
		OCR1AL = speed;			// Save speed in OCR1AL
		OCR1AH = 0; 
		
		if(direction == 1){			// If forward
			PORTD = 0x70;			// PWM1,PWM2 & Forward bit
		}else if(direction == -1){		// If backward
			PORTD = 0xB0;			// PWM1,PWM2 & Backward bit
		}else{					// Else, stop
			PORTD = 0xF0;			// PWM1,PWM2 & Forward & backward bit
		} 
}

void motor2(int speed, int direction){
		OCR1BL = speed;			// Save speed in OCR1BL
		OCR1BH = 0; 
		if(direction == 1){			// If forward
			PORTB = 0x02;			// Forward bit
		}else if(direction == -1){		// If backward
			PORTB = 0x01;			// Backward bit
		}else{					// Else, stop
			PORTB = 0x03;			// Forward & backward bit
		}
}
