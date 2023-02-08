#ifndef _SHOT_INCLUDE
#define _SHOT_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Shot
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, bool isPlayerShot, bool isPowerful);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	
	glm::ivec2 getPosition();
	void setPosition(const glm::vec2& pos);

	bool getAliveness();
	void setAliveness();

	int getShotDamage();
	bool getIsPowerful();

private:
	bool isAlive;
	bool isPowerful;
	bool isPlayerShot;
	int damage;
	glm::ivec2 tileMapDispl, posShot;
	int jumpAngle, startY;
	Texture spritesheet;
	ShaderProgram texProgram;
	Sprite* sprite;
	TileMap* map;
};


#endif // _PLAYER_INCLUDE


