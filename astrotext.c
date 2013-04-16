#include "globals.h"
#include "astrotext.h"
#include "lcdLib.h"
#include "audioplayer.h"

#define DEFAULT_GAME_SPEED 	9 				// FPS
#define POWERUP_TIME_1 		25

bool				status; 				// status != 0 is active, status = 0 is inactive
volatile u08		speed;					// FPS
volatile u08		shipLoc; 				// location of ships tail
volatile u16		asteroidsTop;			// bits denote asteroid locations, 1 for asteroid, 0 for no asteroid
volatile u16		asteroidsBottom;
volatile u16		destroyedAsteroidsTop;
volatile u16		destroyedAsteroidsBottom;
volatile u16		userProjectilesTop;
volatile u16		userProjectilesBottom;
volatile u16		powerUpsTop;
volatile bool 		movePressed;
volatile bool 		shootPressed;
volatile bool		userCollided;
volatile bool		powerUp;
volatile u08		powerUpTimer;
volatile u08		shootTimer;
volatile u16		score;

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
	status = 					true;
	speed = 					DEFAULT_GAME_SPEED;
	shipLoc = 					0x10;
	asteroidsTop = 				0;
	asteroidsBottom = 			0;
	userProjectilesTop = 		0;
	userProjectilesBottom = 	0;
	destroyedAsteroidsTop = 	0;
	destroyedAsteroidsBottom = 	0;
	powerUpTimer = 				0;
	powerUpsTop = 				0;
	shootTimer = 				0;
	score =						0;
	movePressed = 				false;
	shootPressed = 				false;
	userCollided =				false;
	powerUp = 					false;
	
	// show title screen
	playTrack(TITLE_TRACK);
	drawTitle();
	playTrack(START_SOUND);
	enableButtons();
	return &status;
}

void shoot();
void createAsteroids();
void checkAsteroidCollisions();
void checkShipCollisions();
void printScore();

void renderFrame() {
	// create canvas for drawing
	char	topRow[SCREEN_WIDTH] = 		"                ";
	char	bottomRow[SCREEN_WIDTH] = 	"                ";
	
	// GAME LOGIC
	// move user
	if (movePressed) {
		tbi(shipLoc, 4); // move ship
	}
	
	// move user projectiles
	userProjectilesTop = (userProjectilesTop >> 1);
	userProjectilesBottom = (userProjectilesBottom >> 1);
	
	// create new user projectiles
	if (shootPressed) {
		if (!shootTimer) {
			shoot();
			shootTimer = 3;
		}
	}
	if (powerUp) {
		shoot();
		powerUp--;
	}
	
	// check for Asteroid collisions
	checkAsteroidCollisions();
	
	// move asteroids and enemy projectiles
	powerUpsTop = (powerUpsTop << 1);
	asteroidsTop = (asteroidsTop << 1);
	asteroidsBottom = (asteroidsBottom << 1);
	destroyedAsteroidsTop = (destroyedAsteroidsTop << 1);
	destroyedAsteroidsBottom = (destroyedAsteroidsBottom << 1);
	
	// create new asteroids and enemy projectiles
	createAsteroids();
	
	// check for collisions
	checkAsteroidCollisions();
	checkShipCollisions();
	
	// check for powerUp
	if ((powerUpsTop & 0xC000) && !(shipLoc & 0x10)) {
		powerUp = 50;
	}
	
	// render scene
	drawScene(topRow, bottomRow);
	
	// draw frame
	lcdHome();
	lcdWriteString(topRow);
	lcdRowTwoHome();
	lcdWriteString(bottomRow);
	
	// act on collisions
	if (userCollided) {
		disableButtons();
		status = false;
		playTrack(CRASH_SOUND);
		_delay_ms(2500);
		lcdSetCursor(0x05);
		lcdWriteString("FAIL!!");
		playTrack(FAIL_SOUND);
		_delay_ms(2000);
		lcdSetCursor(0x12);
		lcdWriteString("SCORE:0");
		printScore();
		_delay_ms(3000);
		return;
	} else if (destroyedAsteroidsTop | destroyedAsteroidsBottom) {
		playTrack(HIT_SOUND);
	}
	// clear destroyed asteroids
	destroyedAsteroidsTop = 0;
	destroyedAsteroidsBottom = 0;
	
	// reset button pressed status
	movePressed = false;
	shootPressed = false;
	
	// increment timers
	score++;
	powerUpTimer++;
	if (shootTimer) {
		shootTimer--;
	}
	
	// increase game speed if score is high enough
	if (score > 50) {
		speed = DEFAULT_GAME_SPEED + 1;
	} else if (score > 100) {
		speed = DEFAULT_GAME_SPEED + 2;
	} else if (score > 150) {
		speed = DEFAULT_GAME_SPEED + 3;
	} else if (score > 200) {
		speed = DEFAULT_GAME_SPEED + 4;
	} else if (score > 250) {
		speed = DEFAULT_GAME_SPEED + 5;
	} else if (score > 300) {
		speed = DEFAULT_GAME_SPEED + 6;
	} else if (score > 350) {
		speed = DEFAULT_GAME_SPEED + 7;
	} else if (score > 400) {
		speed = DEFAULT_GAME_SPEED + 8;
	} else if (score > 450) {
		speed = DEFAULT_GAME_SPEED + 9;
	} else if (score > 500) {
		speed = DEFAULT_GAME_SPEED + 10;
	} else if (score > 550) {
		speed = DEFAULT_GAME_SPEED + 11;
	} else if (score > 600) {
		speed = DEFAULT_GAME_SPEED + 12;
	}

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
	
	// draw user projectiles
	loopDraw(topRow, userProjectilesTop, '-');
	loopDraw(bottomRow, userProjectilesBottom, '-');
	
	// draw asteroids
	loopDraw(topRow, asteroidsTop, BLACK_SQUARE);
	loopDraw(bottomRow, asteroidsBottom, BLACK_SQUARE);
	
	// draw collided asteroids
	loopDraw(topRow, destroyedAsteroidsTop, 'X');
	loopDraw(bottomRow, destroyedAsteroidsBottom, 'X');
	
	// draw powerUps
	if (powerUpsTop) {
		loopDraw(topRow, powerUpsTop, '+');
	}
}

