#ifndef AUDIOFILE_H_
#define AUDIOFILE_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <string>

using namespace std;

class AudioFile {
public:
  AudioFile(string name, void *file, bool is_music);
  ~AudioFile();
  
  AudioFile(const AudioFile& audiofile);
  
  void play();
  void play_loop(int times);
  void stop();
  void toggle_mute() {mute = !mute;}
  
private:
  void *file; // May be Mix_Music, or Mix_Chunk
  string name;
  bool is_music;
  bool is_playing;
  int channel;
  bool mute;
};

#endif
