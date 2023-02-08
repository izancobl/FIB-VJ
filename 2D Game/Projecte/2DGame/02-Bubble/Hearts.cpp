#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Hearts.h"


enum HeartsAnims
{
	ZERO, ONE, TWO, THREE
};

void Hearts::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	currentTime = 0;
	spritesheet.loadFromFile("images/lifes.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(372 / 1.5, 124 / 1.5), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(ZERO, 8);
	sprite->addKeyframe(ZERO, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(ONE, 8);
	sprite->addKeyframe(ONE, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(TWO, 8);
	sprite->addKeyframe(TWO, glm::vec2(0.0f, 0.5f));

	sprite->setAnimationSpeed(THREE, 8);
	sprite->addKeyframe(THREE, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(THREE);

	sprite->setPosition(glm::vec2(50, 45));

}

void Hearts::update(int currentTime, int lives)
{
	sprite->update(currentTime);
	if(lives == 3) sprite->changeAnimation(THREE);
	else if (lives == 2) sprite->changeAnimation(TWO);
	else if (lives == 1) sprite->changeAnimation(ONE);
	else if (lives == 0) {
		sprite->changeAnimation(ZERO);
		Audio::instance().playGameOver();
	}

	if (currentTime <= 136755.0f)
		sprite->setPosition(glm::vec2(currentTime / 7.f + 50, 45));
	else
		sprite->setPosition(glm::vec2(136755.0f / 7.f, 45));
}

void Hearts::render()
{
	sprite->render();
}

void Hearts::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}