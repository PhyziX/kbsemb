#include <avr/io.h>
#include <avr/iom16.h>
#include "delay.c"

int main(int charv, char **argv){
	//KnightRider();
	Vullen();
	return 0;
}

int KnightRider(){
	/* A & C als uitvoer en B & D als invoer */
	DDRA = 0xFF;
	DDRB = 0x00;
	DDRC = 0xFF;
	DDRD = 0x00;
	
	/* PIN2 van PORTC aan zetten */
	PORTC = 0x04;

	int running = 1;
	while(running){
		/* For loop om pin 0 naar 7 om en om aan te zetten */
		int led;
		for(led = 0x80; led > 0x01; led = led/2){
			PORTA = led;
			delay(80);
		}

		/* For loop om pin 0 naar 7 om en om aan te zetten */
		for(led = 0x01; led < 0x80; led = led*2){
			PORTA = led;
			delay(80);
		}
	}
	return 0;
}

int Vullen(){
	/* A & C als uitvoer en B & D als invoer */
	DDRA = 0xFF;
	DDRB = 0;
	DDRC = 0xFF;
	DDRD = 0;
	
	/* PIN2 van PORTC aan zetten */
	PORTC = 0x04;
	int running = 1;	

	
	int loper;		// zorgt ervoor dat de leds gaan lopen (opdracht 1b)
	int teller;		// de variabele voor de 2-forloops. 
	int grens;	// houdt in de gaten tot waar de leds moeten lopen.
				// dus als hij als waarde 0x40 heeft, dan weet het blokje dat
				// hij tot 0x40 moet doorgaan (dus tot en met 0x20)

	// het programma alleen uitvoeren zolang running true (1) is
	while(running){
		// eerst moet loper op 0 worden gezet omdat bij de eerste ronde er
		// nog geen blokje aan hoeft te staan. dit moet pas na de eerste ronde
		loper = 0;
		// grens is 0x80 omdat het eerste blokje dat aan gaat de waarde 128 heeft
		// vervolgens wordt hij gehalveerd en gaat de tweede led aan
		grens = 0x80;
		// loop wordt 8 keer doorlopen omdat er 8 leds zijn
		for (teller = 1; teller <= 8; teller++){
			
			/* For loop om pin 0 naar 7 om en om aan te zetten */
			int led;
			for(led = grens; led >= 1; led = led/2){
				// leds gaan om en om aan + de leds die aan moeten zijn
				PORTA = led + loper;
				// wachttijd
				delay(80);
			}

			/* For loop om pin 0 naar 7 om en om aan te zetten */
			// de blokjes gaan hier terug (vlnr) (om en om)
			for(led = 2; led <= (grens/2); led = led*2){
				PORTA = led + loper;
				delay(80);
			}
			// loper wordt opgehoogd met grens zodat hij weet welke de volgende 
			// ronde ook aan moet zijn
			loper = loper + grens;
			// grens wordt gehalveerd zodat de blokjes die om en om aan gaan
			// weten tot hoe ver ze moeten gaan
			grens = grens / 2;
		
		}
		delay(200);

		/*
				vanaf hier gaan we terug
				dus vrnl
		*/

		loper = 0;		// zorgt ervoor dat de leds gaan lopen (opdracht 1b)
		grens = 1;		// houdt in de gaten tot waar de leds moeten lopen.
					// dus als hij als waarde 0x40 heeft, dan weet het programma dat
					// hij tot 0x40 moet doorgaan (dus tot en met 0x20)

		// loop wordt 8 keer doorlopen omdat er 8 leds zijn
		for (teller = 1; teller <= 8; teller ++){
			
			/* For loop om pin 0 naar 7 om en om aan te zetten */
			int led;
			for(led = grens; led <= 0x80; led = led*2){
				PORTA = led + loper;
				delay(80);
			}

			/* For loop om pin 0 naar 7 om en om aan te zetten */
			for(led = 0x80; led >= (grens * 2); led = led/2){
				PORTA = led + loper;
				delay(80);
			}
			// loper wordt opgehoogd met grens zodat hij weet welke de volgende 
			// ronde ook aan moet zijn
			loper = loper + grens;
			// grens wordt verdubbeld zodat de leds die om en om aan gaan
			// weten tot hoe ver ze moeten gaan
			grens = grens * 2;
		}
		delay(200);
	}
	return 0;
}
