#ifndef LCDLIB_H
#define LCDLIB_H

#define CTLREG PORTB
#define RS PORTB0
#define RW PORTB1
#define EN PORTB2

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
#define INFINITY_    0xF3
#define OMEGA        0xF4
#define BIG_SIGMA    0xF6
#define PI_SYMBOL    0xF7
#define X_BAR        0xF8
#define DIVISION     0xFD
#define BLACK_SQUARE 0xFF

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
void lcdIncrementCursor();
void lcdDecrementCursor();
void lcdSetCursor(u08 loc); // use MSB to denote row and bits 4 ~ 0 to denote col

#endif //ifndef LCDLIB_H