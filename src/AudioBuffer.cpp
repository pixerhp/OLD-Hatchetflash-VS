//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   AudioBuffer.cpp file description:
* Define a methods for a class that stores audio data.
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#include "AudioBuffer.h"
#include <AL/al.h>
#include <AL/alc.h>
#define DR_WAV_IMPLEMENTATION
#include "dr_wav/dr_wav.h"

// Load audio from a file.
void loadAudio(ALuint buffer, const char *path) {
	unsigned int channels = 0;
	unsigned int sampleRate = 0;
	drwav_uint64 totalFrameCount = 0;
	drwav_int16 *data = drwav_open_file_and_read_pcm_frames_s16(path, &channels, &sampleRate, &totalFrameCount, NULL);

	//Note: currently doesn't handle audio with > 2 channels.
	//The *channels*2 is because openal expects total byte count,
	// while dr_wav provides frame count
	// (1 frame = 1 sample per channel, 1 sample = 16 bits / 8 bits per byte = 2 bytes)
	alBufferData(buffer, channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, data, totalFrameCount*channels*2, sampleRate);
	drwav_free(data, NULL);
}

// Constructor takes in path to audio file.
AudioBuffer::AudioBuffer(const char *path) {
    alGenBuffers(1, &buffer);
    loadAudio(buffer, path);
}

AudioBuffer::~AudioBuffer() {
    alDeleteBuffers(1, &buffer);
}

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 