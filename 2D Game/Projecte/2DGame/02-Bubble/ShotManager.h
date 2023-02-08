#ifndef _SHOTMANAGER_INCLUDE
#define _SHOTMANAGER_INCLUDE

#include <vector>
#include "Shot.h"

// ShotManager is a singleton (a class with a single instance)

class ShotManager
{

private:
	ShotManager() {}

public:
	static ShotManager& instance()
	{
		static ShotManager G;

		return G;
	}

	void init();
	void update(int deltaTime);
	void render();

	// Added methods
	vector<Shot *> getAllPlayerShots();
	vector<Shot*> getAllEnemyShots();
	
	void addPlayerShot(glm::vec2 posPlayer, ShaderProgram& shaderProgram, TileMap* map, bool isPowerful);
	void addEnemyShot(glm::vec2 posEnemy, ShaderProgram& shaderProgram, TileMap* map, bool isPowerful);

private:
	std::vector< Shot* > playerShots;
	std::vector< Shot* > enemyShots;
	Shot* shot;
};


#endif // _SHOTMANAGER_INCLUDE


