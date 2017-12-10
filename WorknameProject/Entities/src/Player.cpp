#include "../include/Player.hpp"
#include "../include/AttackArea.hpp"
#include <iostream>

Player::Player(const sf::Vector2f& initPos, b2World& world)
	: Unit(initPos, sf::Vector2f(20.0f, 10.0f), GROUP_PLAYER, world, Unit::UnitStats(100.0f, 10.0f, 100.0f))
{
	animationManager.addAnimation(STATE_ATTACK,  new Animation(sprite, "WorknameProject/Textures/PlayerAttack.png",  sf::Vector2u(12, 8), 0.8f, Animation::TYPE_SINGLE));
	animationManager.addAnimation(STATE_DEATH,   new Animation(sprite, "WorknameProject/Textures/PlayerDeath.png",   sf::Vector2u(20, 8), 0.8f, Animation::TYPE_SINGLE));
	animationManager.addAnimation(STATE_IDLE,    new Animation(sprite, "WorknameProject/Textures/PlayerIdle.png",    sf::Vector2u(8, 8),  0.8f , Animation::TYPE_REPEATING));
	animationManager.addAnimation(STATE_STAGGER, new Animation(sprite, "WorknameProject/Textures/PlayerStagger.png", sf::Vector2u(6, 8),  0.3f, Animation::TYPE_SINGLE));
	animationManager.addAnimation(STATE_EVADE,   new Animation(sprite, "WorknameProject/Textures/PlayerVapor.png",   sf::Vector2u(18, 8), 0.8f, Animation::TYPE_SINGLE));
	animationManager.addAnimation(STATE_WALK,    new Animation(sprite, "WorknameProject/Textures/PlayerWalk.png",    sf::Vector2u(8, 8),  0.8f , Animation::TYPE_REPEATING));

	animationManager.setAnimation(STATE_IDLE);

	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height - 20.0f);
}




Player::~Player()
{
}




Entity::EntityManagerRequest* Player::update(float deltaTime, b2World& world)
{
	if(isControllable)
	{
		control(world);
	} else
	{
		actionTimer += deltaTime;

		if(state == STATE_ATTACK && actionTimer >= 0.6f) {
			state = STATE_IDLE;
			return new EntityManagerRequest(EntityManagerRequest::TYPE_ADD, EntityGroup::GROUP_DANGERZONE, "PlayerAttack", new AttackArea(sf::Vector2f(abstractBody.getPosition().x, abstractBody.getPosition().y), sf::Vector2f(100.0f, 100.0f), stats.strenght, GROUP_ENEMY));
		}

		if(animationManager.isAnimationEnded())
		{
			actionTimer = 0.0f;

			if(state == STATE_DEATH)
			{
				return nullptr;
			}

			state = STATE_IDLE;
			animationManager.setAnimation(state);
			isControllable = true;
		}
	}

	movement.x *= stats.speed;
	movement.y *= stats.speed;
	if(movement.x && movement.y)
	{
		movement.x *= 0.8988f;
		movement.y *= 0.4382f;
	}

	if(stats.hp <= 0 && state != STATE_DEATH)
	{
		isAlive = false;
		state = STATE_DEATH;
		animationManager.setAnimation(state);
		isControllable = false;
	}

	animationManager.update(currDir, deltaTime);
	physicalBody->SetLinearVelocity(movement);
	abstractBody.setPosition(physicalBody->GetPosition().x, physicalBody->GetPosition().y);
	sprite.setPosition(abstractBody.getPosition());
	movement.x = movement.y = 0.0f;


	return nullptr;
}




void Player::control(b2World& world)
{
	UnitState newState = STATE_IDLE;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		movement.y++;
		newState = STATE_WALK;
		currDir = DIR_DOWN;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		movement.x--;
		newState = STATE_WALK;
		if(currDir == DIR_DOWN)
		{
			currDir = DIR_DL;
		} else
		{
			currDir = DIR_LEFT;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		movement.y--;
		newState = STATE_WALK;
		switch(currDir)
		{
		case DIR_LEFT:
			currDir = DIR_LU;
			break;
		case DIR_DOWN:
			newState = STATE_IDLE;
		default:
			currDir = DIR_UP;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		movement.x++;
		newState = STATE_WALK;
		switch(currDir)
		{
		case DIR_UP:
			currDir = DIR_UR;
			break;
		case DIR_DOWN:
			currDir = DIR_RD;
			break;
		case DIR_LEFT:
			newState = STATE_IDLE;
		default:
			currDir = DIR_RIGHT;
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) //Run
	{
		movement *= 2.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) //Attack
	{
		newState = STATE_ATTACK;
		isControllable = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) //Evade
	{
		newState = STATE_EVADE;
		isControllable = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) //SightLock
	{
	}

	if(newState != state)
	{
		state = newState;
		animationManager.setAnimation(newState);
	}
}
