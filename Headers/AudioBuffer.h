#pragma once
#include <AL/al.h>
#include <AL/alc.h>

class AudioBuffer {
public:
    ALuint buffer;
    
	AudioBuffer(const char *path);
	~AudioBuffer();
};