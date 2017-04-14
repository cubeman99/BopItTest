#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include "Sound.h"
#include <string>
#include <vector>


// Looping modes for playing sounds.
enum SoundLoopMode
{
	SOUND_PLAY_LOOP = 0,
	SOUND_PLAY_ONCE,
};


// A sound instance is a sound that is being played.
class SoundInstance
{
public:
	SoundInstance(const Sound* pSound, SoundLoopMode loopMode);

	// Accessors.
	bool isDone() const;
	inline const Sound*		getSound()		const { return mpSound; }
	inline SoundLoopMode	getLoopMode()	const { return mLoopMode; }
	
	// Mutators.
	void nextAudioChunk(int length, const Uint8** pAudioChunk, int* pChunkLength);

private:
	const Sound*	mpSound;		// The sound this is an instance of.
	Uint32			mAudioPosition;	// Current position in the audio data during playback.
	SoundLoopMode	mLoopMode;
};


// The sound system is respsible for playing audio,
class SoundSystem
{
public:
	SoundSystem();
	~SoundSystem();

	// Control functions
	bool init();
	void cleanup();

	// Accessors
	inline const AudioFormat& getDeviceAudioFormat() const { return mDeviceAudioFormat; }
	inline float getMasterVolume() const { return mMasterVolume; }
	inline bool isSoundGroupEnabled(SoundGroup group) const { return mSoundGroupsEnabled[(int) group]; }
	inline void enableSoundGroup(SoundGroup group, bool isEnabled) { mSoundGroupsEnabled[(int) group] = isEnabled; }

	// Mutators
	void setMasterVolume(float masterVolume);

	// Playback
	//void playSound(const std::string& soundName, SoundLoopMode loopMode = SOUND_PLAY_ONCE);
	void playSound(const Sound* pSound, SoundLoopMode loopMode = SOUND_PLAY_ONCE);
	//void stopSound(const std::string& soundName);
	void stopSound(const Sound* pSound);
	//bool isSoundPlaying(const std::string& soundName);
	bool isSoundPlaying(const Sound* pSound);


private:
	static void fillAudioCallback(void *pUserData, Uint8* pStream, int length);

	bool				mIsInitialized;
	AudioFormat			mDeviceAudioFormat;
	SDL_AudioSpec		mSDLAudioDeviceSpec;
	SDL_AudioDeviceID	mSDLAudioDeviceID;
	float				mMasterVolume;
	std::vector<SoundInstance> mSoundInstances;
	bool				mSoundGroupsEnabled[NUM_SOUND_GROUPS];
};


#endif // SOUND_SYSTEM_H