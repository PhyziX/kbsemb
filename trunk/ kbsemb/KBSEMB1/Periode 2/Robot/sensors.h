int distance = 0;				// measured distance with ultrasone sensor

int sensor1(){					
	// Output pulse to Ping))) - Trigger pulse
	DDRC = (1 << PC2);			// Set port as to output
	PORTC = (1 << PC2);			// Set port high
    _delay_us(5); 				// Wait 5 microseconds
        					// Bring pin to high input 
    DDRC = (0 << PC2);			// Set port as input
	PORTC = (0 << PC2);			// Set port low
    _delay_us(750); 			// Wait 750 microseconds
       						// Wait for pin to go high 
    loop_until_bit_is_set(PINC, PINC2); 
    TCNT0 = 0; 					// Start counter
       						// Wait for pin to go low 
    loop_until_bit_is_clear(PINC, PINC2);
    distance = TCNT0 / 1,90;	// TCNT0 divide by 1,90 to get distance in cm
    _delay_us(200); 			// Wait 200 micro seconds for next measurement
	
	return distance;
}

int sensor2(){					
	// Output pulse to Ping))) - Trigger pulse
	DDRC = (1 << PC3);			// Set port as to output
	PORTC = (1 << PC3);			// Set port high
    _delay_us(5); 				// Wait 5 microseconds
        					// Bring pin to high input 
    DDRC = (0 << PC3);			// Set port as input
	PORTC = (0 << PC3);			// Set port low
    _delay_us(750); 			// Wait 750 microseconds
       						// Wait for pin to go high 
    loop_until_bit_is_set(PINC, PINC3); 
    TCNT0 = 0; 					// Start counter
       						// Wait for pin to go low 
    loop_until_bit_is_clear(PINC, PINC3);
    distance = TCNT0 / 1,90;	// TCNT0 divide by 1,90 to get distance in cm
    _delay_us(200); 			// Wait 200 micro seconds for next measurement
	
	return distance;
}

int sensor3(){					
	// Output pulse to Ping))) - Trigger pulse
	DDRC = (1 << PC4);			// Set port as to output
	PORTC = (1 << PC4);			// Set port high
    _delay_us(5); 				// Wait 5 microseconds
        					// Bring pin to high input 
    DDRC = (0 << PC4);			// Set port as input
	PORTC = (0 << PC4);			// Set port low
    _delay_us(750); 			// Wait 750 microseconds
       						// Wait for pin to go high 
    loop_until_bit_is_set(PINC, PINC4); 
    TCNT0 = 0; 					// Start counter
       						// Wait for pin to go low 
    loop_until_bit_is_clear(PINC, PINC4);
    distance = TCNT0 / 1,90;	// TCNT0 divide by 1,90 to get distance in cm
    _delay_us(200); 			// Wait 200 micro seconds for next measurement
	
	return distance;
}
