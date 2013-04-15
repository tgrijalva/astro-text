/* Project 1
 * CPE 329
 * Timothy Grijalva
 */

#include "globals.h"
#include "lcdLib.h"
#include "astrotext.h"

void setup() {
	
    // SET PIN MODES
	// set data bus and control signal pins to outputs
	DDRD = 0xFF;
	sbi(DDRB, DDB0);
	sbi(DDRB, DDB1);
	sbi(DDRB, DDB2);
	
	// game setup
	gameSetup();
	
	// lcd setup
	lcdInit();
	lcdCursorStyle(false, false);
}

int main() {
    setup();

	// main run loop
	for (;;) {
		// hello world program
		lcdClear();
		char *hello = "Hello World!";
		lcdWriteString(hello);
		while( !(gbi(PINB, PINB4) | gbi(PINC, PINC0)) ) {
			// wait for button press
		}
		
		// Astrotext game
		u08 *gameStatus = newGame();
		while(*gameStatus) {
			renderFrame();
		}
	}
}