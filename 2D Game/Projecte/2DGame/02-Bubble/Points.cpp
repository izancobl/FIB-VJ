#include "Points.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"


enum PointsAnims
{
	F0, F1, F2, F3, F4
};

void Points::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/points.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(361 / 1.5, 60 / 1.5), glm::vec2(1.f, 0.2f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(F0, 8);
	sprite->addKeyframe(F0, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(F1, 8);
	sprite->addKeyframe(F1, glm::vec2(0.0f, 0.2f));

	sprite->setAnimationSpeed(F2, 8);
	sprite->addKeyframe(F2, glm::vec2(0.0f, 0.4f));

	sprite->setAnimationSpeed(F3, 8);
	sprite->addKeyframe(F3, glm::vec2(0.0f, 0.6f));

	sprite->setAnimationSpeed(F4, 8);
	sprite->addKeyframe(F4, glm::vec2(0.0f, 0.8f));


	sprite->changeAnimation(F0);

	sprite->setPosition(glm::vec2(900, 45));

}
  
void Points::update(int currentTime, int points)
{
	sprite->update(currentTime);

	if(points < 250) sprite->changeAnimation(F0);
	else if (points >= 250 && points < 500) sprite->changeAnimation(F1);
	else if (points >= 500 && points < 750) sprite->changeAnimation(F2);
	else if (points >= 750 && points < 1000) sprite->changeAnimation(F3);
	else if (points >= 1000) sprite->changeAnimation(F4);

	if (currentTime <= 136755.0f)
		sprite->setPosition(glm::vec2(currentTime / 7.f + 900, 45));
	else
		sprite->setPosition(glm::vec2(136755.0f / 7.f + 900, 45));
}

void Points::render()
{
	sprite->render();
}

void Points::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}