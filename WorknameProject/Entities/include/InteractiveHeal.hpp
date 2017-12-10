#ifndef INTERACTIVE_HEAL_HPP
#define INTERACTIVE_HEAL_HPP

#include "../../Core/include/Entity.hpp"
#include "../../Core/include/AnimationManager.hpp"

class InteractiveHeal : public Entity
{
public:
	InteractiveHeal(const sf::Vector2f&, const sf::Vector2f&, int);
	~InteractiveHeal();

	EntityManagerRequest* update(float);
	void collisionEvent(Entity*);
private:
	int power;
	AnimationManager animationManager;

	enum InteractiveState
	{
		STATE_USED,
		STATE_READY,
	} state;
};

#endif //INTERACTIVE_HEAL_HPP
