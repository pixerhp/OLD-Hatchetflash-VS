/* AudioSource.h file description:
*
*/

#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include "glm/glm.hpp"

class AudioSource {
public:
    ALuint source;
    
	AudioSource(glm::vec3 pos = glm::vec3(0.0f), int pitch = 1, int gain = 1);
	~AudioSource();

    bool isPlaying();
    bool isLooping();
    void queueBuffer(ALuint buffer);
    void setPitch(float newPitch);
    void setGain(float newGain);
    void setPos(glm::vec3 pos);
    void setVel(glm::vec3 vel);
    void setOffset(float offset);
    void play();
    void pause();
};