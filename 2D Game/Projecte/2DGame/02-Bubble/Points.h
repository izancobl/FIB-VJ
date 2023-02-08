#ifndef _POINTS_INCLUDE
#define _POINTS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"



class Points
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int currentTime, int lives);
	void render();

	void setTileMap(TileMap* tileMap);

private:
	int currentTime;
	int points;
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	glm::mat4 projection;
};

#endif // _POINTS_INCLUDE