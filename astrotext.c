#include "globals.h"
#include "astrotext.h"
#include "lcdLib.h"

void drawTitle();
void frameDelay(Game *game);
void drawShip(Game *game, char *topRow, char *bottomRow);
void win(Game *game);
void lose(Game *game);

void newGame(Game *game) {
	// reset game elements
	game->status = 					1;
	game->speed = 					5; // FPS
	game->shipLoc = 				0;
	game->asteroidsTop = 			0;
	game->asteroidsBottom = 		0;
	game->userProjectilesTop = 		0;
	game->userProjectilesBottom = 	0;
	
	// show title screen
	drawTitle();
}

void renderFrame(Game *game) {
	// create canvas for drawing
	char	topRow[16] = 	"                ";
	char	bottomRow[16] = "                ";
	
	// GAME LOGIC
	// user input
	
	// move projectiles
	
	// create new projectiles
	
	// check for collisions
	
	// move asteroids
	
	// check for collisions
	
	// render scene
	drawShip(game, topRow, bottomRow);
	
	// draw frame
	lcdHome();
	lcdWriteString(topRow);
	lcdRowTwoHome();
	lcdWriteString(bottomRow);
	
	// time delay between frames
	frameDelay(game);
}

void frameDelay(Game *game) {
	switch (game->speed) {
		case 5:
			_delay_ms(200);
			break;
		case 6:
			_delay_ms(167);
			break;
		case 7:
			_delay_ms(143);
			break;
		case 8:
			_delay_ms(125);
			break;
		case 9:
			_delay_ms(111);
			break;
		case 10:
			_delay_ms(100);
			break;
		default:
			lcdClear();
			lcdWriteString("game speed");
			lcdRowTwoHome();
			lcdWriteString("out of range");
			_delay_ms(10000);
			break;
	}
}

void drawTitle() {
	char *title = "   Astro-Text   ";
	lcdClear();
	lcdWrite(BLACK_SQUARE);
	u08 i;
	for (i = 0; i < 16; i++) {
		_delay_ms(100);
		lcdDecrementCursor();
		lcdWrite(title[i]);
		lcdWrite(BLACK_SQUARE);
	}
	_delay_ms(1000);
	for (i = 0; i < 5; i++) {
		lcdClear();
		lcdRowTwoHome();
		lcdWriteString(title);
		_delay_ms(1000);
		lcdClear();
		lcdWriteString(title);
		_delay_ms(1000);
	}
}

void drawShip(Game *game, char *topRow, char *bottomRow) {
	if ((game->shipLoc & 0x80) == 0x00) {
		// ship on top row
		topRow[0] = '=';
		topRow[1] = '>';
	} else {
		// ship on bottom row
		bottomRow[0] = '=';
		bottomRow[1] = '>';
	}
}

void createAsteroids(Game *game) {
	
}

void drawAsteroids(Game *game, char *topRow, char *bottomRow) {
	
}