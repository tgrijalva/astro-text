#include "globals.h"
#include "audioplayer.h"
#include "./sounds/lasersound.h"
#include "./sounds/crashsound.h"
#include "./sounds/failsound.h"

#define NORMAL_VOLUME 40
#define LOUD_VOLUME 128
#define MAX_VOLUME 255

volatile u08 trackNumber = 0;
volatile u16 sampleCount = 0;
volatile u08 amplitude = 0;
volatile bool waveUp = true;
volatile u08 squareTimer = 0;

void audioSetup() {
	// setup pwm output for audio
	sbi(DDRB, DDB3);
	sbi(TCCR2A, COM2A1);
	sbi(TCCR2A, WGM21);
	sbi(TCCR2A, WGM20);
	sbi(TCCR2B, CS20);
	
	// setup timer for audio interrupt
	sbi(TCCR1B, WGM12);
	sbi(TCCR1B, CS11);
	OCR1A = 99;
	sbi(TIMSK1, OCIE1A);
	sei();
	
	AUDIO_OUT = 0; // make sure audio is off at start
}

void playTrack(u08 trackNum) {
	trackNumber = trackNum;
	sampleCount = 0;
}

void triWave(u08 stepSize) {
	if (waveUp) {
		if ( ((u16)amplitude) + ((u16)stepSize) > 255) {
			waveUp = false;
			amplitude -= stepSize;
		} else {
			amplitude += stepSize;
		}
	} else {
		if ( ((s16)amplitude) - ((s16)stepSize) < 0) {
			waveUp = true;
			amplitude += stepSize;
		} else {
			amplitude -= stepSize;
		}
	}
}

void volumeSquareWave(u08 dutySize, u08 volume) {
	if (waveUp) {
		amplitude = volume;
		if ( ((u16)squareTimer) + ((u16)dutySize) > 255) {
			waveUp = false;
			squareTimer -= dutySize;
		} else {
			squareTimer += dutySize;
		}
	} else {
		amplitude = 0;
		if ( ((s16)squareTimer) - ((s16)dutySize) < 0) {
			waveUp = true;
			squareTimer += dutySize;
		} else {
			squareTimer -= dutySize;
		}
	}
}

void squareWave(u08 dutySize) {
	if (waveUp) {
		amplitude = NORMAL_VOLUME;
		if ( ((u16)squareTimer) + ((u16)dutySize) > 255) {
			waveUp = false;
			squareTimer -= dutySize;
		} else {
			squareTimer += dutySize;
		}
	} else {
		amplitude = 0;
		if ( ((s16)squareTimer) - ((s16)dutySize) < 0) {
			waveUp = true;
			squareTimer += dutySize;
		} else {
			squareTimer -= dutySize;
		}
	}
}

void nextAudioSample() {
	sampleCount++;
	switch (trackNumber) {
			case TITLE_TRACK:
				if (sampleCount < 2500) {
					triWave(3);
				} else if (sampleCount < 5000) {
					triWave(4);
				} else if (sampleCount < 7500) {
					triWave(5);
				} else if (sampleCount < 10000) {
					squareWave(10);
				} else if (sampleCount < 12500) {
					squareWave(15);
				} else if (sampleCount < 15000) {
					triWave(20);
				} else if (sampleCount < 17500) {
					squareWave(25);
				} else if (sampleCount < 20000) {
					triWave(8);
				} else if (sampleCount < 22500) {
					squareWave(16);
				} else if (sampleCount < 25000) {
					squareWave(10);
				} else if (sampleCount < 27500) {
					triWave(5);
				} else if (sampleCount < 30000) {
					triWave(12);
				} else if (sampleCount < 32500) {
					triWave(7);
				} else if (sampleCount < 35000) {
					squareWave(4);
				} else if (sampleCount < 37500) {
					triWave(8);
				} else if (sampleCount < 40000) {
					squareWave(10);
				} else if (sampleCount < 42500) {
					squareWave(5);
				} else if (sampleCount < 45000) {
					triWave(20);
				} else if (sampleCount < 47500) {
					triWave(15);
				} else if (sampleCount < 50000) {
					triWave(10);
				} else if (sampleCount < 52500) {
					squareWave(5);
				} else if (sampleCount < 55000) {
					squareWave(4);
				} else if (sampleCount < 57500) {
					squareWave(2);
				} else if (sampleCount < 60000) {
					squareWave(1);
				} else {
					trackNumber = 0;
					sampleCount = 0;
				}
				break;
				
			case START_SOUND:
				if (sampleCount < 2500) {
					squareWave(1);
				} else {
					trackNumber = 0;
					sampleCount = 0;
				}
				break;
				
			case LASER_SOUND:
				if (sampleCount < getLaserSoundLength()) {
					amplitude = getLaserSoundSample(sampleCount);
				} else {
					trackNumber = 0;
					sampleCount = 0;
				}
				break;
				
			case CRASH_SOUND:
				if (sampleCount < getCrashSoundLength()) {
					amplitude = getCrashSoundSample(sampleCount);
				} else {
					trackNumber = 0;
					sampleCount = 0;
				}
				break;
				
			case FAIL_SOUND:
				if (sampleCount < getFailSoundLength()) {
					amplitude = getFailSoundSample(sampleCount);
				} else {
					trackNumber = 0;
					sampleCount = 0;
				}
				break;
			
			default:
				amplitude = 0;
	}
}

// audio player interrupt
ISR(TIMER1_COMPA_vect) {
	nextAudioSample();
	AUDIO_OUT = amplitude;
}