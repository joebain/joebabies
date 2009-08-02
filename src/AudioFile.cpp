#include "AudioFile.h"
  
AudioFile::AudioFile(string name, void *file, bool is_music) {
  this->name = name;
  this->file = file;
  this->is_music = is_music;
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

void
AudioFile::play() {
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
