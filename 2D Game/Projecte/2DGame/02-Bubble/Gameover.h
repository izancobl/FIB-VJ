#ifndef _GAMEOVER_INCLUDE
#define _GAMEOVER_INCLUDE

#include <vector>
#include "Sprite.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class Gameover {
public:

	void init();
	void render();
	void update(int deltaTime);

private:
	void initShaders();

	int id;
	Sprite* sprite;
	float currentTime;
	Texture spritesheet;
	ShaderProgram texProgram;
	glm::mat4 projection;

};

#endif // _GAMEOVER_INCLUDE