#include "Audio.h"

void Audio::playMusic(const char* SongName) {
	SoundEngine->play2D(SongName,true);
}

void Audio::stopMusic() {
	SoundEngine->removeAllSoundSources();
}