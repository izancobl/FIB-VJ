#include "Enemy4.h"
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
	STAND_LEFT, STAND_LEFTD, EXPLODE
};

bool Enemy4::getAliveness() {
	return isAlive;
}

void Enemy4::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	isAlive = true;
	lives = 4;
	spritesheet.loadFromFile("images/spriteEnemy4.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(59, 36), glm::vec2(0.5, 1), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.f));

	sprite->setAnimationSpeed(STAND_LEFTD, 1500);
	sprite->addKeyframe(STAND_LEFTD, glm::vec2(0.5, 0.0f));

	sprite->setAnimationSpeed(EXPLODE, 8);
	sprite->addKeyframe(EXPLODE, glm::vec2(0.25, 0.25f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));

}

void Enemy4::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (isAlive) move();
}

void Enemy4::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

glm::ivec2 Enemy4::getPosition()
{
	return posEnemy;
}

void Enemy4::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy4::render()
{
	sprite->render();
}

void Enemy4::move() {
	posEnemy.x -= 1.5;
	sprite->changeAnimation(STAND_LEFT);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Enemy4::loseLife(int damage)
{
	lives -= damage;
	sprite->changeAnimation(STAND_LEFT);
	if (lives <= 0) isAlive = false;
}

int Enemy4::getPoints() {
	return points;
}