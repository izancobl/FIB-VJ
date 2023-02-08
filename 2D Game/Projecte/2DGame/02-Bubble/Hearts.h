#ifndef _HEARTS_INCLUDE
#define _HEARTS_INCLUDE

#include "Sprite.h"
#include "TileMap.h"



class Hearts
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int currentTime, int lives);
	void render();

	void setTileMap(TileMap* tileMap);

private:
	int currentTime;
	int lives;
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	glm::mat4 projection;
};

#endif // _HEARTS_INCLUDE