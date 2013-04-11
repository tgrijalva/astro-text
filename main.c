/* Project 1
 * CPE 329
 * Timothy Grijalva
 */

#include "globals.h"
#include "lcdLib.h"
#include "astrotext.h"

void helloWorld();

void setup() {
	
    // SET PIN MODES
	// set data bus pins to outputs
	DDRD = 0xFF;
	// set control signal pins to outputs
	sbi(DDRB, DDB0);
	sbi(DDRB, DDB1);
	sbi(DDRB, DDB2);
	
	// setup pwm output for audio
	sbi(DDRB, DDB3);
	sbi(TCCR2A, COM2A1);
	sbi(TCCR2A, WGM21);
	sbi(TCCR2A, WGM20);
	sbi(TCCR2B, CS20);
	
	// setup timer for audio interrupt
	sbi(TCCR1B, WGM12);
	sbi(TCCR1B, CS11);
	OCR1A = 99;
	sbi(TIMSK1, OCIE1A);
	sei();
	
	// lcd setup
	lcdInit();
	lcdCursorStyle(false, false);
}

int main() {
    setup();

	//audio
	OCR2A = 0x7F;

	// main run loop
	for (;;) {
		// hello world program
		// helloWorld();
		
		// Astrotext game
		Game game;
		newGame(&game);
		while(game.status) {
			renderFrame(&game);
		}
		
		// debug 
		lcdClear();
		lcdWriteString("not to be seen");
		_delay_ms(10000);
	}
}

void helloWorld() {
	
	char *hello = "hello world!";
	char *mom = "Your Mom!";
	
	u08 i;
	for (i = 0; i < 5; i++) {
		lcdWriteString(hello);
		_delay_ms(1000);
		lcdClear();
		lcdRowTwoHome();
		lcdWriteString(hello);
		_delay_ms(1000);
		lcdClear();
	}
	lcdWriteString(hello);
	_delay_ms(1000);
	lcdClear();
	lcdRowTwoHome();
	lcdWriteString(mom);
	_delay_ms(1000);
	lcdClear();
}

ISR(TIMER1_COMPA_vect) {
	
}