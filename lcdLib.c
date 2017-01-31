#include "globals.h"
#include "lcdLib.h"

void lcdInit() {
	// Configure data direction
	DATAREG = 0xFF;
	sbi(CTLREG, RS);
	sbi(CTLREG, RW);
	sbi(CTLREG, EN);
	
	_delay_ms(50);
	lcdCmd(0x3F); // function set
	_delay_us(100);
	lcdCmd(0x0F); // display on/off
	_delay_us(100);
	lcdCmd(0x01);
	_delay_us(3300);
	lcdCmd(0x06);
}

void _clearControlSignals() {
	u08 sigs = (1 << RS) | (1 << RW) | (1 << EN);
	CTLPORT &= ~sigs;
}

void lcdWrite(u08 chr) {
	_clearControlSignals();
	
	sbi(CTLPORT, RS);
	sbi(CTLPORT, EN);
	DATAPORT = chr;
	_delay_us(1);
	cbi(CTLPORT, EN);
	cbi(CTLPORT, RS);
	_delay_us(50);
}

void lcdWriteString(char *str) {
	while(*str != 0) {
		lcdWrite(*str++);	
	}
}

void lcdCmd(u08 cmd) {
	_clearControlSignals();
	
	// turn on enable
	sbi(CTLPORT, EN);
	DATAPORT = cmd;
	_delay_us(1);
	cbi(CTLPORT, EN);
	_delay_us(100);
}

void lcdClear() {
	lcdCmd(0x01);
	_delay_us(3300);
}

void lcdHome() {
	lcdCmd(0x80);
}

void lcdRowTwoHome() {
	lcdCmd(0xC0);
}

void lcdCursorStyle(bool on, bool blink) {
	u08 cmd = 0x0C;
	if (on) {
		cmd |= 0x02;
	}
	if (blink) {
		cmd |= 0x01;
	}
	lcdCmd(cmd);
}

void lcdIncrementCursor() {
	lcdCmd(0x14);
}

void lcdDecrementCursor() {
	lcdCmd(0x10);
}

void lcdShiftTextRight() {
	lcdCmd(0x1C);
}

void lcdShiftTextLeft() {
	lcdCmd(0x18);
}

void lcdSetCursor(u08 loc) {
	u08 cmd = 0x80;
	if (loc & 0x10) {	// add 0x40 for row 2
		cmd |= 0x40;
	}
	cmd += (0x0F & loc);
	lcdCmd(cmd);
}