#include "AudioFile.h"
  
AudioFile::AudioFile(string name, void *file, bool is_music) {
  this->name = name;
  this->file = file;
  this->is_music = is_music;
  mute = false;
}

AudioFile::~AudioFile()
{
  if (is_music) {
    Mix_HaltMusic();
    Mix_FreeMusic((Mix_Music*) file);
  } else {
    if (Mix_Playing(channel))
      Mix_HaltChannel(channel);
    Mix_FreeChunk((Mix_Chunk*) file);
  }
}

//pretty sure this doesnt work, copying the music data is suspect at least
//not used atm anyhow
AudioFile::AudioFile(const AudioFile& audiofile)
{
	name = audiofile.name;
	is_music = audiofile.is_music;
	channel = audiofile.channel;
	mute = audiofile.mute;
	
	if (is_music) {
		file = audiofile.file;
	} else {
		Mix_Chunk * newMixChunk = new Mix_Chunk;
		// copy s's chunk data into new chunk
		newMixChunk->allocated = ((Mix_Chunk*)audiofile.file)->allocated;
		newMixChunk->alen = ((Mix_Chunk*)audiofile.file)->alen;
		newMixChunk->volume = ((Mix_Chunk*)audiofile.file)->volume;
		// create a sample buffer for the new sound
		newMixChunk->abuf = new Uint8[newMixChunk->alen];
		// copy sound data
		memcpy(newMixChunk->abuf, ((Mix_Chunk*)audiofile.file)->abuf, newMixChunk->alen);
		file = (void*) newMixChunk;
	}
	

}

void
AudioFile::play() {
	if (mute) return;
  if (is_music) {
    if(Mix_PlayMusic((Mix_Music*) file, 0) == -1) 
    {
	    printf("Unable to play Ogg file: %s\n", Mix_GetError());
    }
  } else {
   channel = Mix_PlayChannel(-1, (Mix_Chunk*) file, 0);
   if(channel == -1) {
	   fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
   } else {
     is_playing = true;
   }
  }
}

void
AudioFile::play_loop(int times) {
	if (mute) return;
  if (times >= -1) {
    if (is_music) {
      if(Mix_PlayMusic((Mix_Music*) file, times) == -1) 
      { 
	      printf("Unable to play Ogg file: %s\n", Mix_GetError());
      } 
    } else {
      channel = Mix_PlayChannel(-1, (Mix_Chunk*) file, times);
      if(channel == -1) {
	     fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
      } else {
        is_playing = true;
      }
    }
  } else {
    printf("Invalid number of loop times given: %d\n", times);
  }
}

void
AudioFile::stop()
{
  if (is_music) {
    Mix_HaltMusic();
  } else {
    if (is_playing) {
      is_playing = false;
      if (Mix_Playing(channel))
        Mix_HaltChannel(channel);
    }
  }
}
