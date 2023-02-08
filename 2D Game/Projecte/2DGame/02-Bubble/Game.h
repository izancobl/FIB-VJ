#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "Menu.h"
#include "Instructions.h"
#include "Credits.h"
#include "Background.h"
#include "Audio.h"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960


// Game is a singleton (a class with a single instance) that represents our whole application

class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button, int x, int y);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	int currentScreen;
	int spaceCounter;
	int delay;
	bool spacePressed;

	Menu menu;
	Instructions inst;
	Credits cre;
	Background bg;
	int dead = 0;

	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time

};


#endif // _GAME_INCLUDE


