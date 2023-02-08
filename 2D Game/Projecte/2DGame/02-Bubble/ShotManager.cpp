#include <GL/glew.h>
#include <GL/glut.h>
#include "ShotManager.h"


void ShotManager::init()
{
	shot = NULL;
}

void ShotManager::update(int deltaTime)
{
	for (Shot* s : playerShots) {
		if (s->getAliveness()) s->update(deltaTime);
		else playerShots.erase(std::remove(playerShots.begin(), playerShots.end(), s), playerShots.end());
	}

	for (Shot* s : enemyShots) {
		if (s->getAliveness()) s->update(deltaTime);
		else enemyShots.erase(std::remove(enemyShots.begin(), enemyShots.end(), s), enemyShots.end());
	}
}

void ShotManager::render()
{
	for(Shot* s : playerShots){
		s->render();
	}

	for (Shot* s : enemyShots) {
		s->render();
	}
}

void ShotManager::addPlayerShot(glm::vec2 posPlayer, ShaderProgram& shaderProgram, TileMap* map, bool isPowerful) {
	shot = new Shot();
	
	shot->init(glm::vec2(32, 32), shaderProgram, true, isPowerful);
	shot->setPosition(glm::vec2(posPlayer.x, posPlayer.y));
	shot->setTileMap(map);

	playerShots.push_back(shot);
}

void ShotManager::addEnemyShot(glm::vec2 posEnemy, ShaderProgram& shaderProgram, TileMap* map, bool isPowerful) {
	shot = new Shot();

	shot->init(glm::vec2(32, 32), shaderProgram, false, isPowerful);
	shot->setPosition(glm::vec2(posEnemy.x, posEnemy.y));
	shot->setTileMap(map);

	enemyShots.push_back(shot);
}

vector<Shot*> ShotManager::getAllPlayerShots() {
	return playerShots;
}

vector<Shot*> ShotManager::getAllEnemyShots() {
	return enemyShots;
}
