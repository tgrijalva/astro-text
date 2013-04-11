#include "globals.h"
#include "audioplayer.h"

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
}

void nextAudioSample() {
	
}

// audio player interrupt
ISR(TIMER1_COMPA_vect) {
	nextAudioSample();
}