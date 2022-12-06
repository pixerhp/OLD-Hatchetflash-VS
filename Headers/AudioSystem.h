//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   AudioSystem.h file description:
* Declare a class that acts as a Audio Listener (kinda like a microphone).
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include "glm/glm.hpp"

// Declare a class that acts as a Audio Listener (kinda like a microphone).
class AudioSystem {
public:
	ALCdevice *device;
	ALCcontext *context;

	AudioSystem();
	~AudioSystem();

	void setListenerPos(glm::vec3 pos);
	void setListenerGain(float gain);
	void setListenerVel(glm::vec3 vel);
	void setListenerDir(glm::vec3 front);
};

// (Used in "AudioSystem.cpp" for throwing a pretty recognizable error for when/if the audio device can't be initialized.)
class AudioInitException{};

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 