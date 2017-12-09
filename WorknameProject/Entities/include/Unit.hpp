#ifndef UNIT_HPP
#define UNIT_HPP

#include <Box2D/Box2D.h>
#include "../../Core/include/Entity.hpp"
#include "../../Core/include/AnimationManager.hpp"

class Unit : public Entity
{
public:

	struct UnitStats
	{
		UnitStats(int, int, float);
		int hp;
		int strenght;
		float speed;
	};

	Unit(const sf::Vector2f&, const sf::Vector2f&, EntityGroup, b2World&, const UnitStats&);
	virtual ~Unit();

	virtual void control(b2World&) = 0;
	void collisionEvent(Entity*);

	void hurt(int);
	void stagger();
	
	bool isAlive;
protected:
	b2Body *physicalBody;
	b2Vec2 movement;

	AnimationManager animationManager;
	UnitStats stats;

	float actionTimer;
	bool isControllable;

	enum UnitState
	{
		STATE_IDLE,
		STATE_WALK,
		STATE_ATTACK,
		STATE_EVADE,
		STATE_STAGGER,
		STATE_DEATH
	} state;

	enum Direction
	{
		DIR_DOWN,
		DIR_DL,
		DIR_LEFT,
		DIR_LU,
		DIR_UP,
		DIR_UR,
		DIR_RIGHT,
		DIR_RD,
	} currDir;
};

#endif //UNIT_HPP
