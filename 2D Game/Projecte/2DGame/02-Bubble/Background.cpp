#include "Background.h"
#include "Sprite.h"
#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Background::init() {
	initShaders();
	currentTime = 0.0f;
	spritesheet.loadFromFile("images/background.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(20520 * 2, 896 * 2), glm::vec2(1.0, 1.0), &spritesheet, &texProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(0, 0));

	projection = glm::ortho(0.f, float(1280 - 1), float(960 - 1), 0.f);
	currentTime = 0.0f;
}

void Background::update(int deltaTime) {
	currentTime += deltaTime;
	sprite->update(deltaTime);

	if (currentTime <= 136755.0f)
		projection = glm::ortho(currentTime / 4.f, float(1280 - 1) + currentTime / 4.f, float(960 - 1), 0.f);
	else
		projection = glm::ortho(136755.0f / 4.f, float(1280 - 1) + 136755.0f / 4.f, float(960 - 1), 0.f);

}

void Background::render() {
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	sprite->render();
}

void Background::initShaders()
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