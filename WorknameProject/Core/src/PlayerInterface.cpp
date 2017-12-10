#include "../include/PlayerInterface.hpp"

PlayerInterface::PlayerInterface(sf::View& _view)
	: view(_view)
{
	boardersTexture.loadFromFile("WorknameProject/Textures/Boarders.png");
	boarders.setTexture(boardersTexture);
	hpPoolTexture.loadFromFile("WorknameProject/Textures/health.png");
	hpPool.setTexture(hpPoolTexture);
}




PlayerInterface::~PlayerInterface()
{
}




void PlayerInterface::update(Unit::UnitStats& stats)
{
	sf::Vector2f newPos = view.getCenter() - sf::Vector2f(640.0f, 360.0f);
	hpPool.setScale(stats.hp/stats.maxHp, 1.0f);
	boarders.setPosition(newPos);
	hpPool.setPosition(newPos + sf::Vector2f(5.0f, 5.0f));
}




void PlayerInterface::render(sf::RenderWindow& window)
{
	window.draw(hpPool);
	window.draw(boarders);
}
