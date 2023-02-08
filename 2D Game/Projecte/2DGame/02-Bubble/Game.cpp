#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


enum CurrentScreen {
	MENU, GAME, CREDITS, INSTRUCTIONS
};

void Game::init()
{
	spaceCounter = 0;
	delay = 0;
	spacePressed = false;

	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	currentScreen = MENU;
	Audio::instance().playMenu();
	menu.init();
}

bool Game::update(int deltaTime)
{			
	switch (currentScreen) {
	case MENU:
		menu.update(deltaTime);
		break;

	case GAME:
		if (dead == 0) {
			if (spaceCounter >= 1 && spaceCounter <= 40 && delay <= 0) {
				delay = 10;
				scene.addPlayerShot(false);
				Audio::instance().playPlayerShot();
			}

			else if (spaceCounter >= 100 && !spacePressed) {
				scene.addPlayerShot(true);
				Audio::instance().playPlayerShot2();
				spaceCounter = 0;
			}

			if (delay > 0) delay--;
			if (spacePressed) spaceCounter++;
			else spaceCounter = 0;

			bg.update(deltaTime);
			scene.update(deltaTime);
		}
		else {
			currentScreen = MENU;
			menu.init();
			dead = 0;
		}
		break;

	case INSTRUCTIONS:
		inst.update(deltaTime);
		break;

	case CREDITS:
		cre.update(deltaTime);
		break;
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (currentScreen) {
	case MENU:
		menu.render();
		break;

	case GAME:
		bg.render();
		scene.render();
		break;

	case INSTRUCTIONS:
		inst.render();
		break;

	case CREDITS:
		cre.render();
		break;
	}
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	else if (key == 49) // 1 code
		scene.goToFirstPhase();
	else if (key == 50) // 2 code
		scene.goToSecondPhase();
	else if (key == 51) // 3 code
		scene.goToThirdPhase();
	else if (key == 52) // 4 code
		scene.goToFourthPhase();
	else if (key == 32) // Space code
		spacePressed = true;
	else if (key == 70 || key == 102) // F code
		scene.goToThirdPhase();
	else if (key == 71 || key == 103) // G code
		scene.setPlayerInvulnerability();
	else if (key == 13) {			// Enter code
		Audio::instance().playMenu();
		dead = 1;
	}
		

	keys[key] = true;
}

void Game::keyReleased(int key)
{
	if (key == 32) // Space code
		spacePressed = false;
	
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button, int x, int y)
{
	if (currentScreen == MENU) {
		if (x >= 550 && x < 730 && y >= 540 && y < 620) {
			currentScreen = GAME;
			Audio::instance().playLevel();
			scene.init();
			bg.init();
		}
		else if (x >= 380 && x < 900 && y >= 680 && y < 750) {
			currentScreen = INSTRUCTIONS;
			inst.init();
		}
		else if (x >= 1090 && x < 1240 && y >= 885 && y < 930) {
			currentScreen = CREDITS;
			cre.init();
		}
	}
	else if (currentScreen == INSTRUCTIONS || currentScreen == CREDITS) {
		if (x >= 0 && x < 95 && y >= 0 && y < 80) {
			currentScreen = MENU;
			menu.init();
		}
	}
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





