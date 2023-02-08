#include "Audio.h"
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <irrKlang.h>
#include <vector>
using namespace irrklang;

ISoundEngine* engineMusic;
ISoundEngine* engineEffects;
ISound* music;
ISound* effect;

Audio::Audio()
{
	init();
}


Audio::~Audio()
{
	music->drop();
	engineEffects->drop();
	engineMusic->drop();

}

void Audio::init() {
	engineMusic = createIrrKlangDevice();
	engineEffects = createIrrKlangDevice();
}

void Audio::playMusic(char* url)
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D(url, true, false, true);
	music->setVolume(0.1f);
}

void Audio::playMenu()
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D("sound/menu.wav", true, false, true);
	music->setVolume(0.3f);
}


void Audio::playLevel() {
	engineMusic->stopAllSounds();
	music = engineMusic->play2D("sound/lev.mp3", true, false, true);
	music->setVolume(0.2f);
}

void Audio::playWin()
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D("sound/win.wav", false, false, true);
	music->setVolume(0.3f);
}

void Audio::playGameOver()
{
	engineMusic->stopAllSounds();
	music = engineMusic->play2D("sound/game_over.wav", false, false, true);
	music->setVolume(0.1f);
}

void Audio::playPlayerShot()
{
	effect = engineMusic->play2D("sound/shot.wav", false, false, true);
	effect->setVolume(0.25f);
}

void Audio::playPlayerShot2()
{
	effect = engineMusic->play2D("sound/shot2.wav", false, false, true);
	effect->setVolume(0.75f);
}

void Audio::playOneUp()
{
	effect = engineMusic->play2D("sound/oneUp.mp3", false, false, true);
	effect->setVolume(0.25f);
}

void Audio::playSpaceShipCrashing()
{
	effect = engineMusic->play2D("sound/spaceshipCrashing.wav", false, false, true);
	effect->setVolume(0.25f);
}

void Audio::playDamage()
{
	effect = engineMusic->play2D("sound/damage.wav", false, false, true);
	effect->setVolume(0.25f);
}

void Audio::playBossDamage()
{
	effect = engineMusic->play2D("sound/damageToBoss.wav", false, false, true);
	effect->setVolume(0.25f);
}

void Audio::playBossShot()
{
	effect = engineMusic->play2D("sound/shotBoss.wav", false, false, true);
	effect->setVolume(0.25f);
}

void Audio::resumeMusic() {
	engineMusic->setAllSoundsPaused(false);
}


void Audio::pauseMusic() {
	engineMusic->setAllSoundsPaused();
}

void Audio::stopMusic() {
	engineMusic->stopAllSounds();
}

void Audio::explosionEffect() {
	effect = engineEffects->play2D("sound/kill.wav", false, false, true);
	effect->setVolume(0.2f);
}

void Audio::changeScreenEffect() {
	effect = engineEffects->play2D("sound/change_screen.wav", false, false, true);
	effect->setVolume(0.5f);
}