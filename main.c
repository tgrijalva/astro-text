/* Project 1
 * CPE 329
 * Timothy Grijalva
 */

#include "globals.h"
#include "lcdLib.h"
#include "astrotext.h"

void setup() {
	
    // SET PIN MODES
	// set data bus pins to outputs
	DDRD = 0xFF;
	// set control signal pins to outputs
	sbi(DDRB, DDB0);
	sbi(DDRB, DDB1);
	sbi(DDRB, DDB2);
	
	lcdInit();
}

int main() {
    setup();

	char *hello = "hello world!";
	char *mom = "hello your mom!";
	// main run loop
	for (;;) {
		// hello your mom program
		// u08 i;
		// for (i = 0; i < 5; i++) {
		// 	lcdWriteString(hello);
		// 	_delay_ms(1000);
		// 	lcdClear();
		// 	lcdRowTwoHome();
		// 	lcdWriteString(hello);
		// 	_delay_ms(1000);
		// 	lcdClear();
		// }
		// lcdWriteString(hello);
		// _delay_ms(1000);
		// lcdClear();
		// lcdRowTwoHome();
		// lcdWriteString(mom);
		// _delay_ms(1000);
		// lcdClear();
		
		// astrotext game
		Game game;
		newGame(&game);
		while(game.status == 1) {
			renderFrame(&game);
			_delay_ms(1000);
			game.shipLoc = 0x80;
			renderFrame(&game);
			_delay_ms(1000);
			game.shipLoc = 0x00;
		}
		lcdClear();
		lcdWriteString("not to be seen");
		_delay_ms(10000);
		if (game.status == 2) {
			// win
			lcdWriteString(hello);
		} else {
			// lose
			lcdWriteString(mom);
		}
	}
}