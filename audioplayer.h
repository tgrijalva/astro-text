#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#define AUDIO_OUT OCR2A

#define TITLE_TRACK 3
#define START_SOUND 4
#define LASER_SOUND 5

void audioSetup(); // call during setup
void playTrack(u08 trackNum);

#endif //ifndef AUDIOPLAYER_H