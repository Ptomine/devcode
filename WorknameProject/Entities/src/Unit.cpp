#include "../include/Unit.hpp"
#include <iostream>

Unit::UnitStats::UnitStats(float _hp, float _strenght, float _speed)
	: maxHp(_hp)
	, hp(_hp)
	, strenght(_strenght)
	, speed(_speed)
{
}




Unit::Unit(const sf::Vector2f& initPos, const sf::Vector2f& size, EntityGroup group, b2World& world, const UnitStats& _stats)
	: Entity(initPos, sf::Vector2f(size.x + 1.0f, size.y + 1.0f), group)
	, movement(0.0f, 0.0f)
	, animationManager()
	, stats(_stats)
	, actionTimer(0.0f)
	, isControllable(true)
	, isAlive(true)
	, state(STATE_IDLE)
	, currDir(DIR_DOWN)
{
	b2BodyDef physicalBodyDef;
	physicalBodyDef.type = b2_dynamicBody;
	physicalBodyDef.position.Set(abstractBody.getPosition().x, abstractBody.getPosition().y);

	physicalBody = world.CreateBody(&physicalBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x, size.y);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1.0f;
	physicalBody->CreateFixture(&boxFixtureDef);
}




Unit::~Unit()
{
}




void Unit::collisionEvent(Entity*)
{
}




void Unit::hurt(float dmg)
{
	stats.hp -= dmg;
	if(stats.hp <= 0) {
		live = false;
	}
}




void Unit::stagger()
{
	isControllable = false;
	state = STATE_STAGGER;
	animationManager.setAnimation(state);
}




Unit::UnitStats& Unit::getStats()
{
	return stats;
}
