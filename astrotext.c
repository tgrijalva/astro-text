#include "globals.h"
#include "astrotext.h"
#include "lcdLib.h"
#include "audioplayer.h"

bool				status; 				// status != 0 is active, status = 0 is inactive
volatile u08		speed;					// FPS
volatile u08		shipLoc; 				// location of ships tail
volatile u16		asteroidsTop;			// bits denote asteroid locations, 1 for asteroid, 0 for no asteroid
volatile u16		asteroidsBottom;
volatile u16		destroyedAsteroidsTop;
volatile u16		destroyedAsteroidsBottom;
volatile u16		userProjectilesTop;
volatile u16		userProjectilesBottom;
volatile bool 		movePressed;
volatile bool 		shootPressed;
volatile bool		userCollided;

void drawTitle();
void frameDelay();
void drawScene(char *topRow, char *bottomRow);
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

void disableButtons() {
	cbi(PCICR, PCIE0);
	cbi(PCICR, PCIE1);
}

bool* newGame() {
	// reset game elements
	status = 					1;
	speed = 					9; // FPS
	shipLoc = 					0x10;
	asteroidsTop = 				0;
	asteroidsBottom = 			0;
	userProjectilesTop = 		0;
	userProjectilesBottom = 	0;
	destroyedAsteroidsTop = 		0;
	destroyedAsteroidsBottom = 	0;
	movePressed = 				false;
	shootPressed = 				false;
	userCollided =				false;
	
	// show title screen
	playTrack(TITLE_TRACK);
	drawTitle();
	playTrack(START_SOUND);
	enableButtons();
	return &status;
}

void shoot();
void createAsteroids();

void renderFrame() {
	// create canvas for drawing
	char	topRow[SCREEN_WIDTH] = 		"                ";
	char	bottomRow[SCREEN_WIDTH] = 	"                ";
	
	// GAME LOGIC
	// move user
	if (movePressed) {
		tbi(shipLoc, 4); // move ship
		playTrack(CRASH_SOUND);
	}
	// move user projectiles
	userProjectilesTop = (userProjectilesTop >> 1);
	userProjectilesBottom = (userProjectilesBottom >> 1);
	// create new user projectiles
	if (shootPressed) {
		shoot();
	}
	// check for collisions
	
	// move asteroids and enemy projectiles
	
	// create new asteroids and enemy projectiles
	createAsteroids();
	
	// check for collisions
	
	// render scene
	drawScene(topRow, bottomRow);
	
	// draw frame
	lcdHome();
	lcdWriteString(topRow);
	lcdRowTwoHome();
	lcdWriteString(bottomRow);
	
	// play sounds
	
	// reset button pressed status
	movePressed = false;
	shootPressed = false;
	
	// time delay between frames
	frameDelay();
}

void drawTitle() {
	char *title = "   Astro-Text   ";
	lcdClear();
	lcdWrite(BLACK_SQUARE);
	u08 i;
	for (i = 0; i < SCREEN_WIDTH; i++) {
		_delay_ms(40);
		lcdDecrementCursor();
		lcdWrite(title[i]);
		lcdWrite(BLACK_SQUARE);
	}
	_delay_ms(670);	
	for (i = 0; i < (SCREEN_WIDTH + 1); i++) {
			lcdRowTwoHome();
			u08 j;
			for (j = 0; j < i; j++) {
				lcdWrite(' ');
			}
			lcdWriteString("=>");
			_delay_ms(40);
	}
	_delay_ms(1000);
}

void loopDraw(char *writeString, u16 boolValues, char character) {
	u08 i;
	for (i = 0; i < 16; i++) {
		if (boolValues & (1<<i)) {
			writeString[15-i] = character;
		}
	}
}

void drawScene(char *topRow, char *bottomRow) {
	// draw ship
	if ((shipLoc & 0x10) == 0x00) {
		// ship on top row
		topRow[0] = '=';
		topRow[1] = '>';
	} else {
		// ship on bottom row
		bottomRow[0] = '=';
		bottomRow[1] = '>';
	}
	
	// draw projectiles
	loopDraw(topRow, userProjectilesTop, '-');
	loopDraw(bottomRow, userProjectilesBottom, '-');
	
	// draw asteroids
	loopDraw(topRow, asteroidsTop, BLACK_SQUARE);
	loopDraw(bottomRow, asteroidsBottom, BLACK_SQUARE);
}

void createAsteroids() {
	// top row
	
	asteroidsTop |= 0;
	// bottom row
	
	asteroidsBottom |= 0;
}

void shoot() {
	if ( !((userProjectilesTop | userProjectilesBottom) & 0xF800) ) {
		if (!gbi(shipLoc, 4)) { // top row
			userProjectilesTop |= 0x2000;
		} else { // bottom row
			userProjectilesBottom |= 0x2000;
		}
		playTrack(LASER_SOUND);
	}
}

void frameDelay() {
	switch (speed) {
		case 3:
			_delay_ms(333);
			break;
		case 4:
			_delay_ms(250);
			break;
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
		case 11:
			_delay_ms(91);
			break;
		case 12:
			_delay_ms(83);
			break;
		case 13:
			_delay_ms(77);
			break;
		case 14:
			_delay_ms(71);
			break;
		case 15:
			_delay_ms(67);
			break;
		case 16:
			_delay_ms(63);
			break;
		case 17:
			_delay_ms(59);
			break;
		case 18:
			_delay_ms(56);
			break;
		case 19:
			_delay_ms(53);
			break;
		case 20:
			_delay_ms(50);
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

ISR(PCINT0_vect) { // move button pressed
	_delay_ms(2);
	if (gbi(PINB, PINB4) && !movePressed) {
		movePressed = true;
	}
}

ISR(PCINT1_vect) { // shoot button pressed
	_delay_ms(2);
	if (gbi(PINC, PINB0) && !shootPressed) {
		shootPressed = true;
	}
}