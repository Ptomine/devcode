#include "../include/AttackArea.hpp"
#include "../include/Unit.hpp"

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
	Entity::EntityGroup group = other->whatGroup();
	if(group == target && group & (Entity::EntityGroup::GROUP_PLAYER | Entity::EntityGroup::GROUP_ENEMY))
	{
		Unit *targeted = static_cast<Unit*>(other);
		targeted->hurt(damage);
		if(targeted->isAlive)
		{
			targeted->stagger();
		}
	}
}
