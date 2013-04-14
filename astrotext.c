#include "globals.h"
#include "astrotext.h"
#include "lcdLib.h"
#include "audioplayer.h"

u08		status; 							// status != 0 is active, status = 0 is inactive
volatile u08		speed;					// FPS
volatile u08		shipLoc; 				// location of ships tail
volatile u16		asteroidsTop;			// bits denote asteroid locations, 1 for asteroid, 0 for no asteroid
volatile u16		asteroidsBottom;
volatile u16		userProjectilesTop;
volatile u16		userProjectilesBottom;
volatile bool 		movePressed;
volatile bool 		shootPressed;

void drawTitle();
void frameDelay();
void drawShip(char *topRow, char *bottomRow);
void win();
void lose();

void gameSetup() {
	// set up audio
	audioSetup();
}

void enableButtons() {
	// turn on PCI
	sbi(PCICR, PCIE0);
	sbi(PCICR, PCIE1);
	sei();
	sbi(PCMSK0, PCINT4);
	sbi(PCMSK1, PCINT8);
}

u08* newGame() {
	// reset game elements
	status = 					1;
	speed = 					5; // FPS
	shipLoc = 					0x10;
	asteroidsTop = 				0;
	asteroidsBottom = 			0;
	userProjectilesTop = 		0;
	userProjectilesBottom = 	0;
	movePressed = 				false;
	shootPressed = 				false;
	
	// show title screen
	playTrack(TITLE_TRACK);
	drawTitle();
	playTrack(START_SOUND);
	enableButtons();
	return &status;
}

void renderFrame() {
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
	drawShip(topRow, bottomRow);
	
	// draw frame
	lcdHome();
	lcdWriteString(topRow);
	lcdRowTwoHome();
	lcdWriteString(bottomRow);
	
	// time delay between frames
	frameDelay();
	
	// reset button pressed status
	movePressed = false;
	shootPressed = false;
}

void frameDelay() {
	switch (speed) {
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
		_delay_ms(40);
		lcdDecrementCursor();
		lcdWrite(title[i]);
		lcdWrite(BLACK_SQUARE);
	}
	_delay_ms(750);	
	for (i = 0; i < 17; i++) {
			lcdRowTwoHome();
			u08 j;
			for (j = 0; j < i; j++) {
				lcdWrite(' ');
			}
			lcdWriteString("=>");
			_delay_ms(35);
	}
	_delay_ms(1000);
}

void drawShip(char *topRow, char *bottomRow) {
	if ((shipLoc & 0x10) == 0x00) {
		// ship on top row
		topRow[0] = '=';
		topRow[1] = '>';
	} else {
		// ship on bottom row
		bottomRow[0] = '=';
		bottomRow[1] = '>';
	}
}

void createAsteroids() {
	
}

void drawAsteroids(char *topRow, char *bottomRow) {
	
}

ISR(PCINT0_vect) { // move button pressed
	if (gbi(PINB, PINB4) && !movePressed) {
		tbi(shipLoc, 4);
		movePressed = true;
	}
}

ISR(PCINT1_vect) { // shoot button pressed
	lcdClear();
	lcdWriteString("shoot");
	_delay_ms(5);
}