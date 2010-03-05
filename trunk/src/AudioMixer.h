#ifndef AUDIOMIXER_H_
#define AUDIOMIXER_H_

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "AudioFile.h"

#include <string>
#include <list>

using namespace std;

class AudioMixer 
{
public:
	AudioMixer();
	~AudioMixer();

	AudioFile* new_audio_file(string name, bool is_music);
	AudioFile* new_music(string name) {return new_audio_file(name,true);}
	AudioFile* new_sound_effect(string name) {return new_audio_file(name,false);}
	void fade_out_all();

private:
	list<AudioFile*> audio_files;
	
	int audio_rate;
	Uint16 audio_format;
	int audio_channels;
	int audio_buffers;

	int volume;
	bool music_on;
	bool sfx_on;
	bool no_audio;
};


#endif // AUDIOMIXER_H_
