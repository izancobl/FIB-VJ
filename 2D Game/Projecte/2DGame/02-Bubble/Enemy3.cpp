#include "Enemy3.h"
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
	MOVE_UP, MOVE_DOWN, EXPLODE, MOVE_UPD, MOVE_DOWND
};

bool Enemy3::getAliveness() {
	return isAlive;
}


void Enemy3::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	isAlive = true;
	lives = 2;
	spritesheet.loadFromFile("images/spriteEnemy3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(60 / 1.5, 68 / 1.5), glm::vec2(0.25, 1), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(5);

	sprite->setAnimationSpeed(MOVE_UP, 8);
	sprite->addKeyframe(MOVE_UP, glm::vec2(0.25f, 0.0f));

	sprite->setAnimationSpeed(MOVE_DOWN, 8);
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(MOVE_UPD, 1500);
	sprite->addKeyframe(MOVE_UPD, glm::vec2(0.75f, 0.0f));

	sprite->setAnimationSpeed(MOVE_DOWND,1500);
	sprite->addKeyframe(MOVE_DOWND, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(EXPLODE, 8);
	sprite->addKeyframe(EXPLODE, glm::vec2(0.25, 0.25f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy3::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (isAlive) move();
}

void Enemy3::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

glm::ivec2 Enemy3::getPosition()
{
	return posEnemy;
}

void Enemy3::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy3::render()
{
	sprite->render();
}

void Enemy3::move() {

	if (movement == 0 && n != 20) {
		sprite->changeAnimation(MOVE_UP);
		if (map->collisionMoveUp(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.y += 4;
		}
		else posEnemy.y -= 4;

		++n;

		if (n == 20) {
			movement = 1;
			n = 0;
		}
	}

	else if (movement == 1 && n != 20) {
		sprite->changeAnimation(MOVE_DOWN);
		if (map->collisionMoveDown(posEnemy, glm::ivec2(32, 32), &posEnemy.y)) {
			posEnemy.y -= 4;
		}
		else posEnemy.y += 4;

		++n;

		if (n == 20) {
			movement = 0;
			n = 0;
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy3::loseLife(int damage)
{
	lives -= damage;
	if (sprite->animation() == MOVE_UP) sprite->changeAnimation(MOVE_UPD);
	else if (sprite->animation() == MOVE_DOWN) sprite->changeAnimation(MOVE_DOWND);
	if (lives <= 0) isAlive = false;
}

int Enemy3::getPoints() {
	return points;
}