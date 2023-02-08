#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE

#include <vector>
#include "Sprite.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>

class Instructions {
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

#endif // _INSTRUCTIONS_INCLUDE
