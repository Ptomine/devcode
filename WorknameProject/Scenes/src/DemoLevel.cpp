#include "../include/DemoLevel.hpp"
#include "../include/MainMenu.hpp"
#include "../../Entities/include/Player.hpp"
#include "../../Entities/include/Enemy.hpp"
#include <iostream>
#include <tinyxml.h>

DemoLevel::DemoLevel()
	: manager(new EntityManager)
	, world(b2Vec2(0.0f, 0.0f))
{
}




DemoLevel::~DemoLevel()
{
	std::cout << "Deleted demolvl" << std::endl;
	delete manager;
}




void DemoLevel::initialize(sf::RenderWindow&)
{
	level.loadFromFile("WorknameProject/Textures/Levels/Demo/Final.tmx");
	createBarriers(level.getObjects("wall"));

	enemyFromFile("WorknameProject/Textures/Levels/Demo/enemies.xml");
	//manager->getEntity("EnemyName")->flatBody = world.CreateBody(&manager->getEntity("EnemyName")->bodyDef);
	//manager->getEntity("EnemyName")->flatBody->CreateFixture(&manager->getEntity("EnemyName")->bodyShape, 1);
	manager->addEntity("Player", new Player(level.getObject("player").shape.getPoint(0), world));
	//manager->getEntity("playerName")->flatBody = world.CreateBody(&manager->getEntity("playerName")->bodyDef);
	//manager->getEntity("playerName")->flatBody->CreateFixture(&manager->getEntity("playerName")->bodyShape, 1);
}




BasicScene* DemoLevel::update(sf::RenderWindow& window, float deltaTime)
{
	view.setCenter(manager->getEntity(Entity::GROUP_PLAYER, "Player")->getSprite().getPosition());
	view.setSize(1280.f, 720.f);
	window.setView(view);
	world.Step(deltaTime, 8, 3);
	manager->update(deltaTime, world);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		window.setView(window.getDefaultView());
		active = false;
		return new MainMenu;
	}
	return this;
}

void DemoLevel::createBarriers(const std::vector<Object>& barriers) {
	for(auto& object: barriers) {
		b2PolygonShape barrier;

		b2Vec2 vertices[4];
		for(int j = 0; j < 4; j++) {
			vertices[j].Set(object.shape.getPoint(j).x, object.shape.getPoint(j).y);
		}
		barrier.Set(vertices, 4);
		b2BodyDef bDef;
		bDef.type = b2_staticBody;
		world.CreateBody(&bDef)->CreateFixture(&barrier, 1);
	}
}


void DemoLevel::render(sf::RenderWindow& window)
{
	level.drawLayer(window, 0);
	level.drawLayer(window, 1);
	level.drawLayer(window, 2);
	manager->render(window);
	level.drawLayer(window, 3);
	level.drawLayer(window, 4);

}

void DemoLevel::enemyFromFile(std::string path) {
	TiXmlDocument enemiesFile(path);
	enemiesFile.LoadFile();
	TiXmlElement* enemiesBD = enemiesFile.FirstChildElement("enemies");

	std::vector<Object> enemies = level.getObjects("enemy");
	char index = '1';
	for(auto& object: enemies) {
		TiXmlElement* enemy = enemiesBD->FirstChildElement("enemy");
			while(enemy) {
			if(enemy->Attribute("id") == object.type) {
				TiXmlElement* stats = enemy->FirstChildElement("stats");
				int hp = atoi(stats->Attribute("hppool"));
				int strenght = atoi(stats->Attribute("strenght"));
				float speed = strtof(stats->Attribute("speed"), nullptr);

				TiXmlElement* images = enemy->FirstChildElement("images");

				std::string name = "Enemy";
				name.push_back(index);
				manager->addEntity(name, new Enemy(object.shape.getPoint(0), world, hp, strenght, speed,
				                                      images->Attribute("attack"), images->Attribute("death"),
				                                      images->Attribute("idle"), images->Attribute("stagger"),
				                                      images->Attribute("walk"), atoi(images->Attribute("attackCount")), atoi(images->Attribute("deathCount")), atoi(images->Attribute("idleCount")), atoi(images->Attribute("staggerCount")), atoi(images->Attribute("walkCount"))));
				index++;
			}
			enemy = enemy->NextSiblingElement("enemy");
		}
	}
}