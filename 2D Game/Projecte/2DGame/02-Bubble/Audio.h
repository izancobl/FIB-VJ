#ifndef _AUDIO_INCLUDE
#define _AUDIO_INCLUDE

#pragma once
#include <string>

class Audio
{
public:
	static Audio& instance()
	{
		static Audio A;

		return A;
	}
	Audio();
	~Audio();
	void playMusic(char* url);
	void playMenu();
	void playLevel();
	void playWin();
	void playGameOver();
	void playPlayerShot();
	void playPlayerShot2();
	void playOneUp();
	void playSpaceShipCrashing();
	void playDamage();
	void playBossDamage();
	void playBossShot();

	void resumeMusic();
	void pauseMusic();
	void stopMusic();

	void explosionEffect();
	void changeScreenEffect();

private:
	void init();
};

#endif // _AUDIO_INCLUDE