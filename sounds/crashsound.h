#ifndef CRASHSOUND_H
#define CRASHSOUND_H

#include <avr/pgmspace.h>

u16 getCrashSoundLength();
u08 getCrashSoundSample(u16 n);

#endif //ifndef CRASHSOUND_H