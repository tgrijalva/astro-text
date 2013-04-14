#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#define AUDIO_OUT OCR2A

void audioSetup(); // call during setup
void playTrack(u08 trackNum);

#endif //ifndef AUDIOPLAYER_H