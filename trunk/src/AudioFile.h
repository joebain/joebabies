#ifndef AUDIOFILE_H_
#define AUDIOFILE_H_

#include "SDL.h"
#include "SDL_mixer.h"

#include <string>

using namespace std;

class AudioFile {
public:
  AudioFile(string name, void *file, bool is_music);
  ~AudioFile();
  
  void play();
  void play_loop(int times);
  void stop();
  
private:
  void *file; // May be Mix_Music, or Mix_Chunk
  string name;
  bool is_music;
  bool is_playing;
  int channel;
};

#endif
