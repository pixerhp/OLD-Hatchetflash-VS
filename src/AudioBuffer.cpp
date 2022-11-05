#include "AudioBuffer.h"
#include <AL/al.h>
#include <AL/alc.h>
#include "AudioFile/AudioFile.h"

static inline ALenum to_al_format(short channels, short samples)
{
	bool stereo = (channels > 1);

	switch (samples) {
	case 16:
		if (stereo)
			return AL_FORMAT_STEREO16;
		else
			return AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			return AL_FORMAT_STEREO8;
		else
			return AL_FORMAT_MONO8;
	default:
		return -1;
	}
}

void loadAudio(ALuint buffer, const char *path) {
    AudioFile<double> audioFile;
    audioFile.load(path);

    std::vector<uint8_t> bufferData;
    audioFile.savePCMToBuffer(bufferData);
    alBufferData(buffer, to_al_format(audioFile.getNumChannels(), audioFile.getBitDepth()), bufferData.data(), bufferData.size(), audioFile.getSampleRate());
}

AudioBuffer::AudioBuffer(const char *path) {
    alGenBuffers(1, &buffer);
    loadAudio(buffer, path);
}

AudioBuffer::~AudioBuffer() {
    alDeleteBuffers(1, &buffer);
}