#ifndef LCDLIB_H
#define LCDLIB_H

#define CTLREG PORTB
#define RS PORTB0
#define RW PORTB1
#define EN PORTB2

// init functions
void lcdInit();

// read/write functions
void lcdWrite(u08 c);
void lcdWriteString(char *str);
// void lcdRead(int &x);

// command functions
void lcdCmd(u08 c);
void lcdClear();
void lcdHome();
void lcdRowTwoHome();
void lcdCursorStyle(bool on, bool blink);
void lcdSetCursor(u08 loc); // use MSB to denote row and bits 4 ~ 0 to denote col

#endif //ifndef LCDLIB_H