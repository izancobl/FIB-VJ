#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


class Enemy
{

public:


	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render() = 0;

	virtual void setTileMap(TileMap* tileMap) = 0;
	
	virtual glm::ivec2 getPosition() = 0;
	virtual void setPosition(const glm::vec2& pos) = 0;

	virtual void move() = 0;
	virtual void loseLife(int damage) = 0;

	
	void setAliveness();
	virtual bool getAliveness() = 0;
	virtual int getPoints() = 0;

protected:
	bool isAlive;
	int p;
};


#endif // _ENEMY_INCLUDE