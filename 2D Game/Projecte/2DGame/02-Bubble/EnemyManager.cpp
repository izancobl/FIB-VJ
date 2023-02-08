#include "EnemyManager.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"


void EnemyManager::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, TileMap* map)
{
	tl = tileMapPos;
	sp = shaderProgram;
	m = map;
	currentTime = 0;

	e1 = NULL;
	e2 = NULL;
	e3 = NULL;
	e4 = NULL;
}

void EnemyManager::update(int currentTime)
{
	if (cont == 80 && currentTime < 136755.0f) {
		numEnemy = 1 + rand() % (5 - 1);

		if (numEnemy == 1) {
			e1 = new Enemy1;
			e1->init(tl, sp);
			e1->setPosition(glm::vec2(float(1280 - 1) + currentTime / 7.f + 50, (350 + rand() % (601 - 350))));
			e1->setTileMap(m);
			enemies.push_back(e1);
		}
		else if (numEnemy == 2) {
			e2 = new Enemy2;
			e2->init(tl, sp);
			e2->setPosition(glm::vec2(float(1280 - 1) + currentTime / 7.f + 50, (350 + rand() % (601 - 350))));
			e2->setTileMap(m);
			enemies.push_back(e2);
		}
		else if (numEnemy == 3) {
			e3 = new Enemy3;
			e3->init(tl, sp);
			e3->setPosition(glm::vec2(float(1280 - 1) + currentTime / 7.f + 50, (350 + rand() % (601 - 350))));
			e3->setTileMap(m);
			enemies.push_back(e3);
		}
		else {
			e4 = new Enemy4;
			e4->init(tl, sp);
			e4->setPosition(glm::vec2(float(1280 - 1) + currentTime / 7.f + 50, (350 + rand() % (601 - 350))));
			e4->setTileMap(m);
			enemies.push_back(e4);
		}
		cont = 0;
	}

	for (Enemy* e : enemies) {
		if (e->getAliveness()) e->update(currentTime);
		else enemies.erase(std::remove(enemies.begin(), enemies.end(), e), enemies.end());
	}

	++cont;
}

void EnemyManager::render()
{
	for (Enemy* e : enemies) {
		e->render();
	}
}

vector<Enemy*> EnemyManager::getAllEnemies() {
	return enemies;
}