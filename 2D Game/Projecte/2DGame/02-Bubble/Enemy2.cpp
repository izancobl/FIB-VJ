#include "Enemy2.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum EnemyAnims
{
	STAND_LEFT, MOVE_UP, MOVE_DOWN, EXPLODE, MOVE_UPD, MOVE_DOWND
};


void Enemy2::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	lives = 2;
	bJumping = false;
	isAlive = true;
	spritesheet.loadFromFile("images/spriteEnemy2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(52, 56), glm::vec2(0.25, 0.333333333), &spritesheet, &shaderProgram);


	sprite->setNumberAnimations(6);


	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.f));

	sprite->setAnimationSpeed(MOVE_UP, 8);
	sprite->addKeyframe(MOVE_UP, glm::vec2(0.0, 0.3333333f));

	sprite->setAnimationSpeed(MOVE_DOWN, 8);
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25f, 0.0f));

	sprite->setAnimationSpeed(MOVE_UPD, 1500);
	sprite->addKeyframe(MOVE_UPD, glm::vec2(0.5, 0.3333333f));

	sprite->setAnimationSpeed(MOVE_DOWND, 1500);
	sprite->addKeyframe(MOVE_DOWND, glm::vec2(0.75f, 0.0f));

	sprite->setAnimationSpeed(EXPLODE, 1500);
	sprite->addKeyframe(EXPLODE, glm::vec2(0.0, 0.6666666f));
	sprite->addKeyframe(EXPLODE, glm::vec2(0.5f, 0.33333f));
	sprite->addKeyframe(EXPLODE, glm::vec2(0.5, 0.666666f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

bool Enemy2::getAliveness() {
	return isAlive;
}

void Enemy2::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (!isAlive) {
		sprite->changeAnimation(EXPLODE);
	}
	else {
		move();
	}
}

void Enemy2::move() {

	posEnemy.x -= 0.5;

	if (movement == 0 && n != 40) {
		sprite->changeAnimation(MOVE_UP);
		if (map->collisionMoveUp(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.y += 2;
		}
		else posEnemy.y -= 2;

		++n;

		if (n == 40) {
			movement = 1;
			n = 0;
		}
	}

	else if (movement == 1 && n != 40) {
		sprite->changeAnimation(MOVE_DOWN);
		if (map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.y -= 2;
		}
		else posEnemy.y += 2;

		++n;

		if (n == 40) {
			movement = 0;
			n = 0;
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy2::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

glm::ivec2 Enemy2::getPosition()
{
	return posEnemy;
}

void Enemy2::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy2::render()
{
	sprite->render();
}

void Enemy2::loseLife(int damage)
{
	lives -= damage;
	if (sprite->animation() == MOVE_UP) sprite->changeAnimation(MOVE_UPD);
	else if (sprite->animation() == MOVE_DOWN) sprite->changeAnimation(MOVE_DOWND);
	if (lives <= 0) {
		sprite->changeAnimation(EXPLODE);
  		this->isAlive = false;
	}
}

int Enemy2::getPoints() {
	return points;
}