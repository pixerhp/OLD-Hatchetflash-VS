//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   AudioSource.cpp file description:
* Define methods for a class that plays audio.
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "AudioSource.h"
#include <AL/al.h>
#include <AL/alc.h>
#include "glm/glm.hpp"


// The constructor takes in an initial position, pitch, and gain.
AudioSource::AudioSource(glm::vec3 pos, int pitch, int gain) {
    alGenSources((ALuint)1, &source);
    alSourcef(source, AL_PITCH, pitch);
	alSourcef(source, AL_GAIN, gain);
	alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
}

AudioSource::~AudioSource() {
    alDeleteSources(1, &source);
}

bool AudioSource::isPlaying() {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

bool AudioSource::isLooping() {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_LOOPING;
}

// Add a sound to the sound queue.
void AudioSource::queueBuffer(ALuint buffer) {
    alSourceQueueBuffers(source, 1, &buffer);
}

void AudioSource::setPitch(float newPitch) {
    alSourcef(source, AL_PITCH, newPitch);
}

void AudioSource::setGain(float newGain) {
    alSourcef(source, AL_GAIN, newGain);
}

void AudioSource::setPos(glm::vec3 pos) {
    alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
}
        
void AudioSource::setVel(glm::vec3 vel) {
    alSource3f(source, AL_VELOCITY, vel.x, vel.y, vel.z);
}

void AudioSource::setOffset(float offset) {
    alSourcef(source, AL_SEC_OFFSET, offset);
}

void AudioSource::play() {
    alSourcePlay(source);
}

void AudioSource::pause() {
    alSourcePause(source);
}

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 