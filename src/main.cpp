#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <thread>
#include "BopIt.h"
#include <Windows.h>
#include <SDL.h>
#include "audio/SoundSystem.h"

using namespace std;

#undef main
#undef min
#undef max


int main(int argc, char* argv[])
{
	//-------------------------------------------------------------------------
	// Run the tests

	::testing::InitGoogleTest(&argc, argv);
	int rc = RUN_ALL_TESTS();
	
	cout << "Press enter to start playing bop it...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	

	//-------------------------------------------------------------------------
	// Play a game of bopit!!!!

	system("cls");

	// Initialize systems
	SDL_Init(SDL_INIT_EVERYTHING);
	SoundSystem soundSystem;
	soundSystem.init();
	soundSystem.setMasterVolume(0.35f);
	
	// Load sounds
	Sound* soundMusicIntro = Sound::loadWAV("../sounds/music_intro.wav", soundSystem.getDeviceAudioFormat());
	Sound* soundMusicRiff = Sound::loadWAV("../sounds/music_riff.wav", soundSystem.getDeviceAudioFormat());
	Sound* soundGameOver = Sound::loadWAV("../sounds/game_over_begin.wav", soundSystem.getDeviceAudioFormat());
	Sound* soundGameOverPost[5];
	soundGameOverPost[0] = Sound::loadWAV("../sounds/game_over_1.wav", soundSystem.getDeviceAudioFormat());
	soundGameOverPost[1] = Sound::loadWAV("../sounds/game_over_2.wav", soundSystem.getDeviceAudioFormat());
	soundGameOverPost[2] = Sound::loadWAV("../sounds/game_over_3.wav", soundSystem.getDeviceAudioFormat());
	soundGameOverPost[3] = Sound::loadWAV("../sounds/game_over_4.wav", soundSystem.getDeviceAudioFormat());
	soundGameOverPost[4] = Sound::loadWAV("../sounds/game_over_5.wav", soundSystem.getDeviceAudioFormat());
	Sound* actionSoundPrompts[NUM_ACTIONS];
	Sound* actionSoundResponses[NUM_ACTIONS];
	actionSoundPrompts[ACTION_BOP]		= Sound::loadWAV("../sounds/vo_bopit.wav", soundSystem.getDeviceAudioFormat());
	actionSoundPrompts[ACTION_PULL]		= Sound::loadWAV("../sounds/vo_pullit.wav", soundSystem.getDeviceAudioFormat());
	actionSoundPrompts[ACTION_TWIST]	= Sound::loadWAV("../sounds/vo_twistit.wav", soundSystem.getDeviceAudioFormat());
	actionSoundPrompts[ACTION_SPIN]		= Sound::loadWAV("../sounds/vo_spinit.wav", soundSystem.getDeviceAudioFormat());
	actionSoundPrompts[ACTION_FLICK]	= Sound::loadWAV("../sounds/vo_flickit.wav", soundSystem.getDeviceAudioFormat());
	actionSoundResponses[ACTION_BOP]	= Sound::loadWAV("../sounds/sfx_bopit.wav", soundSystem.getDeviceAudioFormat());
	actionSoundResponses[ACTION_PULL]	= Sound::loadWAV("../sounds/sfx_pullit.wav", soundSystem.getDeviceAudioFormat());
	actionSoundResponses[ACTION_TWIST]	= Sound::loadWAV("../sounds/sfx_twistit.wav", soundSystem.getDeviceAudioFormat());
	actionSoundResponses[ACTION_SPIN]	= Sound::loadWAV("../sounds/sfx_spinit.wav", soundSystem.getDeviceAudioFormat());
	actionSoundResponses[ACTION_FLICK]	= Sound::loadWAV("../sounds/sfx_flickit.wav", soundSystem.getDeviceAudioFormat());

	// Init action text and keyboard keys.
	string actionPrompts[NUM_ACTIONS];
	actionPrompts[ACTION_BOP]	= "Bop it!";
	actionPrompts[ACTION_PULL]	= "Pull it!";
	actionPrompts[ACTION_TWIST] = "Twist it!";
	actionPrompts[ACTION_SPIN]	= "Spin it!";
	actionPrompts[ACTION_FLICK]	= "Flick it!";
	int actionKeys[NUM_ACTIONS];
	actionKeys[ACTION_BOP]		= (int) 'B';
	actionKeys[ACTION_PULL]		= (int) 'P';
	actionKeys[ACTION_TWIST]	= (int) 'T';
	actionKeys[ACTION_SPIN]		= (int) 'S';
	actionKeys[ACTION_FLICK]	= (int) 'F';
	bool keyStatesCurr[256] = { 0 };
	bool keyStatesPrev[256] = { 0 };

	printf("~ BOP IT ~\n");
	printf("Controls:\n");
	printf(" * Escape = exit\n");
	printf(" * I = insult\n");
	for (int i = 0; i < NUM_ACTIONS; ++i)
	{
		printf(" * %c = %s\n", (char) actionKeys[i], actionPrompts[i].c_str());
	}
	printf("\n");

	bool quit = false;
	BopIt bopit;
	srand((unsigned int) time(NULL));
	
	while (!quit)
	{
		printf("Starting new game...\n\n");

		// Music intro.
		Sleep(500);
		soundSystem.playSound(soundMusicIntro);
		Sleep(1800);

		// Start game and first action prompt.
		bopit.startGame();
		BopItAction promptedAction = bopit.getCurrentAction();
		cout << actionPrompts[(int) promptedAction] << endl;
		soundSystem.playSound(actionSoundPrompts[promptedAction]);
		Sleep(200);
		soundSystem.playSound(soundMusicRiff);

		// Play the game.
		while (bopit.isPlaying())
		{
			// Update keyboard state.
			for (unsigned int i = 0; i < 255; ++i)
			{
				keyStatesPrev[i] = keyStatesCurr[i];
				keyStatesCurr[i] = (GetAsyncKeyState(i) != 0);
			}

			// Check for pressing an action key.
			BopItAction pressedAction = ACTION_NONE;
			for (unsigned int i = 0; i < NUM_ACTIONS; ++i)
			{
				if (keyStatesCurr[actionKeys[i]] && !keyStatesPrev[actionKeys[i]])
				{
					pressedAction = (BopItAction) i;
					break;
				}
			}

			if (keyStatesCurr[(int) 'I'] && !keyStatesPrev[(int) 'I'])
			{
				bopit.insult();
				printf("You insulted the bop it!\n");
			}
			else if (pressedAction != ACTION_NONE)
			{
				soundSystem.playSound(actionSoundResponses[pressedAction]);

				if (bopit.performAction(pressedAction))
				{
					// next action!
					promptedAction = bopit.getCurrentAction();
					Sleep(500);
					soundSystem.playSound(soundMusicRiff);
					Sleep(500);
					cout << actionPrompts[(int) promptedAction] << endl;
					soundSystem.playSound(actionSoundPrompts[promptedAction]);
				}
				else
				{
					// Game over!!
				}
			}

			// Escape will quit.
			if (GetAsyncKeyState((int) VK_ESCAPE) != 0)
			{
				quit = true;
				break;
			}

			Sleep(17);
		}

		if (quit)
			break;

		// Game over!!
		Sleep(400);
		soundSystem.playSound(soundGameOver);
		Sleep(3000);
		soundSystem.playSound(soundGameOverPost[rand() % 5]);
		Sleep(300);
		cout << "Game Over!!\n";
		cout << "You scored " << bopit.getScore() << " points\n";
		Sleep(1000);
		cout << endl;

		cout << "Press enter to play again...";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	// Cleanup
	delete soundMusicIntro;
	delete soundMusicRiff;
	delete soundGameOver;
	for (int i = 0; i < 5; ++i)
		delete soundGameOverPost[i];
	for (int i = 0; i < NUM_ACTIONS; ++i)
	{
		delete actionSoundPrompts[i];
		delete actionSoundResponses[i];
	}
	soundSystem.cleanup();
	SDL_Quit();

	return rc;
}
