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

	// this string is a hack to fix a major bug
	// that was occurring after audio files were added using PROGMEM.
	// how does it work? no one may ever know.
	lcdWriteString("");

	// main run loop
	for (;;) {
		// hello world program
		lcdClear();
		lcdWriteString("Hello World!");
		while( !(gbi(PINB, PINB4) | gbi(PINC, PINC0)) ) {
			// wait for button press
		}
		
		// Astrotext game
		bool *gameStatus = newGame();
		while(*gameStatus) {
			renderFrame();
		}
	}
}