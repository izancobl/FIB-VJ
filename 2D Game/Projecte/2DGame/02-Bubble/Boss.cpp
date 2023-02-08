#include "Boss.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

enum BossAnims
{
	STAND_LEFT, DAMAGED
};

void Boss::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	isAlive = true;
	soundWinPlayed = false;
	lives = 70;
	cont = 0;
	spritesheet.loadFromFile("images/boss.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(508/1.54, (492*2)/1.54), glm::vec2(0.5, 1), &spritesheet, &shaderProgram);


	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.0f, 0.f));

	sprite->setAnimationSpeed(DAMAGED, 1000);
	sprite->addKeyframe(DAMAGED, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));

}

void Boss::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (sprite->animation() != STAND_LEFT) sprite->changeAnimation(STAND_LEFT);

	if (!isAlive && !soundWinPlayed) {
		Audio::instance().playWin();
		soundWinPlayed = true;
	}
}

void Boss::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

glm::ivec2 Boss::getPosition()
{
	return posBoss;
}

void Boss::setPosition(const glm::vec2& pos)
{
	posBoss = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBoss.x), float(tileMapDispl.y + posBoss.y)));
}

void Boss::loseLife(int damage)
{
	lives -= damage;
	sprite->changeAnimation(DAMAGED);
	Audio::instance().playBossDamage();

	if (lives <= 0) isAlive = false;
}

bool Boss::getAliveness()
{
	return isAlive;
}

void Boss::render()
{
	sprite->render();
}

