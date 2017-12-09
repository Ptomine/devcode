#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Unit.hpp"

class Player : public Unit
{
public:
	Player(const sf::Vector2f&, b2World& world);
	~Player();

	EntityManagerRequest* update(float, b2World&);
	void control(b2World&);
};

#endif //PLAYER_HPP
