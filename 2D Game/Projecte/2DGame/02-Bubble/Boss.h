#ifndef _BOSS_INCLUDE
#define _BOSS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Boss
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);

	void shoot();

	void setTileMap(TileMap* tileMap);
	void render();

	glm::ivec2 getPosition();
	void setPosition(const glm::vec2& pos);

	void loseLife(int damage);
	bool getAliveness();

private:
	bool bJumping;
	bool isAlive;
	int lives;
	int cont;
	glm::ivec2 tileMapDispl, posBoss;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	bool soundWinPlayed;
};


#endif // _BOSS_INCLUDE