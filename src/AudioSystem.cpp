//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   AudioSystem.cpp file description:
* Define functions for a class that acts as a Audio Listener (kinda like a microphone).
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "AudioSystem.h"


AudioSystem::AudioSystem() {
	device = alcOpenDevice(alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER));
	if (!device) {
		throw(new AudioInitException);
	}

	context = alcCreateContext(device, nullptr);      
    alcMakeContextCurrent(context);            
    alGetError();

    ALCenum error;
    error = alGetError();
	if (error != AL_NO_ERROR) {
		throw(new AudioInitException);
    }

	alSpeedOfSound(343.3f);
}

AudioSystem::~AudioSystem() {
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
    alcCloseDevice(device);
}

void AudioSystem::setListenerPos(glm::vec3 pos) {
    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
}

void AudioSystem::setListenerGain(float gain) {
    alListenerf(AL_GAIN, gain);
}

void AudioSystem::setListenerVel(glm::vec3 vel) {
    alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z);
}

void AudioSystem::setListenerDir(glm::vec3 front) {
    ALfloat ori[] = {front.x, front.y, front.z, 0.0f, 1.0f, 0.0f};
    alListenerfv(AL_ORIENTATION, ori);
}

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 