#include "../include/AttackArea.hpp"
#include <iostream>

AttackArea::AttackArea(const sf::Vector2f& initPos, const sf::Vector2f& size, int _damage, Entity::EntityGroup _target)
	: Entity(initPos, size, EntityGroup::GROUP_DANGERZONE)
	, damage(_damage)
	, target(_target)
{
}




AttackArea::~AttackArea()
{
}




Entity::EntityManagerRequest* AttackArea::update(float, b2World& world)
{
	active = false;
	return nullptr;
}




void AttackArea::collisionEvent(Entity *other)
{
	if(other->whatGroup() == target)
	{
		other->hurt(damage);
	}
}
