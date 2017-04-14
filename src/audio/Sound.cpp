#include "Sound.h"
#include <cassert>
#include <iostream>


Sound::Sound():
	mpAudioData(NULL),
	mAudioLength(0),
	mAllocBySDLWAV(false),
	mGroup(SOUND_GROUP_NONE)
{
}

Sound::~Sound()
{
	if (mpAudioData != NULL)
	{
		if (mAllocBySDLWAV)
			SDL_FreeWAV(mpAudioData);
		else
			delete [] mpAudioData;
	}
}

// Load a WAV sound file from file.
Sound* Sound::loadWAV(const std::string& fileName, const AudioFormat& desiredFormat, bool shouldConvert)
{
	SDL_AudioSpec audioSpec;
	Uint8*        pAudioData;
	Uint32        audioLength;

	// Load the WAV file.
	if (SDL_LoadWAV(fileName.c_str(), &audioSpec, &pAudioData, &audioLength) == NULL)
	{
		std::cerr << "Error: unable to load WAV file " << fileName << std::endl;
		return NULL;
	}

	// Create the sound object.
	Sound* pSound = new Sound();
	pSound->mAudioLength	= audioLength;
	pSound->mpAudioData		= pAudioData;
	pSound->mSampleFormat	= audioSpec.format;
	pSound->mNumChannels	= (int) audioSpec.channels;
	pSound->mFrequency		= audioSpec.freq;
	pSound->mAllocBySDLWAV	= true;

	// Convert the sound to the desired format if necessary.
	SDL_AudioCVT cvt;
	int cvtReturn = SDL_BuildAudioCVT(&cvt,
		audioSpec.format, audioSpec.channels, audioSpec.freq,
		desiredFormat.sampleFormat, desiredFormat.channels, desiredFormat.frequency);
	
	// * Was there was an error in the conversion setup?
	if (cvtReturn < 0)
	{
		std::cerr << "Error unable to convert WAV file " << fileName << " to the correct format: " << SDL_GetError() << std::endl;
		delete pSound;
		return NULL;
	}

	// * Is the sound already in the correct format?
	if (cvtReturn == 0)
		return pSound;
	
	// * Otherwise, the sound needs to be converted.
	
	if (!shouldConvert)
	{
		// There needs to be conversion but 'shouldConvert' is false!
		std::cerr << "Error: the WAV file " << fileName << " is not in the correct audio format" << std::endl;
		delete pSound;
		return NULL;
	}

	cvt.len = audioLength;
	cvt.buf = new unsigned char[cvt.len * cvt.len_mult];
	SDL_memcpy(cvt.buf, pAudioData, audioLength);
	SDL_ConvertAudio(&cvt);
	SDL_FreeWAV(pAudioData);
	pSound->mpAudioData		= cvt.buf;
	pSound->mAudioLength	= (unsigned int) (cvt.len * cvt.len_ratio);
	pSound->mNumChannels	= desiredFormat.channels;
	pSound->mFrequency		= desiredFormat.frequency;
	pSound->mAllocBySDLWAV	= false;
	return pSound;
}

