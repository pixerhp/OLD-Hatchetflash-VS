//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   AudioBuffer.h file description:
* Declare a class that stores audio data.
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include <AL/al.h>
#include <AL/alc.h>


// A class that stores audio data.
class AudioBuffer {
	public:
		// The internal ID of this audio buffer.
		ALuint buffer;
    
		// Constructor takes in path to audio file.
		AudioBuffer(const char *path);
		~AudioBuffer();
};

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 