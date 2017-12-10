#ifndef PLAYER_INTERFACE_HPP
#define PLAYER_INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "../../Entities/include/Unit.hpp"

class PlayerInterface
{
public:
	PlayerInterface(sf::View&);
	~PlayerInterface();

	void update(Unit::UnitStats&);
	void render(sf::RenderWindow&);

	void setPlayer(Unit*);
private:
	sf::View& view;
	sf::Texture boardersTexture;
	sf::Sprite boarders;
	sf::Texture hpPoolTexture;
	sf::Sprite hpPool;
};

#endif //PLAYER_INTERFACE_HPP
