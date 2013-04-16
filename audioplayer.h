#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#define AUDIO_OUT OCR2A

#define TITLE_TRACK 1
#define START_SOUND 2
#define LASER_SOUND 3
#define CRASH_SOUND 4
#define FAIL_SOUND  5

void audioSetup(); // call during setup
void playTrack(u08 trackNum);

#endif //ifndef AUDIOPLAYER_H