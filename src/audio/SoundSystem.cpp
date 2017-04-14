#include "SoundSystem.h"
#include <assert.h>
//#include "MathLib.h"
//#include "Services.h"
#include <iostream>


static unsigned int getMin(unsigned int a, unsigned int b)
{
	return (a < b ? a : b);
}

static float clampValue(float x, float minValue, float maxValue)
{
	if (x < minValue)
		return minValue;
	if (x > maxValue)
		return maxValue;
	return x;
}


SoundInstance::SoundInstance(const Sound* pSound, SoundLoopMode loopMode) :
	mAudioPosition(0),
	mpSound(pSound),
	mLoopMode(loopMode)
{
}

bool SoundInstance::isDone() const
{
	return (mLoopMode == SOUND_PLAY_ONCE && mAudioPosition >= mpSound->getAudioLength());
}

void SoundInstance::nextAudioChunk(int length, const Uint8** pAudioChunk, int* pChunkLength)
{
	assert(mAudioPosition < mpSound->getAudioLength());
	
	// Output the audio chunk info.
	*pAudioChunk  = (mpSound->getAudioData() + mAudioPosition);
	*pChunkLength = getMin(length, (int) mpSound->getAudioLength() - mAudioPosition);
	
	// Advance the audio position.
	mAudioPosition += (Uint32) length;
	if (mAudioPosition >= mpSound->getAudioLength() && mLoopMode == SOUND_PLAY_LOOP)
		mAudioPosition %= mpSound->getAudioLength();
}


//-----------------------------------------------------------------------------
// Constructor & destructor
//-----------------------------------------------------------------------------

SoundSystem::SoundSystem()
{
	mIsInitialized = false;
}

SoundSystem::~SoundSystem()
{
	cleanup();
}


//-----------------------------------------------------------------------------
// Control functions
//-----------------------------------------------------------------------------

bool SoundSystem::init()
{
	if (mIsInitialized)
		return false;
	
	mMasterVolume = 0.2f;

    // Set the desired audio device format.
	SDL_AudioSpec obtainedSpec;
    mSDLAudioDeviceSpec.freq		= 44100;		// Sample rate.
    mSDLAudioDeviceSpec.format		= AUDIO_S16;	// 2 bytes per sample (for a signed 16 bit value).
    mSDLAudioDeviceSpec.channels	= 2;			// 1 = mono, 2 = stereo.
    mSDLAudioDeviceSpec.samples		= 1024;			// Good low-latency value for callback.
    mSDLAudioDeviceSpec.callback	= fillAudioCallback;
    mSDLAudioDeviceSpec.userdata	= this;
	
	// Open an available audio device.
	mSDLAudioDeviceID = SDL_OpenAudioDevice(NULL, 0, &mSDLAudioDeviceSpec, &obtainedSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);
	if (mSDLAudioDeviceID == 0)
	{
		std::cerr << "Error opening an audio device: " << SDL_GetError() <<std::endl;
        return false;
	}

	// Read the obtained audio device format.
	mDeviceAudioFormat.sampleFormat = obtainedSpec.format;
	mDeviceAudioFormat.channels     = obtainedSpec.channels;
	mDeviceAudioFormat.frequency    = obtainedSpec.freq;

	// Begin the audio stream.
	SDL_PauseAudioDevice(mSDLAudioDeviceID, 0);

	// Enable all sound groups.
	for (int i = 0; i < NUM_SOUND_GROUPS; i++)
		mSoundGroupsEnabled[i] = true;

	mIsInitialized = true;
	return true;
}

void SoundSystem::cleanup()
{
	if (mIsInitialized)
	{
		SDL_CloseAudioDevice(mSDLAudioDeviceID);
		mIsInitialized = false;
	}
}


//-----------------------------------------------------------------------------
// Mutators
//-----------------------------------------------------------------------------

// Set the scalar volume for all sounds (0.0f to 1.0f).
void SoundSystem::setMasterVolume(float masterVolume)
{
	mMasterVolume = clampValue(masterVolume, 0.0f, 1.0f);
}


//-----------------------------------------------------------------------------
// Playback
//-----------------------------------------------------------------------------

//// Play a sound with the given name and loop mode.
//void SoundSystem::playSound(const std::string& soundName, SoundLoopMode loopMode)
//{
//	Sound* pSound = Services::getResources()->getSound(soundName);
//	if (pSound != NULL)
//		playSound(pSound, loopMode);
//}

// Play a sound with the given loop mode.
void SoundSystem::playSound(const Sound* pSound, SoundLoopMode loopMode)
{
	mSoundInstances.push_back(SoundInstance(pSound, loopMode));
}

//void SoundSystem::stopSound(const std::string& soundName)
//{
//	Sound* pSound = Services::getResources()->getSound(soundName);
//	if (pSound != NULL)
//		stopSound(pSound);
//}

void SoundSystem::stopSound(const Sound* pSound)
{
	for (unsigned int i = 0; i < mSoundInstances.size(); i++)
	{
		if (mSoundInstances[i].getSound() == pSound)
		{
			mSoundInstances.erase(mSoundInstances.begin() + i);
			i--;
		}
	}
}

//bool SoundSystem::isSoundPlaying(const std::string& soundName)
//{
//	Sound* pSound = Services::getResources()->getSound(soundName);
//	if (pSound != NULL)
//		return isSoundPlaying(pSound);
//	return false;
//}

bool SoundSystem::isSoundPlaying(const Sound* pSound)
{
	for (unsigned int i = 0; i < mSoundInstances.size(); i++)
	{
		if (mSoundInstances[i].getSound() == pSound)
			return true;
	}
	return false;
}


//-----------------------------------------------------------------------------
// Internal methods
//-----------------------------------------------------------------------------

// This is the callback function of the SDL_AudioCallback prototype
// which fills the audio device stream with our sound data.
void SoundSystem::fillAudioCallback(void *pUserData, Uint8* pStream, int length)
{
	SoundSystem* pSoundSystem = (SoundSystem*) pUserData;

	// Make sure we start with silence.
	SDL_memset(pStream, 0, length);
	
	const Uint8* pChunkData;
	int chunkLength;
	int volume = (int) (pSoundSystem->mMasterVolume * SDL_MIX_MAXVOLUME);
	SDL_AudioFormat audioFormat = pSoundSystem->mDeviceAudioFormat.sampleFormat;

	// Mix the audio data for all sound instances.
	for (unsigned int i = 0; i < pSoundSystem->mSoundInstances.size(); i++)
	{
		SoundInstance& soundInstance = pSoundSystem->mSoundInstances[i];

		if (soundInstance.getSound()->mGroup == SOUND_GROUP_NONE ||
			pSoundSystem->isSoundGroupEnabled(soundInstance.getSound()->mGroup))
		{
			// Mix this sound instance if it isn't done playing.
			if (!soundInstance.isDone())
			{
				soundInstance.nextAudioChunk(length, &pChunkData, &chunkLength);
				SDL_MixAudioFormat(pStream, pChunkData, soundInstance.getSound()->mSampleFormat, chunkLength, volume);
			}

			// Remove completed sound instances form list.
			if (soundInstance.isDone())
			{
				pSoundSystem->mSoundInstances.erase(pSoundSystem->mSoundInstances.begin() + i);
				i--;
			}
		}
	}
}

