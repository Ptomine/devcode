#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Unit.hpp"

class Enemy : public Unit
{
public:
	Enemy(const sf::Vector2f& initPos, b2World& world, int hp, int strenght, float speed, const std::string& attackpath, const std::string& deathpath, const std::string& idlepath, const std::string& staggerpath, const std::string& walkpath, int attackCount, int deathCount, int idleCount, int staggerCount, int walkCount);
	~Enemy();

	EntityManagerRequest* update(float, b2World&);
	void control(b2World&);

	bool visibility(b2World& world, sf::Vector2f position);
private:
	enum Behavior
	{   INNACTIVITY,
		ALERTNESS,
		AGGRESSION,
		ESCAPE
	} curBehavior;
};

#endif //ENEMY_HPP
