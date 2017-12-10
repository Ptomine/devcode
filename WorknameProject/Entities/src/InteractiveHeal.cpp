#include "../include/InteractiveHeal.hpp"
#include "../include/Unit.hpp"

InteractiveHeal::InteractiveHeal(const sf::Vector2f& initPos, const sf::Vector2f& size, int _power)
	: Entity(initPos, size, Entity::EntityGroup::GROUP_PICKUP)
	, power(_power)
	, animationManager()
	, state(STATE_READY)
{
	animationManager.addAnimation(STATE_USED,  new Animation(sprite, "WorknameProject/Textures/potionempty.png", sf::Vector2u(1, 1), 0.8f, Animation::TYPE_SINGLE));
	animationManager.addAnimation(STATE_READY, new Animation(sprite, "WorknameProject/Textures/potionready.png",  sf::Vector2u(1, 1),  0.8f, Animation::TYPE_REPEATING));
	animationManager.setAnimation(STATE_READY);
}




InteractiveHeal::~InteractiveHeal()
{
}




Entity::EntityManagerRequest* InteractiveHeal::update(float deltaTime, b2World& world)
{
	animationManager.update(0, deltaTime);
	return nullptr;
}




void InteractiveHeal::collisionEvent(Entity *other)
{
	if(state == InteractiveHeal::STATE_READY)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		{
			static_cast<Unit*>(other)->hurt(-power);
			state = STATE_USED;
			animationManager.setAnimation(state);
		}
	}
}
