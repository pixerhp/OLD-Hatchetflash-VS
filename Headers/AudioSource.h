/* AudioSource.h file description:
*   Declare a class that plays audio.
*/

#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include "glm/glm.hpp"

// Declare a class that plays audio.
class AudioSource {
public:
    // The internal ID of this AudioSource.
    ALuint source;
    
    // The constructor takes in an initial position, pitch, and gain.
	AudioSource(glm::vec3 pos = glm::vec3(0.0f), int pitch = 1, int gain = 1);
	~AudioSource();

    bool isPlaying();
    bool isLooping();
    // Add a sound to the sound queue.
    void queueBuffer(ALuint buffer);
    void setPitch(float newPitch);
    void setGain(float newGain);
    void setPos(glm::vec3 pos);
    void setVel(glm::vec3 vel);
    void setOffset(float offset);
    void play();
    void pause();
};