u08 countBits(u16 bools) {
	u08 count = 0;
	u08 i;
	for (i = 0; i < 16; i++) {
		if ((bools >> i) & 0x0001) {
			count++;
		}
	}
	return count;
}

void createAsteroids() {
	if (powerUpTimer == POWERUP_TIME_1) {
		powerUpsTop |= 1;
	} else if (!((asteroidsTop | asteroidsBottom) & 0x0007)) {
		if ((powerUpTimer == POWERUP_TIME_1 + 1) || (powerUpTimer == POWERUP_TIME_1 + 2) || (powerUpTimer == POWERUP_TIME_1 + 3)) {
			// dont place asteroid directly behind powerup
				asteroidsBottom |= 1;
		}
		
		u08 topCount = countBits(asteroidsTop);
		u08 bottomCount = countBits(asteroidsBottom);
		// pattern chooser
		u16 asteroidLogicBool = (asteroidsTop | asteroidsBottom) ^ (userProjectilesTop | userProjectilesBottom);
		if (!asteroidLogicBool) {
			asteroidsBottom |= 1;
		} else if (gbi(asteroidLogicBool, 13)) {
			asteroidsTop |= 1;
			asteroidsBottom |= 1;
		} else if (topCount < bottomCount) {
			asteroidsTop |= 1;
		} else if (topCount > bottomCount) {
			asteroidsBottom |= 1;
		} else {
			asteroidsTop |= 1;
		}
	}
}

void shoot() {
	if (!gbi(shipLoc, 4)) { // top row
		userProjectilesTop |= 0x2000;
	} else { // bottom row
		userProjectilesBottom |= 0x2000;
	}
	playTrack(LASER_SOUND);
}

void checkShipCollisions() {
	// check user asteroid collision
	if (shipLoc & 0x10) {	// ship on bottom
		if ( (asteroidsBottom | destroyedAsteroidsBottom) & 0xC000) {
			userCollided = true;
		}
	} else { 				// ship on top
		if ( (asteroidsTop | destroyedAsteroidsTop) & 0xC000) {
			userCollided = true;
		}
	}
}

void checkAsteroidCollisions() {
	// check for laser asteroid collisions
	u16 collideBoolTop = userProjectilesTop & asteroidsTop;
	u16 collideBoolBottom = userProjectilesBottom & asteroidsBottom;
	score += countBits(collideBoolTop);
	score += countBits(collideBoolBottom);
	// destroy asteroids
	destroyedAsteroidsTop |= collideBoolTop;
	destroyedAsteroidsBottom |= collideBoolBottom;
	// remove live asteroids
	asteroidsTop &= ~collideBoolTop;
	asteroidsBottom &= ~collideBoolBottom;
	// remove collided lasers
	userProjectilesTop &= ~collideBoolTop;
	userProjectilesBottom &= ~collideBoolBottom;
}

void printScore() {
	lcdWrite((score / 10000) + 48);
	score %= 10000;
	lcdWrite((score / 1000) + 48);
	score %= 1000;
	lcdWrite((score / 100) + 48);
	score %= 100;
	lcdWrite((score / 10) + 48);
	score %= 10;
	lcdWrite(score + 48);
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
			_delay_ms(1);
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