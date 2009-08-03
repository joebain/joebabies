#ifndef AUDIOMIXER_H_
#define AUDIOMIXER_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "AudioFile.h"

#include <string>

using namespace std;

class AudioMixer 
{
public:
  AudioMixer();
  ~AudioMixer();
  
  AudioFile* new_audio_file(string name, bool is_music);

private:
  int audio_rate;
  Uint16 audio_format;
  int audio_channels;
  int audio_buffers;
};


#endif // AUDIOMIXER_H_
