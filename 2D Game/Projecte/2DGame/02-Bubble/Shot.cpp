#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Shot.h"


enum ShotAnims
{
	SHOT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, EXPLODE, SHOOT
};


void Shot::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, bool isPlayerShot, bool isPowerful)
{
	isAlive = true;
	this->isPlayerShot = isPlayerShot;
	this->isPowerful = isPowerful;
	
	if (isPlayerShot) {
		if (isPowerful) {
			damage = 3;
			spritesheet.loadFromFile("images/powerfulshot_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(64, 32), glm::vec2(1.0, 0.33333333), &spritesheet, &shaderProgram);

			sprite->setNumberAnimations(1);

			sprite->setAnimationSpeed(SHOT, 8);
			sprite->addKeyframe(SHOT, glm::vec2(0.f, 0.333333333333f));
			sprite->addKeyframe(SHOT, glm::vec2(0.f, 0.f));
		}

		else {
			damage = 1;
			spritesheet.loadFromFile("images/normalbullet_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0, 1.0), &spritesheet, &shaderProgram);

			sprite->setNumberAnimations(1);

			sprite->setAnimationSpeed(SHOT, 8);
			sprite->addKeyframe(SHOT, glm::vec2(0.f, 0.f));
		}
	}

	else {
		if (isPowerful) {
			damage = 3;
			spritesheet.loadFromFile("images/shotb2.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(124/3.5, 82/3.5), glm::vec2(1.0, 1.0), &spritesheet, &shaderProgram);

			sprite->setNumberAnimations(1);

			sprite->setAnimationSpeed(SHOT, 8);
			sprite->addKeyframe(SHOT, glm::vec2(0.f, 0.f));
		}

		else {
			damage = 1;
			spritesheet.loadFromFile("images/shotb1.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(120/3, 120/3), glm::vec2(1.0, 1.0), &spritesheet, &shaderProgram);

			sprite->setNumberAnimations(1);

			sprite->setAnimationSpeed(SHOT, 8);
			sprite->addKeyframe(SHOT, glm::vec2(0.f, 0.f));
		}
	}

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posShot.x), float(tileMapDispl.y + posShot.y)));

}

bool Shot::getAliveness()
{
	return isAlive;
}

void Shot::setAliveness()
{
	isAlive = !isAlive;
}

int Shot::getShotDamage()
{
	return damage;
}

bool Shot::getIsPowerful()
{
	return isPowerful;
}

void Shot::update(int deltaTime)
{
	sprite->update(deltaTime);
	
	if (isPlayerShot) {
		// Constant velocity
		posShot.x += 10;
		if (map->collisionMoveRight(posShot, glm::ivec2(32, 32))) isAlive = false;
	}

	else {
		// Constant velocity
		posShot.x -= 10;

		if (map->collisionMoveLeft(posShot, glm::ivec2(32, 32))) isAlive = false;
	}
	sprite->changeAnimation(SHOT);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posShot.x), float(tileMapDispl.y + posShot.y)));
}

void Shot::render()
{
	sprite->render();
}

void Shot::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

glm::ivec2 Shot::getPosition()
{
	return posShot;
}

void Shot::setPosition(const glm::vec2& pos)
{
	posShot = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + (posShot.x)), float(tileMapDispl.y + (posShot.y))));
}




