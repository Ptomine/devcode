#include "../include/InteractiveHeal.hpp"
#include "../include/Unit.hpp"

InteractiveHeal::InteractiveHeal(const sf::Vector2f& initPos, const sf::Vector2f& size, int _power)
	: Entity(initPos, size, Entity::EntityGroup::GROUP_PICKUP)
	, power(_power)
	, animationManager()
	, state(STATE_READY)
{
	animationManager.addAnimation(STATE_USED,  new Animation(sprite, "WorknameProject/Textures/PlayerVapor.png", sf::Vector2u(18, 8), 0.8f, Animation::TYPE_SINGLE));
	animationManager.addAnimation(STATE_READY, new Animation(sprite, "WorknameProject/Textures/PlayerIdle.png",  sf::Vector2u(8, 8),  0.8f, Animation::TYPE_REPEATING));
	animationManager.setAnimation(STATE_READY);
}




InteractiveHeal::~InteractiveHeal()
{
}




Entity::EntityManagerRequest* InteractiveHeal::update(float deltaTime)
{
	if(state == STATE_USED)
	{
		if(animationManager.isAnimationEnded())
		{
			state = STATE_READY;
			animationManager.setAnimation(state);
		}
	}
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
