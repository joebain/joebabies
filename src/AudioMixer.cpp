#include "AudioMixer.h"

#include "SDL.h"
#include "SDL_mixer.h"

AudioMixer::AudioMixer()
{
  // Here's your playback options
  audio_rate = 44100;
  audio_format = AUDIO_S16SYS;
  audio_channels = 2;
  audio_buffers = 4096;
  
  // Set up the mixer
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
	  fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
	  exit(1);
  }
}

AudioMixer::~AudioMixer()
{
  Mix_HaltMusic();
  Mix_HaltChannel(-1);
  Mix_CloseAudio();
}

AudioFile*
AudioMixer::new_audio_file(string name, bool is_music)
{
  string filename;
  void *audio;
  if (is_music) {
    string filename = "audio/" + name + ".ogg";
    audio = (void*) Mix_LoadMUS(filename.c_str());
    if(audio == NULL) 
    {
	    printf("Unable to load Ogg file: %s\n", Mix_GetError());
	    exit(1);
    }
  } else {
    // Load a sound file...
    string filename = "audio/" + name + ".wav";
    audio = (void*) Mix_LoadWAV(filename.c_str());
    if(audio == NULL) 
    {
	    printf("Unable to load Wav file: %s\n", Mix_GetError());
	    exit(1);
    }
  }
  AudioFile *audiofile = new AudioFile(name, audio, is_music);
  return audiofile;
  
}
