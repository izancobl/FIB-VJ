#ifndef _ENEMYMANAGER_INCLUDE
#define _ENEMYMANAGER_INCLUDE

#include <vector>
#include "Sprite.h"
#include "TileMap.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"

// EnemyManager is a singleton (a class with a single instance)

class EnemyManager
{
	private:
		EnemyManager() {}

public:
	static EnemyManager& instance()
	{
		static EnemyManager E;

		return E;
	}
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, TileMap* map);
	void update(int currentTime);
	void render();

	vector<Enemy* > getAllEnemies();


private:
	int numEnemy;
	std::vector<Enemy*> enemies;
	Enemy1* e1;
	Enemy2* e2;
	Enemy3* e3;
	Enemy4* e4;

	int cont = 0;
	glm::ivec2 tl;
	ShaderProgram sp;
	float spawnpos;
	TileMap* m;
	float x = 1400;
	int currentTime;
};


#endif // _ENEMYMANAGER_INCLUDE

