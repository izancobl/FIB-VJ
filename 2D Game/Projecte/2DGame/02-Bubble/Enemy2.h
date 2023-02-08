#ifndef _ENEMY2_INCLUDE
#define _ENEMY2_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Enemy.h"


class Enemy2 : public Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);

	void move();
	void loseLife(int damage);

	void setTileMap(TileMap* tileMap);
	void render();
	
	glm::ivec2 getPosition();
	bool getAliveness();
	void setPosition(const glm::vec2& pos);
	int getPoints();

private:
	bool bJumping;
	bool isAlive;
	glm::ivec2 tileMapDispl, posEnemy;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int movement = 0;
	int n = 0;
	int lives;
	int points = 25;
};



#endif // _ENEMY2_INCLUDE