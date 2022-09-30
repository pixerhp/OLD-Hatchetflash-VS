#pragma once
#include <irrklang/irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

class Audio {
public:
	irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
	void playMusic(const char* nameOfSong);
	void stopMusic();
};