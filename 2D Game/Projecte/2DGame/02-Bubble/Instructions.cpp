#include "Instructions.h"
#include "Menu.h"
#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Instructions::init() {
	initShaders();
	currentTime = 0.0f;
	spritesheet.loadFromFile("images/instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(1280, 960), glm::vec2(1.0, 1.0), &spritesheet, &texProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(0, 0));

	projection = glm::ortho(0.f, float(1280 - 1), float(960 - 1), 0.f);
	currentTime = 0.0f;
}

void Instructions::update(int deltaTime) {
	currentTime += deltaTime;
	sprite->update(deltaTime);
}


void Instructions::render() {
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	sprite->render();
}

void Instructions::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}