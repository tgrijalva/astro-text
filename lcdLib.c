#include "globals.h"
#include "lcdLib.h"

#define RIGHT_ARROW  0x7E
#define LEFT_ARROW   0x7F
#define START_FRAME  0xA2
#define END_FRAME    0xA3
#define SEPARATOR    0xA5
#define EMPTY_BOX    0xDB
#define ALPHA        0xE0
#define BETA         0xE2
#define EPSILON      0xE3
#define MU           0xE4
#define SMALL_SIGMA  0xE5
#define RHO          0xE6
#define SQRT_SYMBOL  0xE8
#define CENT_SYMBOL  0xEC
#define THETA        0xF2
#define _INFINITY     0xF3
#define OMEGA        0xF4
#define BIG_SIGMA    0xF6
#define PI_SYMBOL    0xF7
#define X_BAR        0xF8
#define DIVISION     0xFD
#define BLACK_SQUARE 0xFF

u08 getCharCode(char c);

void lcdInit() {
	_delay_ms(50);
	lcdCmd(0x3F); // function set
	_delay_us(100);
	lcdCmd(0x0F); // display on/off
	_delay_us(100);
	lcdCmd(0x01);
	_delay_us(3300);
	lcdCmd(0x06);
}

void lcdInitWithParams() {
	_delay_ms(50);
	
}

void lcdWrite(u08 c) {
	// clear control signals
	sbi(CTLREG, RS);
	CTLREG &= 0x09;
	// set enable
	sbi(CTLREG, EN);
	PORTD = c;
	_delay_us(1);
	cbi(CTLREG, EN);
	cbi(CTLREG, RS);
	_delay_us(50);
}

void lcdWriteString(char *str) {
	char *ptr = str;
	while(*ptr != 0) {
		lcdWrite(*ptr++);	
	}
}

void lcdCmd(u08 c) {
	// clear control signals
	// dont effect PB3
	CTLREG &= 0x08;
	// turn on enable
	sbi(CTLREG, EN);
	PORTD = c;
	_delay_us(1);
	// clear control signals
	// dont effect PB3
	cbi(CTLREG, EN);
	_delay_us(100);
}

void lcdClear() {
	lcdCmd(0x01);
	_delay_us(3300);
}

void lcdHome() {
	lcdCmd(0x02);
}

void lcdRowTwoHome() {
	lcdCmd(0xC0);
}

void lcdSetCursor(u08 loc) {
	
}