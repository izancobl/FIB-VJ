#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 32

#define INIT_PLAYER_X_TILES 14
#define INIT_PLAYER_Y_TILES 14

#define INIT_ENEMY1_X_TILES 20
#define INIT_ENEMY1_Y_TILES 14


Scene::Scene()
{
	map = NULL;
	player = NULL;
	boss = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (boss != NULL)
		delete boss;
}


void Scene::init()
{
	delay = 0;
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	EnemyManager::instance().init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map);

	boss = new Boss();
	boss->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	boss->setPosition(glm::vec2(640 * map->getTileSize(), 129));
	boss->setTileMap(map);

	ShotManager::instance().init();

	win = new Win();
	win->init();

	go = new Gameover();
	go->init();

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	if (player->getAliveness()) {
		player->update(deltaTime, currentTime);
		boss->update(currentTime);
		EnemyManager::instance().update(currentTime);
		checkCollisions();
		ShotManager::instance().update(deltaTime);
		currentTime += deltaTime;

		if (!boss->getAliveness()) {
			win->update(deltaTime);
		}
		
		if (currentTime <= 136755.0f) {
			
			projection = glm::ortho(currentTime / 7.f, float(SCREEN_WIDTH - 1) + currentTime / 7.f, float(SCREEN_HEIGHT - 1), 0.f);
		}
		else {
			delay--;
			projection = glm::ortho(136755.0f / 7.f, float(SCREEN_WIDTH - 1) + 136755.0f / 7.f, float(SCREEN_HEIGHT - 1), 0.f);
			if (delay <= 0) {
				ShotManager::instance().addEnemyShot(glm::vec2(boss->getPosition().x, (rand() % 700) + 170), texProgram, map, rand() % 2);
				Audio::instance().playBossShot();
				delay = rand() % (60 - 30);
			}
		}
			
	}
	else {
		projection = glm::ortho(currentTime / 7.f, float(SCREEN_WIDTH - 1) + currentTime / 7.f, float(SCREEN_HEIGHT - 1), 0.f);
		go->update(deltaTime);
	}
}

void Scene::setPlayerInvulnerability() {
	player->setInvulnerability();
}

void Scene::setPlayerForce() {
	player->setForce();
}

void Scene::goToFirstPhase() {
	player->setAliveness();
	currentTime = 500.0f;
	projection = glm::ortho(currentTime / 7.f, float(SCREEN_WIDTH - 1) + currentTime / 7.f, float(SCREEN_HEIGHT - 1), 0.f);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
}

void Scene::goToSecondPhase() {
	player->setAliveness();
	currentTime = 35000.0f;
	projection = glm::ortho(currentTime / 7.f, float(SCREEN_WIDTH - 1) + currentTime / 7.f, float(SCREEN_HEIGHT - 1), 0.f);
	player->setPosition(glm::vec2(165 * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
}

void Scene::goToThirdPhase() {
	player->setAliveness();
	currentTime = 116000.0f;
	projection = glm::ortho(currentTime / 7.f, float(SCREEN_WIDTH - 1) + currentTime / 7.f, float(SCREEN_HEIGHT - 1), 0.f);
	player->setPosition(glm::vec2(530 * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
}

void Scene::goToFourthPhase() {
	player->setAliveness();
	currentTime = 132000.0f;
	projection = glm::ortho(currentTime / 7.f, float(SCREEN_WIDTH - 1) + currentTime / 7.f, float(SCREEN_HEIGHT - 1), 0.f);
	player->setPosition(glm::vec2(600 * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
}

void Scene::checkCollisions()
{
	vector <Shot *> playerShots = ShotManager::instance().getAllPlayerShots();
	vector <Shot*> enemyShots = ShotManager::instance().getAllEnemyShots();
	vector<Enemy *> enemies = EnemyManager::instance().getAllEnemies();

	// Player collision with borders
	if (currentTime <= 136755.0f) {
		if ((player->getPosition().x <= currentTime / 7.f - 75) || (player->getPosition().x > float(SCREEN_WIDTH - 1) + currentTime / 7.f)) 
			if (!player->getInvulnerability()) player->loseLife();
	}

	// Player collision with enemies
	for (Enemy* e : enemies) {
		if (((int)(player->getPosition().x / 32) == (int)(e->getPosition().x / 32)) && ((int)(player->getPosition().y / 32) == (int)(e->getPosition().y / 32))) {
			e->loseLife(1);
			if (!player->getInvulnerability()) {
				player->loseLife();
				goToFirstPhase();
			}
		}
	}

	// Player collision with enemy shots
	for (Shot* es : enemyShots) {
		if (((int)(player->getPosition().x / 32) == (int)(es->getPosition().x / 32)) && ((int)(player->getPosition().y / 32) == (int)(es->getPosition().y / 32))) {
			if (!es->getIsPowerful()) es->setAliveness();
			if (!player->getInvulnerability()) {
				player->loseLife();
				goToFirstPhase();
			}
		}
		// Enemy shot collision with left border
		if (es->getPosition().x < 130000.0f / 7.f) es->setAliveness();
	}

	
	// Shots collision with enemies
	for (Shot* s : playerShots) {
		for (Enemy* e : enemies) {
			if (((int)(s->getPosition().x / 32) == (int)(e->getPosition().x / 32)) && ((int)(s->getPosition().y / 32) == (int)(e->getPosition().y / 32))) {
				e->loseLife(s->getShotDamage());
				if (!e->getAliveness()) 
					player->setPoints(e->getPoints() + player->getPoints());

				if(!s->getIsPowerful()) s->setAliveness();
			}
		}
		// Shots collision with right border
		if (s->getPosition().x > float(SCREEN_WIDTH - 1) + currentTime / 7.f) s->setAliveness();
		if (s->getPosition().x >= 641 * SCREEN_X) {
			boss->loseLife(s->getShotDamage());
			s->setAliveness();
		}
	}
}

void Scene::addPlayerShot(bool isPowerful) {
	ShotManager::instance().addPlayerShot(player->getPosition(), texProgram, map, isPowerful);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	EnemyManager::instance().render();
	boss->render();
	ShotManager::instance().render();
	if (!player->getAliveness()) go->render();
	if (!boss->getAliveness()) win->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



