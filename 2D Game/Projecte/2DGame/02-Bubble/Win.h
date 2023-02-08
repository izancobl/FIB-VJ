#ifndef _WIN_INCLUDE
#define _WIN_INCLUDE

#include <vector>
#include "Sprite.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class Win {
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

#endif // _WIN_INCLUDE