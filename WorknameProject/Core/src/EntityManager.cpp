#include "../include/EntityManager.hpp"
#include <iostream>
#include <Box2D/Dynamics/b2World.h>

EntityManager::EntityManager()
{
}




EntityManager::~EntityManager()
{
	for(auto& iteratorArr : all)
	{
		for(auto& iteratorMap : iteratorArr)
		{
			delete iteratorMap.second;
		}
	}
}




void EntityManager::addEntity(const std::string& name, Entity *newEntity)
{
	if(newEntity == nullptr)
	{
		return;
	}
	all[newEntity->whatGroup()].insert(std::make_pair(name, newEntity));

	for(auto& iteratorArr : all)
	{
		for(auto& iteratorMap : iteratorArr)
		{
			std::cout << iteratorMap.first << std::endl;
		}
	}
	std::cout << "----------------" << std::endl;
}




Entity* EntityManager::getEntity(Entity::EntityGroup group, const std::string& name)
{
	auto found = all[group].find(name);
	if(found != all[group].end())
	{
		return found->second;
	}
	return nullptr;
}




void EntityManager::update(float deltaTime, b2World& world)
{
	for(auto& iterator : all)
	{
		updateGroup(iterator, deltaTime, world);
	}
	checkCollision(Entity::GROUP_DANGERZONE, Entity::GROUP_PLAYER);
	checkCollision(Entity::GROUP_DANGERZONE, Entity::GROUP_ENEMY);
	checkCollision(Entity::GROUP_PICKUP, Entity::GROUP_PLAYER);
}




void EntityManager::render(sf::RenderWindow& window)
{
	for(auto& iteratorArr : all)
	{
		for(auto& iteratorMap : iteratorArr)
		{
			window.draw(iteratorMap.second->getSprite());
		}
	}
}




void EntityManager::checkCollision(Entity::EntityGroup group1, Entity::EntityGroup group2)
{
	for(auto& iterator1 : all[group1])
	{
		for(auto& iterator2 : all[group2])
		{
			if(iterator1.second->isColliding(iterator2.second))
			{
				iterator1.second->collisionEvent(iterator2.second);
			}
		}
	}
}




void EntityManager::updateGroup(std::unordered_map<std::string, Entity*>& group, float deltaTime, b2World& world)
{
	std::vector<std::string> deqToDelete;
	for(auto& iterator : group)
	{
		if(iterator.second->isActive())
		{
			lastRequest = iterator.second->update(deltaTime, world);
			if(lastRequest != nullptr)
			{
				executeRequest(iterator.second);
				iterator.second->update(0.0f, world);
				delete lastRequest;
				lastRequest = nullptr;
			}
		}
		else
		{
			delete iterator.second;
			deqToDelete.push_back(iterator.first);
		}
	}
	for(auto& trash: deqToDelete) {
		group.erase(trash);
	}
}




void EntityManager::executeRequest(Entity *requester)
{
	switch(lastRequest->reqType)
	{
		case Entity::EntityManagerRequest::TYPE_ADD:
			addEntity(lastRequest->targetName, lastRequest->additive);
			break;
		case Entity::EntityManagerRequest::TYPE_FIND:
			requester->setResponse(getEntity(lastRequest->targetGroup, lastRequest->targetName));
			break;
	}
}
