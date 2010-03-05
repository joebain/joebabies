#include "AudioMixer.h"

#include <iostream>

AudioMixer::AudioMixer()
{
  // Here's your playback options
  audio_rate = 44100;
  audio_format = AUDIO_S16SYS;
  audio_channels = 2;
  audio_buffers = 4096;
  
  //default to music and sfx on
  music_on = true;
  sfx_on = true;
  
  // Set up the mixer
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
	  fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
	  no_audio = true;
	  exit(1);
  } else {
	  no_audio = false;
  }
}

AudioMixer::~AudioMixer()
{
  Mix_HaltMusic();
  Mix_HaltChannel(-1); // this means stop them all
  Mix_CloseAudio();
}

AudioFile*
AudioMixer::new_audio_file(string name, bool is_music)
{
	if (no_audio) return NULL;
  string filename;
  void *audio;
  // Check if this audio file is a music file or not
  if (is_music) {
    // Load a music file...
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
  AudioFile* audiofile = new AudioFile(name, audio, is_music);
  
  if ((is_music && !music_on) || (!is_music && !sfx_on)) audiofile->toggle_mute();
  
  audio_files.push_back(audiofile);
  return audio_files.back();
}

void AudioMixer::fade_out_all()
{
	cout << "fading out" << endl;
	Mix_FadeOutChannel(-1, 500);
	Mix_FadeOutMusic(500);
	
	sfx_on = false;
	music_on = false;
	
	list<AudioFile*>::iterator iter;
	for (iter = audio_files.begin() ; iter != audio_files.end() ; iter++) {
		(*iter)->toggle_mute();
	}
}

//~ void AudioMixer::fade_in_all()
//~ {
	//~ cout << "fading in" << endl;
	//~ Mix_FadeInChannel(-1, 500);
	//~ Mix_FadeInMusic(500);
//~ }
