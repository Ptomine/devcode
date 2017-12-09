#ifndef ATTACK_AREA_HPP
#define ATTACK_AREA_HPP

#include <Box2D/Dynamics/b2World.h>
#include "../../Core/include/Entity.hpp"

class AttackArea : public Entity
{
public:
	AttackArea(const sf::Vector2f&, const sf::Vector2f&, int, EntityGroup);
	~AttackArea();

	EntityManagerRequest* update(float, b2World&);
	void collisionEvent(Entity*);
private:
	int damage;
	EntityGroup target;
};

#endif //ATTACK_AREA_HPP
