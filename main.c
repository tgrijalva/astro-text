/* 
 * Coded by Timothy Grijalva
 */

#include "globals.h"
#include "lcdLib.h"
#include "astrotext.h"

void setup() {	
	// GAME SETUP
	gameSetup();
}

int main() {
	setup();

	// main run loop
	for (;;) {
		// hello world program
		lcdClear();
		lcdWriteString("Hello World!");
		_delay_ms(500);
		waitForInput();
		
		// Astrotext game
		bool *gameStatus = newGame();
		while(*gameStatus) {
			renderFrame();
		}
		waitForInput();
	}
}
