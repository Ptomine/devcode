#include "../include/Enemy.hpp"
#include "../include/AttackArea.hpp"

Enemy::Enemy(const sf::Vector2f& initPos, b2World& world, int hp, int strenght, float speed, const std::string& attackpath, const std::string& deathpath, const std::string& idlepath, const std::string& staggerpath, const std::string& walkpath, int attackCount, int deathCount, int idleCount, int staggerCount, int walkCount)
	: Unit(initPos, sf::Vector2f(20.0f, 10.0f), GROUP_ENEMY, world, Unit::UnitStats(hp, strenght, speed))
	, curBehavior(INNACTIVITY)
{
	animationManager.addAnimation(STATE_ATTACK,  new Animation(sprite, attackpath,  sf::Vector2u(attackCount, 8),  0.8f, Animation::TYPE_SINGLE));
	animationManager.addAnimation(STATE_DEATH,   new Animation(sprite, deathpath,   sf::Vector2u(deathCount, 8),   0.8f, Animation::TYPE_SINGLE));
	animationManager.addAnimation(STATE_IDLE,    new Animation(sprite, idlepath,    sf::Vector2u(idleCount, 8),    0.8f, Animation::TYPE_REPEATING));
	animationManager.addAnimation(STATE_STAGGER, new Animation(sprite, staggerpath, sf::Vector2u(staggerCount, 8), 0.3f, Animation::TYPE_SINGLE));
	animationManager.addAnimation(STATE_WALK,    new Animation(sprite, walkpath,    sf::Vector2u(walkCount, 8),    0.8f, Animation::TYPE_REPEATING));

	animationManager.setAnimation(STATE_IDLE);

	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height *0.853f);
}




Enemy::~Enemy()
{
}




Entity::EntityManagerRequest* Enemy::update(float deltaTime, b2World& world)
{
	if(response == nullptr)
	{
		return new EntityManagerRequest(EntityManagerRequest::TYPE_FIND, GROUP_PLAYER, "Player");
	}

	if(isControllable)
	{
		control(world);
	} else
	{
		actionTimer += deltaTime;

		if(state == STATE_ATTACK && actionTimer >= 0.6f) {
			state = STATE_IDLE;
			return new EntityManagerRequest(EntityManagerRequest::TYPE_ADD, EntityGroup::GROUP_DANGERZONE, "EnemyAttack", new AttackArea(sf::Vector2f(abstractBody.getPosition().x, abstractBody.getPosition().y), sf::Vector2f(100.0f, 100.0f), stats.strenght, GROUP_PLAYER));
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
	sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height * 0.853f);
	sprite.setPosition(abstractBody.getPosition());
	movement.x = movement.y = 0.0f;

	return nullptr;
}




void Enemy::control(b2World& world) {
	if(!response->isLive()) {
		if(state!=STATE_IDLE) {
			state = STATE_IDLE;
			animationManager.setAnimation(state);
		}
		return;
	}
	sf::Vector2f playerPos = response->getSprite().getPosition();

	float distance = sqrtf(powf(playerPos.x - sprite.getPosition().x, 2) + powf(playerPos.y - sprite.getPosition().y, 2));
	float viewCos = ( playerPos.x - sprite.getPosition().x ) / distance;
	float viewSin = ( playerPos.y - sprite.getPosition().y ) / distance;

	UnitState newState = STATE_WALK;
	Behavior newBehavior = curBehavior;
	Direction newDir = currDir;
	physicalBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

	if(viewCos >= 0.9239f) {
		newDir = DIR_RIGHT;
	} else if(viewCos >= 0.3827f) {
		if(viewSin > 0.0f) {
			newDir = DIR_RD;
		} else {
			newDir = DIR_UR;
		}
	} else if(viewCos >= -0.3827) {
		if(viewSin > 0.0f) {
			newDir = DIR_DOWN;
		} else {
			newDir = DIR_UP;
		}
	} else if(viewCos >= -0.9239) {
		if(viewSin > 0.0f) {
			newDir = DIR_DL;
		} else {
			newDir = DIR_LU;
		}
	} else {
		newDir = DIR_LEFT;
	}
	Direction clockwiseDir, counterClockwiseDir;
	if(newDir + 1 > 7) {
		clockwiseDir = DIR_DOWN;
	} else {
		clockwiseDir = (Direction)((int)(newDir) + 1);
	}
	if(newDir - 1 < 0) {
		counterClockwiseDir = DIR_RD;
	} else {
		counterClockwiseDir = (Direction)((int)(newDir) - 1);
	}

	if(curBehavior == AGGRESSION) {
		movement = b2Vec2(viewCos, viewSin);

		if(distance >= 360.f) {
			newBehavior = INNACTIVITY;
			newState = STATE_IDLE;
		}

		if(distance <= 50.f) {
			newState = STATE_ATTACK;
			physicalBody->SetLinearVelocity(b2Vec2(0.f, 0.f));
			isControllable = false;
		}
	}

	if(curBehavior == INNACTIVITY) {
		if(((distance <= 360.f && visibility(world, playerPos) && (currDir == newDir) || (currDir == clockwiseDir) || (currDir == counterClockwiseDir))) || distance <= 60.f) {
			newBehavior = AGGRESSION;
			newState = STATE_WALK;
		} else {
			newState = STATE_IDLE;
			newBehavior = INNACTIVITY;
		}
	}

	if(newState != state) {
		state = newState;
		animationManager.setAnimation(newState);
	}

	if(newBehavior != curBehavior) {
		curBehavior = newBehavior;
	}

	if((curBehavior != INNACTIVITY) && (newDir != currDir)) {
		currDir = newDir;
	}
}

bool Enemy::visibility(b2World& world, sf::Vector2f position) {
	for(b2Body* it = world.GetBodyList(); it != nullptr; it = it->GetNext()) {
		if(it->GetType() == b2_staticBody) {
			b2RayCastInput input;
			input.maxFraction=1.f;
			input.p1 = physicalBody->GetPosition();
			input.p2.x = position.x;
			input.p2.y = position.y;
			b2RayCastOutput out;
			bool intersect = it->GetFixtureList()->RayCast(&out, input, 0);
			if(intersect) {
				return false;
			}
		}
	}
	return true;
}
