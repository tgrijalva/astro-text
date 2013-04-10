/*! @file
    Global defines.
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <avr/io.h>          //I/O definitions (port/pin names, register names, named register bits, etc.)
#include <avr/interrupt.h>   //interrupt support
#include <stdint.h>

//! CPU speed (10MHz) for timer and delay loop calculations.
#define F_CPU 16000000UL
#include <util/delay.h>


//Define new datatypes as easier shorthand
typedef uint8_t		u08; //!< Unsigned 8-bit integer, range: 0 to +255
typedef int8_t		s08; //!< Signed 8-bit integer, range: -128 to +127
typedef uint16_t	u16; //!< Unsigned 16-bit integer, range: 0 to +65,535
typedef int16_t		s16; //!< Signed 16-bit integer, range: -32,768 to +32,767
typedef uint32_t	u32; //!< Unsigned 32-bit integer, range: 0 to +4,294,967,295

//Bit manipulation macros
#define sbi(a, b) ((a) |= 1 << (b))       //!< Sets bit b in variable a.
#define cbi(a, b) ((a) &= ~(1 << (b)))    //!< Clears bit b in variable a.
#define tbi(a, b) ((a) ^= 1 << (b))       //!< Toggles bit b in variable a.
#define gbi(a, b) ((a) & (1 << (b)))      //!< Gets bit b in variable a (masks out everything else).

// user-defined includes

#endif //ifndef GLOBALS_H