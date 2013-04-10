#include "globals.h"
#include "astrotext.h"
#include "lcdLib.h"

void drawShip(Game *game, char *topRow, char *bottomRow);

void newGame(Game *game) {
	game->status = 1;
	game->shipLoc = 0x00;
	game->asteroidsTop = 0;
	game->asteroidsBottom = 0;
	game->userProjectilesTop = 0;
	game->userProjectilesBottom = 0;
}

void renderFrame(Game *game) {
	// create canvas for drawing
	char	topRow[16] = "                ";
	char	bottomRow[16] = "                ";
	
	// check for collisions
	
	// render scene
	drawShip(game, topRow, bottomRow);
	
	// draw frame
	lcdHome();
	lcdWriteString(topRow);
	lcdRowTwoHome();
	lcdWriteString(bottomRow);
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