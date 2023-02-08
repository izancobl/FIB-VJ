#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, EXPLODE, SHOOT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	invulnerability = false;
	force = false;
	isAlive = true;
	lives = 3;
	points = 0;
	h = new Hearts();
	h->init(tileMapPos, shaderProgram);
	p = new Points();
	p->init(tileMapPos, shaderProgram);
	spritesheet.loadFromFile("images/spriteSheetNaveBueno.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.25), &spritesheet, &shaderProgram);


	sprite->setNumberAnimations(7);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f, 0.f));

		sprite->setAnimationSpeed(MOVE_UP, 8);
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.5, 0.25f));

		sprite->setAnimationSpeed(MOVE_DOWN, 8);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.5f));

		sprite->setAnimationSpeed(EXPLODE, 8);
		sprite->addKeyframe(EXPLODE, glm::vec2(0.25, 0.25f));
		
	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::setInvulnerability() {
	invulnerability = !invulnerability;
}

bool Player::getInvulnerability() {
	return invulnerability;
}

void Player::setForce() {
	force = !force;
}

bool Player::getAliveness()
{
	return isAlive;
}

void Player::setAliveness()
{
	isAlive = true;
}

int Player::getLives()
{
	return lives;
}

void Player::loseLife()
{
	this->lives = this->lives--;
	posPlayer.y = 448;
	Audio::instance().playSpaceShipCrashing();
}

void Player::update(int deltaTime, int currentTime)
{
	sprite->update(deltaTime);
	h->update(currentTime, lives);
	p->update(currentTime, points);
	
	if (points >= 1000) {
		if (lives < 3) {
			lives++;
			Audio::instance().playOneUp();
			points = 0;
		}
	}
	
	if (lives == 0) isAlive = false;
	
	if (isAlive) {
		// MOVES
		if (currentTime <= 135000.0f) {
			// Constant velocity
			posPlayer.x += 3;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)) && !invulnerability) {
				loseLife();
			}

			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
				if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)) && !invulnerability)
				{
					loseLife();

				}
				else
					posPlayer.x -= 4;
			}
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
				if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)) && !invulnerability)
				{
					loseLife();
				}
				else
					posPlayer.x += 3;
			}
		}
		

		if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			if (sprite->animation() != MOVE_UP)
				sprite->changeAnimation(MOVE_UP);
			if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y) && !invulnerability)
			{
				loseLife();
			}
			else
				posPlayer.y -= 3;

		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			if (sprite->animation() != MOVE_DOWN)
				sprite->changeAnimation(MOVE_DOWN);
			if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y) && !invulnerability)
			{
				loseLife();
			}
			else
				posPlayer.y += 3;
		}

		else
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
	h->render();
	p->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

glm::vec2 Player::getPosition() {
	return posPlayer;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Player::getPoints()
{
	return points;
}

void Player::setPoints(int point)
{
	points = point;
}

