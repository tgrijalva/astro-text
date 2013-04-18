#ifndef FAILSOUND_H
#define FAILSOUND_H

#include <avr/pgmspace.h>

u16 getFailSoundLength();
u08 getFailSoundSample(u16 n);

#endif //ifndef FAILSOUND_H