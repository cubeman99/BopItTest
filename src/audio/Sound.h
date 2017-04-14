#ifndef SOUND_H
#define SOUND_H

#include <SDL_audio.h>
#include <string>

class SoundSystem;


// For now, these equate to SDL_AudioFormat
enum AudioSampleFormat
{
	AUDIO_FORMAT_S16	= AUDIO_S16,
	AUDIO_FORMAT_U16	= AUDIO_U16,
	AUDIO_FORMAT_S8		= AUDIO_S8,
	AUDIO_FORMAT_U8		= AUDIO_U8,
	AUDIO_FORMAT_F32	= AUDIO_F32,
};


struct AudioFormat
{
	SDL_AudioFormat	sampleFormat;
	int				channels;
	int				frequency;
};


enum SoundGroup
{
	SOUND_GROUP_NONE = 0,
	SOUND_GROUP_SFX,
	SOUND_GROUP_MUSIC,
	NUM_SOUND_GROUPS
};


class Sound
{
	friend class SoundSystem;

public:
	Sound();
	~Sound();

	// Accessors
	inline const Uint8*	getAudioData()		const { return mpAudioData; }
	inline Uint32		getAudioLength()	const { return mAudioLength; }
	inline int			getNumChannels()	const { return mNumChannels; }
	inline int			getSampleRate()		const { return mFrequency; }
	inline SoundGroup	getSoundGroup()		const { return mGroup; }

	// Mutators
	inline void setSoundGroup(SoundGroup soundGroup) { mGroup = soundGroup; }

	// Static methods
	static Sound* loadWAV(const std::string& fileName, const AudioFormat& desiredFormat, bool shouldConvert = true);

private:
	unsigned char*	mpAudioData;
	unsigned int	mAudioLength;
	SDL_AudioFormat	mSampleFormat;
	int				mNumChannels;
	int				mFrequency;
	bool			mAllocBySDLWAV;
	SoundGroup		mGroup;
};


#endif // SOUND_H