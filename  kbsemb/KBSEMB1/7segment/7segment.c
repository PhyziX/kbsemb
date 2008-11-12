#include <avr/io.h>
#include <avr/iom16.h>
#include "delay.c"
#define BOOL unsigned int
#define TRUE 1
#define FALSE 0

	int display_index[17] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 
						0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x40};
						 		// array met [weer te geven cijfer / letter / - (0-9, A-F, -)]
	int getal[4]; 				// array die benodigd is om de drie digit integer invoer 
								// om te zetten in losse integer digits
	int disp;					// geeft aan welke display aan de beurt is
	int running = TRUE;

int raiseNumber(int getal[], int radix){
	radix -= 1;							// zet goede grondtal
	/*
	kijk of het getal te groot is om weer te geven op de displays 
	als het getal te groot is, zet streepjes neer (16 in tabel = -)
	*/
	if((getal[1] > radix) || (getal[2] > radix) || (getal[3] > radix)){
		getal[1] = 16;
		getal[2] = 16;
		getal[3] = 16;
	}
	/* als getal op display past */
	else{
		/* als er op knop 1 gedrukt is */
		if(bit_is_set(PINB, 2)){
			/* als rechter getal minder dan radix-1 is, tel er 1 bij op */
			if(getal[1] < radix){
				getal[1]++;
			}
			else{
				getal[1] = 0;
				/* als middelste getal minder dan radix-1 is, tel er 1 bij op */
				if(getal[2] < radix){
					getal[2]++;
				}
				else{
					getal[2] = 0;
					/* als linker getal minder dan radix-1 is, tel er 1 bij op */

					if(getal[3] < radix){
						getal[3]++;
					}
					/* als linker getal radix-1 of groter is, zet streepjes neer */
					else if(getal[3] >= radix){
						getal[1] = 16;
						getal[2] = 16;
						getal[3] = 16;
					}
				}
			}
		}
		while(bit_is_set(PINB, 2)){
			// wacht tot knop niet meer ingedrukt is
		}
		/* kijkt of er op knop 2 gedrukt is: aftrekken */
		if(bit_is_set(PINB, 4)){
			if((getal[1] == 0) && (getal[2] == 0) && (getal[3] == 0)){
				getal[1] = 16;
				getal[2] = 16;
				getal[3] = 16;
			}
			if((getal[1] == 16) && (getal[2] == 16) && (getal[3] == 16)){
				// blijf op streepjes staan
			}
			else if(getal[1] > 0){
				getal[1]--;
			}
			else{
				getal[1] = radix;
				if(getal[2] > 0){
					getal[2]--;
				}
				else{
					getal[2] = radix;
					if(getal[3] > 0){
						getal[3]--;
					}
					else{
						getal[1] = 16;
						getal[2] = 16;
						getal[3] = 16;
					}
				}
			}
		}
		while(bit_is_set(PINB, 4)){
			// wacht tot knop niet meer ingedrukt is
		}
	}
	return getal;
}

void display (int invoer, int radix){
	
								// A & C als uitvoer en B & D als invoer 
	DDRA = 0xFF;				// 0xFF = 11111111 binair
	DDRB = 0x00;
	DDRC = 0xFF;
	DDRD = 0x00;
	
	getal[0] = 0;				// doet niets, index 1-3 is leesbaarder dan index 0-2
	getal[1] = (invoer/1)%10;	// meest rechtse getal (rechter display, display D1)
	getal[2] = (invoer/10)%10;	// middelste getal (midden display, display D2)
	getal[3] = (invoer/100)%10;	// linkse getal (linker display, display D3)
								// let op, er wordt dus van rechts naar links gerekend!
	while(running == TRUE){

		for(disp = 1; disp <= 3; disp++){
			// zet goede PIN van PORTC open
			// poortwaardes: 	PIN0 = 0x01, PIN1 = 0x02, PIN2 = 0x04, PIN3 = 0x08, 
			// 					PIN4 = 0x10, PIN5 = 0x20, PIN6 = 0x40, PIN7 = 0x80
			// PIN3, 4 en 5 horen respectievelijk bij display 1,2 en 3
			raiseNumber(getal, radix);
			if(disp == 1){
				PORTC = 0x08;	// zet PIN3 aan (rechter display)
				PORTA = display_index[getal[1]];
				delay(1);
			}
			if(disp == 2){	// zet PIN4 aan	(midden display)
				PORTC = 0x10;
				PORTA = display_index[getal[2]];
				delay(1);
			}
			if(disp == 3){	// zet PIN5 aan (linker display)
				PORTC = 0x20;
				PORTA = display_index[getal[3]];
				delay(1);
			}
			
		}
	}
}

int main(int argc, char ** argv){
	display(999, 10);
	// gebruik geen nul aan het begin (tenzij startgetal 0 is), anders ziet de compiler het als octaal getal
	return 0;
}
