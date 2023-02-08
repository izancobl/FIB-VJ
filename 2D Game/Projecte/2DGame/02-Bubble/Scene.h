#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy1.h"
#include "ShotManager.h"
#include "EnemyManager.h"
#include "Menu.h"
#include "Boss.h"
#include "Gameover.h"
#include "Win.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	// Added methods
	void setPlayerInvulnerability();
	void setPlayerForce();
	
	void goToFirstPhase();
	void goToSecondPhase();
	void goToThirdPhase();
	void goToFourthPhase();

	void checkCollisions();

	
	void addPlayerShot(bool isPowerful);

private:
	void initShaders();

private:
	int delay;
	TileMap *map;
	Player *player;
	Boss* boss;
	Gameover* go;
	Win* win;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

