#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Hearts.h"
#include "Points.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime, int currentTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	
	glm::vec2 getPosition();
	void setPosition(const glm::vec2 &pos);

	//Metodos añadidos
	bool getInvulnerability();
	void setInvulnerability();

	void setPoints(int point);
	int getPoints();

	//bool getForce();
	void setForce();

	bool getAliveness();
	void setAliveness();

	int getLives();
	void loseLife();
	
private:
	bool bJumping;
	bool invulnerability;
	bool force;
	bool isAlive;
	int lives;
	int points;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	Hearts* h;
	Points* p;
};


#endif // _PLAYER_INCLUDE


