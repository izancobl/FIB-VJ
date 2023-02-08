#include "Enemy1.h"
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
	STAND_LEFT, MOVE_UP, MOVE_DOWN, STAND_LEFTD, MOVE_UPD, MOVE_DOWND, EXPLODE
};

bool Enemy1::getAliveness() {
	return isAlive;
}

void Enemy1::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	isAlive = true;
	lives = 1;
	movement = 1 + rand() % (3 - 1);

	spritesheet.loadFromFile("images/spriteEnemy1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);


	sprite->setNumberAnimations(7);


	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.f));

	sprite->setAnimationSpeed(MOVE_UP, 8);
	sprite->addKeyframe(MOVE_UP, glm::vec2(0.0, 0.5f));

	sprite->setAnimationSpeed(MOVE_DOWN, 8);
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25f, 0.0f));

	sprite->setAnimationSpeed(STAND_LEFTD, 8);
	sprite->addKeyframe(STAND_LEFTD, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(MOVE_UPD, 1500);
	sprite->addKeyframe(MOVE_UPD, glm::vec2(0.5, 0.5f));

	sprite->setAnimationSpeed(MOVE_DOWND, 1500);
	sprite->addKeyframe(MOVE_DOWND, glm::vec2(0.75f, 0.0f));

	sprite->setAnimationSpeed(EXPLODE, 8);
	sprite->addKeyframe(EXPLODE, glm::vec2(0.75, 0.75f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy1::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (isAlive) move();
}

void Enemy1::move() {

	posEnemy.x -= 4;

	if (movement == 0 && n != 25) {
		sprite->changeAnimation(MOVE_UP);
		if (map->collisionMoveUp(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.y += 5;
		}
		else posEnemy.y -= 5;

		++n;

		if (n == 25) {
			movement = 1;
			n = 0;
		}
	}

	else if (movement == 1 && n != 25) {
		sprite->changeAnimation(MOVE_DOWN);
		if (map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.y -= 5;
		}
		else posEnemy.y += 5;

		++n;

		if (n == 25) {
			movement = 0;
			n = 0;
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy1::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

glm::ivec2 Enemy1::getPosition()
{
	return posEnemy;
}

void Enemy1::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy1::render()
{
	sprite->render();
}

void Enemy1::loseLife(int damage)
{
	lives -= damage;

	if (sprite->animation() == MOVE_UP) sprite->changeAnimation(MOVE_UPD);
	else if (sprite->animation() == MOVE_DOWN) sprite->changeAnimation(MOVE_DOWND);

	if (lives <= 0) this->isAlive = false;
}

int Enemy1::getPoints() {
	return points;
}